/************************************************** 
 * @Author: shuren
 * @Date: 2022-03-02 17:31:17
 * @LastEditTime: 2022-03-04 17:27:28
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_app\disp.c
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#include "disp.h"
#include "base_typle.h"
#include "hc595.h"
//point
struct data_bin_s* cur_p;
struct data_bin_s* head_p;
//data bin
struct data_bin_s time;
struct data_bin_s accum_yield;
struct data_bin_s prev_glue_up;
struct data_bin_s cur_yield_front;
struct data_bin_s prev_glue_dowm;
struct data_bin_s tem;
struct data_bin_s hum;
struct data_bin_s cur_yield_rear;
struct data_bin_s next_glue_up;
struct data_bin_s next_glue_dowm;
struct data_bin_s bank;
//flash
struct flash_flag_s flash;

STACK_S button_record;
void disp_clear_link()
{
    head_p = NULL;
    cur_p = head_p;
}
void disp_set_head(DATA_BIN_S* head)
{
    head_p = head;
    head->next = head;
    head->prev = head;
    cur_p  = head_p;
}
void disp_add_link(DATA_BIN_S* add)
{
    DATA_BIN_S* p;
	DATA_BIN_S* p_prev;
    uint8_t i=0;
    if(head_p == NULL)
    {
        head_p = add;
        add->next = add;
        add->prev = add;
    }else{
        p_prev = head_p;
        p = head_p->next;
        while (p!=NULL && i<100) {
            p_prev = p;
            p = p->next;
            i++;
        }
        p_prev->next = add;
        add->prev    = p_prev;
        add->next    = head_p;
        head_p->prev   = add;
    }
}
void disp_var_init()
{
    disp_set_head(&time);
    disp_add_link(&accum_yield);
    disp_add_link(&prev_glue_up);
    disp_add_link(&cur_yield_front);
    disp_add_link(&prev_glue_dowm);
    disp_add_link(&tem);
    disp_add_link(&hum);
    disp_add_link(&cur_yield_rear);
    disp_add_link(&next_glue_up);
    disp_add_link(&next_glue_dowm);
    disp_add_link(&bank);
    cover_disp_permission(TRUE);
    cover_disp_flash(FLASH_NULL);
    disp_read_store();
    syn_disp_store2data();
    disp_num_max_init();  
    clear_button_stack();
}
void disp_all_link()
{
    disp_set_head(&time);
    disp_add_link(&accum_yield);
    disp_add_link(&prev_glue_up);
    disp_add_link(&cur_yield_front);
    disp_add_link(&prev_glue_dowm);
    disp_add_link(&tem);
    disp_add_link(&hum);
    disp_add_link(&cur_yield_rear);
    disp_add_link(&next_glue_up);
    disp_add_link(&next_glue_dowm);
    disp_add_link(&bank);
    cover_disp_permission(TRUE);
    cover_disp_flash(FLASH_NULL);
    syn_disp_store2data();
    disp_num_max_init();
}
void disp_num_max_init()
{
    time.num_max        = 12;
    accum_yield.num_max = 4;
    prev_glue_up.num_max    = 2;
    cur_yield_front.num_max = 2;
    prev_glue_dowm.num_max  = 2;
    tem.num_max         = 3;
    hum.num_max         = 3;
    cur_yield_rear.num_max  = 2;
    next_glue_up.num_max    = 2;
    next_glue_dowm.num_max  = 2;
    bank.num_max        = 2;
}

void syn_disp_data2store()
{
    // DATA_BIN_S* p;
    // uint8_t i=0;
    // p = head_p;
    // do
    // {
    //     p->store = p->data;
    //     p = p->next;
    //     i++;
    // }while(p!=head_p && i<100);
}
uint8_t search_disp(DATA_BIN_S* data)
{
    DATA_BIN_S* p;
    uint8_t i=0;
    p = head_p;
    do
    {
        if(p == data) return TRUE;
        p = p->next;
        i++;
    }while(p!=head_p && i<100);
    return FALSE;
}
void syn_disp_store2data()
{
    DATA_BIN_S* p;
    uint8_t i=0;
    p = head_p;
    do
    {
        p->data = p->store;
        p = p->next;
        i++;
    }while(p!=head_p && i<100);   
}
void cover_disp_permission(int8_t permission)
{
    DATA_BIN_S* p;
    uint8_t i=0;
    p = head_p;
    do
    {
        p->permission = permission;
        p = p->next;
        i++;
    }while(p!=head_p && i<100);
} 
void cover_disp_flash(int8_t flash)
{
    DATA_BIN_S* p;
    uint8_t i=0;
    p = head_p;
    do
    {
        p->flash = flash;
        p = p->next;
        i++;
    }while(p!=head_p && i<100);
} 
int32_t set_data(int32_t data, int8_t pos, int8_t num)
{
    int32_t temp = 1;
    int32_t temp_l, temp_r;
    int8_t  i;
    for(i=0; i<pos; i++) temp=temp*10;
    temp_l = data%temp;
    temp_r = data/temp;
    temp_r = temp_r/10*10 + num;
    temp_r = temp_r*temp;
    return temp_r+temp_l;
}
void clear_button_stack()
{
    button_record.i= 0;
    button_record.max = 3;
}
void in_button_stack(int16_t sta)
{
    button_record.i++;
    button_record.sta[button_record.i] = sta;
    if(button_record.i < button_record.max) button_record.i++;
}
int16_t out_button_stack()
{
    int16_t temp;
    if(button_record.i<1)return INT16_MIN;
    temp = button_record.sta[button_record.i];
    button_record.i--;
    return temp;
}
void send_num(uint8_t num, boolean_t dot)
{
    uint8_t code;
    switch (num)
    {
        case 0: code=SMG_N0;break;
        case 1: code=SMG_N1;break;
        case 2: code=SMG_N2;break;
        case 3: code=SMG_N3;break;
        case 4: code=SMG_N4;break;
        case 5: code=SMG_N5;break;
        case 6: code=SMG_N6;break;
        case 7: code=SMG_N7;break;    
        case 8: code=SMG_N8;break;  
        case 9: code=SMG_N9;break;  
        default:break;
    }
    (dot==TRUE)?(code&=SEG_DP):(code|=SEG_NDP);
    hc595_send2register(code);
}
void send_reverse_num(uint8_t num, boolean_t dot)
{
    uint8_t code;
    switch (num)
    {
        case 0: code=SMG_RN0;break;
        case 1: code=SMG_RN1;break;
        case 2: code=SMG_RN2;break;
        case 3: code=SMG_RN3;break;
        case 4: code=SMG_RN4;break;
        case 5: code=SMG_RN5;break;
        case 6: code=SMG_RN6;break;
        case 7: code=SMG_RN7;break;    
        case 8: code=SMG_RN8;break;  
        case 9: code=SMG_RN9;break;  
        default:break;
    }
    (dot==TRUE)?(code&=SEG_DP):(code|=SEG_NDP);
    hc595_send2register(code);
}
/****************************************** 
 * @description: 
 * @param {uint8_t} one_char
 * @param {uint8_t} num
 * @return {*}
 ******************************************/
void send_char(uint8_t one_char, uint8_t num)
{
    uint8_t code;
    if(one_char == ' ')code=SMG_SPACK;
    if(one_char == '_')code=SMG_C_;
    uint8_t i;
    for(i=0; i<num; i++) hc595_send2register(code);
}
/****************************************** 
 * @description: 
 * @param {*}
 * @return {*}
 ******************************************/
void disp_refresh_task()
{
    uint8_t temp;
    DATA_BIN_S* p;
    p = &time;
	if(search_disp(p)) { 
        if(p->flash == FLASH_ALL && flash.flag == TRUE) {
            send_char('_',p->num_max);
        }else{
            temp = p->disp%10;
            if (p->flash==1 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/10%10;
            if (p->flash==2 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/100%10;
            if (p->flash==3 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/1000%10;
            if (p->flash==4 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/10000%10;
            if (p->flash==5 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/100000%10;
            if (p->flash==6 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/1000000%10;
            if (p->flash==7 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/10000000%10;
            if (p->flash==8 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/100000000%10;
            if (p->flash==9 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/1000000000%10;
            if (p->flash==10 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/10000000000%10;
            if (p->flash==11 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/100000000000%10;
            if (p->flash==12 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}           
        }
	}else{
		send_char(' ',p->num_max);     
	}
    p = &accum_yield;
	if(search_disp(p)) { 
        if(p->flash == FLASH_ALL && flash.flag == TRUE) {
            send_char('_',p->num_max);
        }else{
            temp = p->disp%10;
            if (p->flash==1 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/10%10;
            if (p->flash==2 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/100%10;
            if (p->flash==3 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/1000%10;
            if (p->flash==4 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}          
        }
	}else{
		send_char(' ',p->num_max);     
	}
    p = &prev_glue_up;
	if(search_disp(p)) { 
        if(p->flash == FLASH_ALL && flash.flag == TRUE) {
            send_char('_',p->num_max);
        }else{
            temp = p->disp%10;
            if (p->flash==1 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/10%10;
            if (p->flash==2 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}        
        }
	}else{
		send_char(' ',p->num_max);     
	}
    p = &cur_yield_front;
	if(search_disp(p)) { 
        if(p->flash == FLASH_ALL && flash.flag == TRUE) {
            send_char('_',p->num_max);
        }else{
            temp = p->disp%10;
            if (p->flash==1 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/10%10;
            if (p->flash==2 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}        
        }
	}else{
		send_char(' ',p->num_max);     
	}
    p = &prev_glue_dowm;
	if(search_disp(p)) { 
        if(p->flash == FLASH_ALL && flash.flag == TRUE) {
            send_char('_',p->num_max);
        }else{
            temp = p->disp%10;
            if (p->flash==1 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/10%10;
            if (p->flash==2 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}        
        }
	}else{
		send_char(' ',p->num_max);     
	}
    p = &tem;
	if(search_disp(p)) { 
        if(p->flash == FLASH_ALL && flash.flag == TRUE) {
            send_char('_',p->num_max);
        }else{
            temp = p->disp%10;
            if (p->flash==1 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/10%10;
            if (p->flash==2 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}        
            temp = p->disp/100%10;
            if (p->flash==3 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);} 
        }
	}else{
		send_char(' ',p->num_max);     
	}
    p = &hum;
	if(search_disp(p)) { 
        if(p->flash == FLASH_ALL && flash.flag == TRUE) {
            send_char('_',p->num_max);
        }else{
            temp = p->disp%10;
            if (p->flash==1 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/10%10;
            if (p->flash==2 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}        
            temp = p->disp/100%10;
            if (p->flash==3 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);} 
        }
	}else{
		send_char(' ',p->num_max);     
	}
   p = &cur_yield_rear;
	if(search_disp(p)) { 
        if(p->flash == FLASH_ALL && flash.flag == TRUE) {
            send_char('_',p->num_max);
        }else{
            temp = p->disp%10;
            if (p->flash==1 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/10%10;
            if (p->flash==2 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}        
        }
	}else{
		send_char(' ',p->num_max);     
	}
   p = &next_glue_up;
	if(search_disp(p)) { 
        if(p->flash == FLASH_ALL && flash.flag == TRUE) {
            send_char('_',p->num_max);
        }else{
            temp = p->disp%10;
            if (p->flash==1 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/10%10;
            if (p->flash==2 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}        
        }
	}else{
		send_char(' ',p->num_max);     
	}
   p = &next_glue_dowm;
	if(search_disp(p)) { 
        if(p->flash == FLASH_ALL && flash.flag == TRUE) {
            send_char('_',p->num_max);
        }else{
            temp = p->disp%10;
            if (p->flash==1 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}
            temp = p->disp/10%10;
            if (p->flash==2 && flash.flag==TRUE){send_char('_',1);}
            else{hc595_send2register(temp);}        
        }
	}else{
		send_char(' ',p->num_max);     
	}
	hc595_parallel_output();	
}


        // temp = p->disp%10;
		// hc595_send2register(temp);
        // temp = p->disp/10%10;
		// hc595_send2register(temp);
        // temp = p->disp/100%10;
		// hc595_send2register(temp);
        // temp = p->disp/1000%10;
		// hc595_send2register(temp);
        // temp = p->disp/10000%10;
		// hc595_send2register(temp);
        // temp = p->disp/100000%10;
		// hc595_send2register(temp);
        // temp = p->disp/1000000%10;
		// hc595_send2register(temp);
        // temp = p->disp/10000000%10;
		// hc595_send2register(temp);
        // temp = p->disp/100000000%10;
		// hc595_send2register(temp);
        // temp = p->disp/1000000000%10;
		// hc595_send2register(temp);
        // temp = p->disp/10000000000%10;
		// hc595_send2register(temp);
        // temp = p->disp/100000000000%10;
		// hc595_send2register(temp);