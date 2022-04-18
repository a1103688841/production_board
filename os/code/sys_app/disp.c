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
#include "main.h"

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
/******************************************
 * @description: 
 * @param {DATA_BIN_S*} head
 * @return {*}
******************************************/
void set_link_head(DATA_BIN_S* head)
{
    if(head == NULL) head_p = NULL;
    head_p = head;
    head->next = head;
    head->prev = head;
    cur_p  = head_p;
}
void add_link_node(DATA_BIN_S* add)
{
    DATA_BIN_S* p, *p_prev;
    uint8_t i=0;
    if(head_p == NULL)
    {
        head_p = add;
        add->next = add;
        add->prev = add;
    }else{
        p_prev = head_p;
        p = head_p->next;
        while (p!=head_p && i<100)
        {
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
    set_link_head(&time);
    add_link_node(&accum_yield);
    add_link_node(&prev_glue_up);
    add_link_node(&cur_yield_front);
    add_link_node(&prev_glue_dowm);
    add_link_node(&tem);
    add_link_node(&hum);
    add_link_node(&cur_yield_rear);
    add_link_node(&next_glue_up);
    add_link_node(&next_glue_dowm);
    add_link_node(&bank);
    cover_disp_permission(TRUE);
    cover_link_par_flash(FLASH_NULL);
    disp_read_store();
    syn_link_par_disp2store();
    clear_button_stack();
}
/******************************************
 * @description: 
 * @param {*}
 * @return {*}
******************************************/
void disp_all_link()
{
    set_link_head(&time);
    add_link_node(&accum_yield);
    add_link_node(&prev_glue_up);
    add_link_node(&cur_yield_front);
    add_link_node(&prev_glue_dowm);
    add_link_node(&tem);
    add_link_node(&hum);
    add_link_node(&cur_yield_rear);
    add_link_node(&next_glue_up);
    add_link_node(&next_glue_dowm);
    add_link_node(&bank);
}
/******************************************
 * @description: 
 * @param {DATA_BIN_S*} p
 * @param {uint8_t} max
 * @return {*}
******************************************/
void set_node_posintion_max(DATA_BIN_S* p, uint8_t max)
{
    uint8_t i;
    p->position_max = max;
    p->data_max     = 0;
    for(i=0; i<max; i++)
    {
        p->data_max = p->data_max*10+9;
    }
}
/******************************************
 * @description: 
 * @param {*}
 * @return {*}
******************************************/
void link_parameter_init()
{
    set_node_posintion_max(&time, 14);
    set_node_posintion_max(&accum_yield, 4);
    set_node_posintion_max(&prev_glue_up, 2);
    set_node_posintion_max(&cur_yield_front, 2);
    set_node_posintion_max(&prev_glue_dowm, 2);
    set_node_posintion_max(&tem, 3);
    set_node_posintion_max(&hum, 3);
    set_node_posintion_max(&cur_yield_rear, 2);
    set_node_posintion_max(&next_glue_up, 2);
    set_node_posintion_max(&next_glue_dowm, 2);
    set_node_posintion_max(&bank, 2);
    cover_link_par_flash(FLASH_NULL);
}
/******************************************
 * @description: 
 * @param {*}
 * @return {*}
******************************************/
void link_parameter_first()
{
    disp_all_link();
    set_node_posintion_max(&time, 14);
    set_node_posintion_max(&accum_yield, 4);
    set_node_posintion_max(&prev_glue_up, 2);
    set_node_posintion_max(&cur_yield_front, 2);
    set_node_posintion_max(&prev_glue_dowm, 2);
    set_node_posintion_max(&tem, 3);
    set_node_posintion_max(&hum, 3);
    set_node_posintion_max(&cur_yield_rear, 2);
    set_node_posintion_max(&next_glue_up, 2);
    set_node_posintion_max(&next_glue_dowm, 2);
    set_node_posintion_max(&bank, 2);
    accum_yield.disp = 9999;
    prev_glue_up.disp = 9;
    prev_glue_dowm.disp = 9;
    next_glue_up.disp = 9;
    next_glue_dowm.disp = 9;
    cur_yield_front.disp = 0;
    cur_yield_rear.disp = 0;
    tem.disp = 0;
    tem.single = 1;
    hum.disp = 0;
    hum.single = 1;
    {
        DATA_BIN_S* p;
        uint8_t i=0;
        p = head_p;
        do
        {
            p->flash = FLASH_NULL;
            p->single = 1;
            p = p->next;
            i++;
        }while(p!=head_p && i<100);
    } 
}
/******************************************
 * @description: 
 * @param {*}
 * @return {*}
******************************************/
void syn_link_par_disp2store()
{
    DATA_BIN_S* p;
    uint8_t i=0;
    p = head_p;
    do
    {
        p->store = p->disp;
        p = p->next;
        i++;
    }while(p!=head_p && i<100);
}
/******************************************
 * @description: 
 * @param {*}
 * @return {*}
******************************************/
void syn_link_par_data2disp()
{
    DATA_BIN_S* p;
    uint8_t i=0;
    p = head_p;
    do
    {
        p->disp = p->data;
        p = p->next;
        i++;
    }while(p!=head_p && i<100);
}
/******************************************
 * @description: 
 * @param {*}
 * @return {*}
******************************************/
void syn_link_par_store2disp()
{
    DATA_BIN_S* p;
    uint8_t i=0;
    p = head_p;
    do
    {
        p->disp = p->store;
        p = p->next;
        i++;
    }while(p!=head_p && i<100);
}
/******************************************
 * @description: 
 * @param {DATA_BIN_S*} data
 * @return {*}
******************************************/
uint8_t search_link(DATA_BIN_S* data)
{
    DATA_BIN_S* p;
    uint8_t i=0;
    p = head_p;
    do
    {
        if(p == data) return TRUE;
        if(p == NULL) return FALSE;
        p = p->next;
        i++;
    }while(p!=head_p && i<100);
    return FALSE;
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
/******************************************
 * @description: 
 * @param {int8_t} flash
 * @return {*}
******************************************/
void cover_link_par_flash(int8_t flash)
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
/******************************************
 * @description: 
 * @param {int32_t} data
 * @param {int8_t} pos
 * @param {int8_t} num
 * @return {*}
******************************************/
int64_t set_data(int64_t data, int8_t pos, int8_t num)
{
    int64_t temp = 1;
    int64_t temp_l, temp_r;
    int8_t  i;
		//position is 1 origin
    for(i=1; i<pos; i++) temp=temp*10;
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
/******************************************
 * @description: 
 * @param {uint8_t} num
 * @param {boolean_t} dot
 * @return {*}
******************************************/
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
void send_num2(uint8_t num, boolean_t dot)
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
    hc595_2_send2register(code);
}
void send_reverse_num2(uint8_t num, boolean_t dot)
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
    hc595_2_send2register(code);
}
/******************************************
 * @description: 
 * @param {uint8_t} num
 * @return {*}
******************************************/
void send_null(uint8_t num)
{
    send_char(' ', NDP,num);
}
void send_null2(uint8_t num)
{
    send_char2(' ', NDP,num);
}
/****************************************** 
 * @description: 
 * @param {uint8_t} one_char
 * @param {uint8_t} num
 * @return {*}
 ******************************************/
void send_char(uint8_t one_char, boolean_t dot, uint8_t num)
{
    uint8_t code;
    if(one_char == ' ')code=SMG_SPACK;
    if(one_char == '_')code=SMG_C_;
    if(one_char == '-')code=SMG_SINGLE;
    (dot==TRUE)?(code&=SEG_DP):(code|=SEG_NDP);
    uint8_t i;
    for(i=0; i<num; i++) hc595_send2register(code);
}
void send_reverse_char(uint8_t one_char, boolean_t dot, uint8_t num)
{
    uint8_t code;
    if(one_char == ' ')code=SMG_SPACK;
    if(one_char == '_')code=SMG_RC_;
    (dot==TRUE)?(code&=SEG_DP):(code|=SEG_NDP);
    uint8_t i;
    for(i=0; i<num; i++) hc595_send2register(code);
}
void send_char2(uint8_t one_char, boolean_t dot, uint8_t num)
{
    uint8_t code;
    if(one_char == ' ')code=SMG_SPACK;
    if(one_char == '_')code=SMG_C_;
    if(one_char == '-')code=SMG_SINGLE;
    (dot==TRUE)?(code&=SEG_DP):(code|=SEG_NDP);
    uint8_t i;
    for(i=0; i<num; i++) hc595_2_send2register(code);
}
void send_reverse_char2(uint8_t one_char, boolean_t dot, uint8_t num)
{
    uint8_t code;
    if(one_char == ' ')code=SMG_SPACK;
    if(one_char == '_')code=SMG_RC_;
    (dot==TRUE)?(code&=SEG_DP):(code|=SEG_NDP);
    uint8_t i;
    for(i=0; i<num; i++) hc595_2_send2register(code);
}
/****************************************** 
 * @description: 
 * @param {DATA_BIN_S*} p
 * @param {uint8_t} position
 * @param {uint8_t} dot
 * @return {*}
******************************************/
void num_deal(DATA_BIN_S* p, uint8_t position, uint8_t dot)
{
    int64_t disp;
    uint8_t i;
    uint8_t num;
    num = 0;
    disp = p->disp;
    for(i=1; i<position; i++)
    {
        disp = disp/10;
    }
    num = disp%10;
    if(p->flash==FLASH_ALL && flash.toggle == TRUE){send_char('_',dot,1);}
    else if(p->flash==position && flash.toggle==TRUE){send_char('_',dot,1);}
    else {send_num(num, dot);}
}
void num_reverse_deal(DATA_BIN_S* p, uint8_t position, uint8_t dot)
{
    int64_t disp;
    uint8_t i;
    uint8_t num;
    num = 0;
    disp = p->disp;
    for(i=1; i<position; i++)
    {
        disp = disp/10;
    }
    num = disp%10;
    if(p->flash==FLASH_ALL && flash.toggle == TRUE){send_reverse_char('_',dot,1);}
    else if(p->flash==position && flash.toggle==TRUE){send_reverse_char('_',dot,1);}
    else {send_reverse_num(num, dot);}
}
void num_deal2(DATA_BIN_S* p, uint8_t position, uint8_t dot)
{
    int64_t disp;
    uint8_t i;
    uint8_t num;
    num = 0;
    disp = p->disp;
    for(i=1; i<position; i++)
    {
        disp = disp/10;
    }
    num = disp%10;
    if(p->flash==FLASH_ALL && flash.toggle == TRUE){send_char2('_',dot,1);}
    else if(p->flash==position && flash.toggle==TRUE){send_char2('_',dot,1);}
    else {send_num2(num, dot);}
}
void num_reverse_deal2(DATA_BIN_S* p, uint8_t position, uint8_t dot)
{
    int64_t disp;
    uint8_t i;
    uint8_t num;
    num = 0;
    disp = p->disp;
    for(i=1; i<position; i++)
    {
        disp = disp/10;
    }
    num = disp%10;
    if(p->flash==FLASH_ALL && flash.toggle == TRUE){send_reverse_char2('_',dot,1);}
    else if(p->flash==position && flash.toggle==TRUE){send_reverse_char2('_',dot,1);}
    else {send_reverse_num2(num, dot);}
}
/******************************************
 * @description: 
 * @param {DATA_BIN_S*} p
 * @param {uint8_t} position
 * @param {uint8_t} dot
 * @return {*}
******************************************/
void single_deal(DATA_BIN_S* p, boolean_t dot)
{
    if(p->single == -1)
    {
        send_char('-',NDP,1);
    }else{
        send_char(' ',NDP,1);
    }
}
/****************************************** 
 * @description: 
 * @param {*}
 * @return {*}
 ******************************************/
void disp_refresh_task()
{
    uint8_t num;
    DATA_BIN_S* p;
    //clear cache
    send_null(2);
    //left to right
    p = &time;
 	if(search_link(p))
    { 
        //skip second
    //    num_deal2(p,3,NDP);
    //    num_deal2(p,4,NDP); 
    //    num_deal2(p,5,NDP);
    //    num_deal2(p,6,NDP);
       num_deal(p,7,NDP);
       num_deal(p,8,NDP);
       num_deal(p,9,NDP);
       num_deal(p,10,NDP);
       num_deal(p,11,NDP);
       num_deal(p,12,NDP);
       num_deal(p,13,NDP);
       num_deal(p,14,NDP);
 	}else{
        // send_null2(4);
 		send_null(8);     
 	}
    p = &accum_yield;
 	if(search_link(p))
    { 
		num_reverse_deal(p,4,NDP);
		num_reverse_deal(p,3,NDP);
        num_reverse_deal(p,2,NDP);
        num_reverse_deal(p,1,NDP);
 	}else{
 		send_null(4);     
 	}
    //left to right
    p = &cur_yield_front;
 	if(search_link(p))
    { 
		num_deal(p,1,NDP);
		num_deal(p,2,NDP);
 		num_deal(p,3,NDP);
		num_deal(p,4,NDP);
     }
     else
     {
 		send_null(4);     
 	}
    //random
    //order    2 1 3
    //position 3 2 1
    p = &tem;
 	if(search_link(p))
    { 
        if(sta == STA_COMPENSATION || sta == STA_DATA_RST)
        {
            num_deal(p,2,DP);
            single_deal(p,NDP);
            num_reverse_deal(p,1,NDP);         
        }else{
            num_deal(p,2,DP);
            num_deal(p,3,NDP);
            num_reverse_deal(p,1,NDP);
        }
 	}else{
 		send_null(3);     
 	}
    //left to right
    p = &hum;
 	if(search_link(p)) 
    { 
        if(sta == STA_COMPENSATION || sta == STA_DATA_RST)
        {
            num_deal(p,1,NDP);
            num_deal(p,2,DP);
            single_deal(p,NDP);
        }else{
            num_deal(p,1,NDP);
            num_deal(p,2,DP);
            num_deal(p,3,NDP);
        }
 	}else{
 		send_null(3);     
 	}
	hc595_parallel_output();
}
/******************************************
 * @description: 
 * @param {*}
 * @return {*}
******************************************/
void disp_refresh_task_2()
{
    uint8_t num;
    DATA_BIN_S* p;
    //clear cache
    send_null2(2);
    p = &cur_yield_rear;
    if(search_link(p))
    { 
       num_deal2(p,1,NDP);
       num_deal2(p,2,NDP); 
	}else{
		send_null2(2);     
	}
    p = &next_glue_up;
    if(search_link(p))
    { 
       num_deal2(p,1,NDP);
       num_deal2(p,2,NDP); 
	}else{
		send_null2(2);     
	}
    p = &next_glue_dowm;
    if(search_link(p))
    { 
       num_deal2(p,1,NDP);
       num_deal2(p,2,NDP); 
	}else{
		send_null2(2);     
	}
    p = &prev_glue_dowm;
    if(search_link(p))
    { 
       num_deal2(p,1,NDP);
       num_deal2(p,2,NDP); 
	}else{
		send_null2(2);     
	}
   p = &prev_glue_up;
	if(search_link(p))
   { 
       num_deal2(p,2,NDP);
       num_deal2(p,1,NDP); 
	}else{
		send_null2(2);     
	}
    //left to right
    p = &time;
 	if(search_link(p))
    { 
        //skip second
       num_deal2(p,3,NDP);
       num_deal2(p,4,NDP); 
       num_deal2(p,5,NDP);
       num_deal2(p,6,NDP);
 	}else{
        send_null2(4);  
 	}
	hc595_2_parallel_output();
}