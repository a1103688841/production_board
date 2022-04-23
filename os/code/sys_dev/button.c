/**************************************************************************************************
* fuction	:                              button     
* file		:  button.c     
* brief		:     
* author	: rinanfang  3/2/2020
**************************************************************************************************/

#define __BUTTON_C__
/* ------------------------------------------- include ----------------------------------------- */
#include "button.h"
#include "base_typle.h"
#include "main.h"
#include "disp.h"
static uint8_t switch_code;
void set_switch_code(uint8_t code)
{
  switch_code = code;
}
static uint32_t matrix_code;
void set_matrix_button_code(uint64_t code)
{
  matrix_code = code;
}
/* ----------------------------------------------------------------------------------------------------- */
/* -------------------------------------------sw level ----------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
static uint8_t Read_SW_OFF_Level(void)
{
  if(matrix_code == 0x38){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_EDIT_Level(void)
{
  if(matrix_code == 0x00){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_TYPLE_Level(void)
{
  if(matrix_code == 0x10){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_METER_Level(void)
{
  if(matrix_code == 0x90){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_STEP_Level(void)
{
  if(matrix_code == 0x50){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_DEL_Level(void)
{
  if(matrix_code == 0x30){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_F1_Level(void)
{
  if(matrix_code == 0x40){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_TIME_Level(void)
{
  if(matrix_code == 0xd8){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_F2_Level(void)
{
  if(matrix_code == 0x60){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_OK_Level(void)
{
  if(matrix_code == 0xc0){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_F3_Level(void)
{
  if(matrix_code == 0xa0){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_N0_Level(void)
{
  if(matrix_code == 0xb8){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_F4_Level(void)
{
  if(matrix_code == 0x20){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_DOT_Level(void)
{
  if(matrix_code == 0x80){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_N1_Level(void)
{
  if(matrix_code == 0x08){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_N2_Level(void)
{
  if(matrix_code == 0x88){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_N3_Level(void)
{
  if(matrix_code == 0x48){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_N4_Level(void)
{
  if(matrix_code == 0x28){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_N5_Level(void)
{
  if(matrix_code == 0xa8){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_N6_Level(void)
{
  if(matrix_code == 0x68){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_N7_Level(void)
{
  if(matrix_code == 0x18){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_N8_Level(void)
{
  if(matrix_code == 0x98){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_N9_Level(void)
{
  if(matrix_code == 0x58){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_SPACE_Level(void)
{
  if(matrix_code == 0xc8){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_STOP_Level(void)
{
  if(matrix_code == 0xe8){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_CLR_Level(void)
{
  if(switch_code == 0x02){return HIGHT;}else{return FALSE;}
}
static uint8_t Read_SW_ADD_Level(void)
{
  if(switch_code == 0x01){return HIGHT;}else{return FALSE;}
}
/**************************************************************************************************
*                                 SW call back
**************************************************************************************************/
void SW_OFF_Down_CallBack(void *btn)
{  
  switch (sta)
  {
      default:
        break;
      case STA_NORMAL:
        sta = STA_OFF;
        clear_button_stack();
        set_link_head(NULL);
        break;
      case STA_DATA_RST:
        syn_link_par_store2disp();
        sta = STA_NORMAL;
        disp_all_link();
        cover_link_par_flash(FLASH_NULL);
        break;
      case STA_OFF:
        sta = STA_NORMAL;
        disp_all_link();
        cover_link_par_flash(FLASH_NULL);
        break;
      case STA_OPTO_SWITCH:
      case STA_CHANNEL_NUM:
      case STA_EDIT_CLEAR_TIME:
      case STA_EDIT:
      case STA_EDIT_REAR:
          sta = STA_NORMAL;
          syn_link_par_store2disp();
          disp_all_link();
          cover_link_par_flash(FLASH_NULL);
          break;
      case STA_ADDR:
          time.disp = time.data;
          sta = STA_NORMAL;
          disp_all_link();
          cover_link_par_flash(FLASH_NULL);
          break;
      case STA_COMPENSATION:
      case STA_TIME:
          sta = STA_NORMAL;
          disp_all_link();
          cover_link_par_flash(FLASH_NULL);
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_EDIT_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_NORMAL:
          sta = STA_EDIT;
          set_link_head(&accum_yield);
          add_link_node(&cur_yield_front);
          add_link_node(&prev_glue_up);
          add_link_node(&prev_glue_dowm);
          cover_link_par_flash(FLASH_NULL);
          accum_yield.flash  = FLASH_ALL;
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_TYPLE_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_TIME:
          // if(out_button_stack() == STA_OFF) {
          //   sta = STA_CLEAR_TIME;
          // }
          break;
      case STA_NORMAL:
        sta = STA_COMPENSATION;
        set_link_head(&tem);
        add_link_node(&hum);
        syn_link_par_store2disp();
        cover_link_par_flash(FLASH_NULL);
        cur_p->flash = FLASH_ALL;
        break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_METER_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_NORMAL:
          sta = STA_CHANNEL_NUM;
          set_link_head(&cur_yield_rear);
          add_link_node(&next_glue_up);
          cover_link_par_flash(FLASH_NULL);
          cur_yield_rear.flash  = FLASH_ALL;   
          serial_p = &next_glue_up;
          serial_data_p = &cur_yield_rear;
          next_glue_up.disp = 1;  
          next_glue_up.serial_max = 4;
          cur_yield_rear.disp = cur_yield_rear.store_n[next_glue_up.disp];
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_STEP_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_NORMAL:
          sta = STA_OPTO_SWITCH;
          set_link_head(&accum_yield);
          add_link_node(&cur_yield_front);
          cover_link_par_flash(FLASH_NULL);
          accum_yield.flash  = FLASH_ALL;   
          cur_yield_front.disp = 1;  
          cur_yield_front.serial_max = 3;
          serial_p = &cur_yield_front;
          serial_data_p = &accum_yield;
          serial_data_p->disp = serial_data_p->store_n[serial_p->disp];
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_DEL_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_NORMAL:
          sta = STA_EDIT_REAR;
          set_link_head(&cur_yield_rear);
          add_link_node(&next_glue_up);
          add_link_node(&next_glue_dowm);
          cover_link_par_flash(FLASH_NULL);
          cur_yield_rear.flash  = FLASH_ALL;      
        break;
      case STA_ADDR:
          cur_p->disp_n[1] = 0;
          cur_p->disp = cur_p->disp_n[1];
          break;
      case STA_EDIT_CLEAR_TIME:
      case STA_COMPENSATION:
      case STA_EDIT:
      case STA_EDIT_REAR:
          cur_p->disp = 0;
          break;
      case STA_OPTO_SWITCH:
      case STA_CHANNEL_NUM:
        serial_data_p->disp_n[serial_p->disp] = 0;
        serial_data_p->disp = serial_data_p->disp_n[serial_p->disp];
        break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_F1_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OPTO_SWITCH:
      case STA_CHANNEL_NUM:
          serial_p->disp --;
          if(serial_p->disp<1){serial_p->disp=1;}
          serial_data_p->disp = serial_data_p->disp_n[serial_p->disp];
          break;
      case STA_COMPENSATION:
      case STA_EDIT_CLEAR_TIME:
      case STA_EDIT:
      case STA_EDIT_REAR:
          cur_p->flash = FLASH_NULL;
          cur_p = cur_p->prev;
          cur_p->flash = FLASH_ALL;
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_TIME_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OFF: 
        sta = STA_TIME;
        //in_button_stack(STA_OFF);
        set_link_head(&time);
        cover_link_par_flash(FLASH_NULL);
        cur_p->flash  = 12;
        break;
      case STA_NORMAL:
          sta = STA_TIME;
          set_link_head(&time);
          cover_link_par_flash(FLASH_NULL);
          cur_p->flash  = 12;
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_F2_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
					break;
      case STA_ADDR: 
      case STA_TIME:
          cur_p->flash++;
          if(cur_p->flash > cur_p->position_max) cur_p->flash = cur_p->position_max;
          break;
      case STA_COMPENSATION:
          cur_p->single = -1;
          break;  
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_OK_Down_CallBack(void *btn)
{
  uint8_t i;
  switch (sta)
  {
      default:
        break;
      case STA_OPTO_SWITCH:
          syn_node_serial_disp2store(serial_data_p);
          write_store();
          syn_link_par_store2disp();
          set_accumulative_prev(accum_yield.disp);
          set_par_lever_timermax(&sw_add,accum_yield.store_n[1]*10/BUTTON_CYCE);
          set_par_sleep_timermax(&sw_add, accum_yield.store_n[2]*10/BUTTON_CYCE);		
          set_par_long_timermax(&sw_add,accum_yield.store_n[3]*10/BUTTON_CYCE);
          set_par_longcyc_timermax(&sw_add, accum_yield.store_n[3]*10/BUTTON_CYCE);
          sta = STA_NORMAL;
          disp_all_link();
          cover_link_par_flash(FLASH_NULL);
          break;
      case STA_CHANNEL_NUM:
          syn_node_serial_disp2store(serial_data_p);
          write_store();
          syn_link_par_store2disp();
          sta = STA_NORMAL;
          disp_all_link();
          cover_link_par_flash(FLASH_NULL);
          break;
      case STA_DATA_RST:
      case STA_EDIT_CLEAR_TIME:
      case STA_COMPENSATION:
          syn_link_par_disp2store();
          write_store();
          set_accumulative_prev(accum_yield.disp);
          sta = STA_NORMAL;
          disp_all_link();
          cover_link_par_flash(FLASH_NULL);
          break;
      case STA_EDIT_REAR:
          syn_link_par_disp2store();
          cur_yield_front.disp = cur_yield_rear.disp;
          cur_yield_front.store = cur_yield_rear.store;
          write_store();
          set_accumulative_prev(accum_yield.disp);
          sta = STA_NORMAL;
          disp_all_link();
          cover_link_par_flash(FLASH_NULL);
          break;
      case STA_EDIT:
          syn_link_par_disp2store();
          cur_yield_rear.disp = cur_yield_front.disp;
          cur_yield_rear.store = cur_yield_front.store;
          write_store();
          set_accumulative_prev(accum_yield.disp);
          sta = STA_NORMAL;
          disp_all_link();
          cover_link_par_flash(FLASH_NULL);
          break;
      case STA_ADDR:
          time.disp = time.data;
          syn_node_serial_disp2store(&time);
          write_store();
          sta = STA_NORMAL;
          disp_all_link();
          cover_link_par_flash(FLASH_NULL);
          break;
      case STA_TIME:
          //miniter
          if(cheak_rtc(cur_p->disp)==TRUE)
          {
            time_adjust(cur_p->disp);
          }else{
            syn_link_par_data2disp();
          }
          sta = STA_NORMAL;
          disp_all_link();
          cover_link_par_flash(FLASH_NULL);
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_F3_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
				break;
      case STA_COMPENSATION:
          cur_p->single = 1;
          break;
      case STA_ADDR: 
          //no moth day hour min second
          cur_p->flash--;
          if(cur_p->flash < 11) cur_p->flash = 11;
        break;
      case STA_TIME:
          //no second
          cur_p->flash--;
          if(cur_p->flash < 3) cur_p->flash = 3;
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_N0_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OPTO_SWITCH:
      case STA_CHANNEL_NUM:
          serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp] *10;
          if(serial_data_p->disp_n[serial_p->disp] > serial_data_p->disp_max)
          {
            serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp]%(serial_data_p->disp_max+1);
          }
          serial_data_p->disp = serial_data_p->disp_n[serial_p->disp];
          break;
      case STA_EDIT_CLEAR_TIME:
      case STA_EDIT:
      case STA_EDIT_REAR:
          cur_p->disp = cur_p->disp *10;
          if(cur_p->disp>cur_p->disp_max)cur_p->disp=cur_p->disp%(cur_p->disp_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = cur_p->disp *10;
          if(cur_p->disp>99)cur_p->disp=cur_p->disp%(99+1);
          break;
      case STA_ADDR:      
          cur_p->disp_n[1] = set_data(cur_p->disp, cur_p->flash, 0);
          cur_p->disp = cur_p->disp_n[1];
          break;
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 0);
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_F4_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OPTO_SWITCH:
      case STA_CHANNEL_NUM:
          serial_p->disp ++;
          if(serial_p->disp > serial_p->serial_max){serial_p->disp=serial_p->serial_max;}
          serial_data_p->disp = serial_data_p->disp_n[serial_p->disp];
          break;
      case STA_COMPENSATION:
      case STA_EDIT_CLEAR_TIME:
      case STA_EDIT:
      case STA_EDIT_REAR:
          cur_p->flash = FLASH_NULL;
          cur_p = cur_p->next;
          cur_p->flash = FLASH_ALL;
          break;
  }
}
void SW_DOT_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OFF:
        sta = STA_ADDR;
        set_link_head(&time);
        cover_link_par_flash(FLASH_NULL);
        cur_p->disp = cur_p->store_n[1];
        cur_p->flash  = 11;
        break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_N1_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OPTO_SWITCH:
      case STA_CHANNEL_NUM:
          serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp] *10+1;
          if(serial_data_p->disp_n[serial_p->disp] > serial_data_p->disp_max)
          {
            serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp]%(serial_data_p->disp_max+1);
          }
          serial_data_p->disp = serial_data_p->disp_n[serial_p->disp];
          break;
      case STA_EDIT_CLEAR_TIME:
      case STA_EDIT:
      case STA_EDIT_REAR:
          cur_p->disp = cur_p->disp*10+1;
          if(cur_p->disp>cur_p->disp_max)cur_p->disp=cur_p->disp%(cur_p->disp_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = cur_p->disp*10+1;
          if(cur_p->disp>99)cur_p->disp=cur_p->disp%(99+1);
          break;      
      case STA_ADDR: 
          cur_p->disp_n[1] = set_data(cur_p->disp, cur_p->flash, 1);
          cur_p->disp = cur_p->disp_n[1];
          break;
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 1);
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_N2_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OPTO_SWITCH:
      case STA_CHANNEL_NUM:
          serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp] *10+2;
          if(serial_data_p->disp_n[serial_p->disp] > serial_data_p->disp_max)
          {
            serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp]%(serial_data_p->disp_max+1);
          }
          serial_data_p->disp = serial_data_p->disp_n[serial_p->disp];
          break;
      case STA_EDIT_CLEAR_TIME:
      case STA_EDIT:
      case STA_EDIT_REAR:
          cur_p->disp = cur_p->disp*10+2;
          if(cur_p->disp>cur_p->disp_max)cur_p->disp=cur_p->disp%(cur_p->disp_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = cur_p->disp*10+2;
          if(cur_p->disp>99)cur_p->disp=cur_p->disp%(99+1);
          break;
      case STA_ADDR:       
          cur_p->disp_n[1] = set_data(cur_p->disp, cur_p->flash, 2);
          cur_p->disp = cur_p->disp_n[1];
          break;
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 2);
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_N3_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OPTO_SWITCH:
      case STA_CHANNEL_NUM:
          serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp] *10+3;
          if(serial_data_p->disp_n[serial_p->disp] > serial_data_p->disp_max)
          {
            serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp]%(serial_data_p->disp_max+1);
          }
          serial_data_p->disp = serial_data_p->disp_n[serial_p->disp];
          break;
      case STA_EDIT_CLEAR_TIME:
      case STA_EDIT:
      case STA_EDIT_REAR:
          cur_p->disp = cur_p->disp*10+3;
          if(cur_p->disp>99)cur_p->disp=cur_p->disp%(cur_p->disp_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = cur_p->disp*10+3;
          if(cur_p->disp>cur_p->disp_max)cur_p->disp=cur_p->disp%(99+1);
          break;   
      case STA_ADDR:    
          cur_p->disp_n[1] = set_data(cur_p->disp, cur_p->flash, 3);
          cur_p->disp = cur_p->disp_n[1];
          break;
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 3);
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_N4_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OPTO_SWITCH:
      case STA_CHANNEL_NUM:
          serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp] *10+4;
          if(serial_data_p->disp_n[serial_p->disp] > serial_data_p->disp_max)
          {
            serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp]%(serial_data_p->disp_max+1);
          }
          serial_data_p->disp = serial_data_p->disp_n[serial_p->disp];
          break;
      case STA_EDIT_CLEAR_TIME:
      case STA_EDIT:
      case STA_EDIT_REAR:
          cur_p->disp = cur_p->disp*10+4;
          if(cur_p->disp>cur_p->disp_max)cur_p->disp=cur_p->disp%(cur_p->disp_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = cur_p->disp*10+4;
          if(cur_p->disp>99)cur_p->disp=cur_p->disp%(99+1);
          break; 
      case STA_ADDR:      
          cur_p->disp_n[1] = set_data(cur_p->disp, cur_p->flash, 4);
          cur_p->disp = cur_p->disp_n[1];
          break;
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 4);
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_N5_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OPTO_SWITCH:
      case STA_CHANNEL_NUM:
          serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp] *10+5;
          if(serial_data_p->disp_n[serial_p->disp] > serial_data_p->disp_max)
          {
            serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp]%(serial_data_p->disp_max+1);
          }
          serial_data_p->disp = serial_data_p->disp_n[serial_p->disp];
          break;
      case STA_EDIT_CLEAR_TIME:
      case STA_EDIT:
      case STA_EDIT_REAR:
          cur_p->disp = cur_p->disp*10+5;
          if(cur_p->disp>cur_p->disp_max)cur_p->disp=cur_p->disp%(cur_p->disp_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = cur_p->disp*10+5;
          if(cur_p->disp>99)cur_p->disp=cur_p->disp%(99+1);
          break;  
      case STA_ADDR:     
          cur_p->disp_n[1] = set_data(cur_p->disp, cur_p->flash, 5);
          cur_p->disp = cur_p->disp_n[1];
          break;
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 5);
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_N6_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OPTO_SWITCH:
      case STA_CHANNEL_NUM:
          serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp] *10+6;
          if(serial_data_p->disp_n[serial_p->disp] > serial_data_p->disp_max)
          {
            serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp]%(serial_data_p->disp_max+1);
          }
          serial_data_p->disp = serial_data_p->disp_n[serial_p->disp];
          break;
      case STA_EDIT_CLEAR_TIME:
      case STA_EDIT:
      case STA_EDIT_REAR:
          cur_p->disp = cur_p->disp*10+6;
          if(cur_p->disp>cur_p->disp_max)cur_p->disp=cur_p->disp%(cur_p->disp_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = cur_p->disp*10+6;
          if(cur_p->disp>99)cur_p->disp=cur_p->disp%(99+1);
          break;      
      case STA_ADDR: 
          cur_p->disp_n[1] = set_data(cur_p->disp, cur_p->flash, 6);
          cur_p->disp = cur_p->disp_n[1];
          break;
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 6);
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_N7_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OPTO_SWITCH:
      case STA_CHANNEL_NUM:
          serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp] *10+7;
          if(serial_data_p->disp_n[serial_p->disp] > serial_data_p->disp_max)
          {
            serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp]%(serial_data_p->disp_max+1);
          }
          serial_data_p->disp = serial_data_p->disp_n[serial_p->disp];
          break;
      case STA_EDIT_CLEAR_TIME:
      case STA_EDIT:
      case STA_EDIT_REAR:
          cur_p->disp = cur_p->disp*10+7;
          if(cur_p->disp>cur_p->disp_max)cur_p->disp=cur_p->disp%(cur_p->disp_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = cur_p->disp*10+7;
          if(cur_p->disp>99)cur_p->disp=cur_p->disp%(99+1);
          break;   
      case STA_ADDR:    
          cur_p->disp_n[1] = set_data(cur_p->disp, cur_p->flash, 7);
          cur_p->disp = cur_p->disp_n[1];
          break;
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 7);
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_N8_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OPTO_SWITCH:
      case STA_CHANNEL_NUM:
          serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp] *10+8;
          if(serial_data_p->disp_n[serial_p->disp] > serial_data_p->disp_max)
          {
            serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp]%(serial_data_p->disp_max+1);
          }
          serial_data_p->disp = serial_data_p->disp_n[serial_p->disp];
          break;
      case STA_EDIT_CLEAR_TIME:
      case STA_EDIT:
      case STA_EDIT_REAR:
          cur_p->disp = cur_p->disp*10+8;
          if(cur_p->disp>cur_p->disp_max)cur_p->disp=cur_p->disp%(cur_p->disp_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = cur_p->disp*10+8;
          if(cur_p->disp>99)cur_p->disp=cur_p->disp%(99+1);
          break;      
      case STA_ADDR: 
          cur_p->disp_n[1] = set_data(cur_p->disp, cur_p->flash, 8);
          cur_p->disp = cur_p->disp_n[1];
          break;
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 8);
          break;
  }
}
/******************************************
 * @description: 
 * @param {void} *btn
 * @return {*}
******************************************/
void SW_N9_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OPTO_SWITCH:
      case STA_CHANNEL_NUM:
          serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp] *10+9;
          if(serial_data_p->disp_n[serial_p->disp] > serial_data_p->disp_max)
          {
            serial_data_p->disp_n[serial_p->disp] = serial_data_p->disp_n[serial_p->disp]%(serial_data_p->disp_max+1);
          }
          serial_data_p->disp = serial_data_p->disp_n[serial_p->disp];
          break;
      case STA_EDIT_CLEAR_TIME:
      case STA_EDIT:
      case STA_EDIT_REAR:
          cur_p->disp = cur_p->disp*10+9;
          if(cur_p->disp>cur_p->disp_max)cur_p->disp=cur_p->disp%(cur_p->disp_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = cur_p->disp*10+9;
          if(cur_p->disp>99)cur_p->disp=cur_p->disp%(99+1);
          break;     
      case STA_ADDR:      
          cur_p->disp_n[1] = set_data(cur_p->disp, cur_p->flash, 9);
          cur_p->disp = cur_p->disp_n[1];
          break;
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 9);
          break;
  }
}
void SW_SPACE_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_OFF:
          sta = STA_DATA_RST;
          disp_all_link();
          cover_link_par_flash(FLASH_NULL);
          link_parameter_first();
          break;
  } 
}
void SW_STOP_Down_CallBack(void *btn)
{
}
void SW_CLR_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_NORMAL:
        cur_yield_front.disp = 0;
        cur_yield_rear.disp = 0;
        cur_yield_front.store = 0;
        cur_yield_rear.store = 0;
        break;
      case STA_OFF:
        break;
  }
}
void SW_CLR_LONG_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_NORMAL:
        accum_yield.disp = 0;
        cur_yield_front.disp = 0;
        cur_yield_rear.disp = 0;
        accum_yield.store = 0;
        cur_yield_front.store = 0;
        cur_yield_rear.store = 0;
        break;
      case STA_OFF:
        break;
  }
}
void SW_ADD_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
        break;
      case STA_NORMAL:
        accum_yield.disp++;
        cur_yield_front.disp++;
        cur_yield_rear.disp = cur_yield_front.disp;
        accum_yield.store = accum_yield.disp;
        cur_yield_front.store = cur_yield_front.disp;
        cur_yield_rear.store = cur_yield_rear.disp;
        break;
      case STA_OFF:
        break;
  }
}
/**************************************************************************************************
* 函数:                                   buttonGpioInit
* 说明: 修改按键引脚初始化 
* 输入:  
**************************************************************************************************/
static void buttonGpioInit(void)
{


}
/**************************************************************************************************
* 函数:                                   buttonAttachInit
* 说明:  按键链接初始化
**************************************************************************************************/
void buttonAttachInit(void)
{
  Head_Button = NULL;
  buttonGpioInit();
  //first line
  Button_Create("off",&sw_off,Read_SW_OFF_Level);
  Button_Attach(&sw_off,BUTTON_DOWN,SW_OFF_Down_CallBack);               //call fuction attach
  Button_Create("edit",&sw_edit,Read_SW_EDIT_Level);                     //call fuction attach
  Button_Attach(&sw_edit,BUTTON_DOWN,SW_EDIT_Down_CallBack);             //call fuction attach
  //second line
  Button_Create("typle",&sw_typle,Read_SW_TYPLE_Level);                     //call fuction attach
  Button_Attach(&sw_typle,BUTTON_DOWN,SW_TYPLE_Down_CallBack);             //call fuction attach
  Button_Create("meter",&sw_meter,Read_SW_METER_Level);                     //call fuction attach
  Button_Attach(&sw_meter,BUTTON_DOWN,SW_METER_Down_CallBack);             //call fuction attach
  Button_Create("step",&sw_step,Read_SW_STEP_Level);                     //call fuction attach
  Button_Attach(&sw_step,BUTTON_DOWN,SW_STEP_Down_CallBack);             //call fuction attach
  //third line
  Button_Create("del",&sw_del,Read_SW_DEL_Level);                     //call fuction attach
  Button_Attach(&sw_del,BUTTON_DOWN,SW_DEL_Down_CallBack);             //call fuction attach
  Button_Create("f1",&sw_f1,Read_SW_F1_Level);                     //call fuction attach
  Button_Attach(&sw_f1,BUTTON_DOWN,SW_F1_Down_CallBack);             //call fuction attach
  Button_Create("time",&sw_time,Read_SW_TIME_Level);                     //call fuction attach
  Button_Attach(&sw_time,BUTTON_DOWN,SW_TIME_Down_CallBack);             //call fuction attach
  //fourth line
  Button_Create("f2",&sw_f2,Read_SW_F2_Level);                     //call fuction attach
  Button_Attach(&sw_f2,BUTTON_DOWN,SW_F2_Down_CallBack);             //call fuction attach
  Button_Create("ok",&sw_ok,Read_SW_OK_Level);                     //call fuction attach
  Button_Attach(&sw_ok,BUTTON_DOWN,SW_OK_Down_CallBack);             //call fuction attach
  Button_Create("f3",&sw_f3,Read_SW_F3_Level);                     //call fuction attach
  Button_Attach(&sw_f3,BUTTON_DOWN,SW_F3_Down_CallBack);             //call fuction attach 
  //fifth line
  Button_Create("n0",&sw_n0,Read_SW_N0_Level);                     //call fuction attach
  Button_Attach(&sw_n0,BUTTON_DOWN,SW_N0_Down_CallBack);             //call fuction attach
  Button_Create("f4",&sw_f4,Read_SW_F4_Level);                     //call fuction attach
  Button_Attach(&sw_f4,BUTTON_DOWN,SW_F4_Down_CallBack);             //call fuction attach
  Button_Create("dot",&sw_dot,Read_SW_DOT_Level);                     //call fuction attach
  Button_Attach(&sw_dot,BUTTON_DOWN,SW_DOT_Down_CallBack);             //call fuction attach 
  //six line
  Button_Create("n1",&sw_n1,Read_SW_N1_Level);                     //call fuction attach
  Button_Attach(&sw_n1,BUTTON_DOWN,SW_N1_Down_CallBack);             //call fuction attach
  Button_Create("n2",&sw_n2,Read_SW_N2_Level);                     //call fuction attach
  Button_Attach(&sw_n2,BUTTON_DOWN,SW_N2_Down_CallBack);             //call fuction attach
  Button_Create("n3",&sw_n3,Read_SW_N3_Level);                     //call fuction attach
  Button_Attach(&sw_n3,BUTTON_DOWN,SW_N3_Down_CallBack);             //call fuction attach  
  //seven line
  Button_Create("n4",&sw_n4,Read_SW_N4_Level);                     //call fuction attach
  Button_Attach(&sw_n4,BUTTON_DOWN,SW_N4_Down_CallBack);             //call fuction attach
  Button_Create("n5",&sw_n5,Read_SW_N5_Level);                     //call fuction attach
  Button_Attach(&sw_n5,BUTTON_DOWN,SW_N5_Down_CallBack);             //call fuction attach
  Button_Create("n6",&sw_n6,Read_SW_N6_Level);                     //call fuction attach
  Button_Attach(&sw_n6,BUTTON_DOWN,SW_N6_Down_CallBack);             //call fuction attach 
  //eighth line
  Button_Create("n7",&sw_n7,Read_SW_N7_Level);                     //call fuction attach
  Button_Attach(&sw_n7,BUTTON_DOWN,SW_N7_Down_CallBack);             //call fuction attach
  Button_Create("n8",&sw_n8,Read_SW_N8_Level);                     //call fuction attach
  Button_Attach(&sw_n8,BUTTON_DOWN,SW_N8_Down_CallBack);             //call fuction attach
  Button_Create("n9",&sw_n9,Read_SW_N9_Level);                     //call fuction attach
  Button_Attach(&sw_n9,BUTTON_DOWN,SW_N9_Down_CallBack);             //call fuction attach 
  //nine line
  Button_Create("sp",&sw_space,Read_SW_SPACE_Level);                     //call fuction attach
  Button_Attach(&sw_space,BUTTON_DOWN,SW_SPACE_Down_CallBack);             //call fuction attach
  Button_Create("stop",&sw_stop,Read_SW_STOP_Level);                     //call fuction attach
  Button_Attach(&sw_stop,BUTTON_DOWN,SW_STOP_Down_CallBack);             //call fuction attach
  //poto switch
  Button_Create("clr_s",&sw_clr,Read_SW_CLR_Level);                     //call fuction attach
  Button_Attach(&sw_clr,BUTTON_DOWN,SW_CLR_Down_CallBack);             //call fuction attach
  Button_Attach(&sw_clr,BUTTON_LONG,SW_CLR_LONG_CallBack);             //call fuction attach
  Button_Create("add_s",&sw_add,Read_SW_ADD_Level);                     //call fuction attach
  Button_Attach(&sw_add,BUTTON_DOWN,SW_ADD_Down_CallBack);             //call fuction attach
}


/******************************************
 * @description: 
 * @param {Button_t} *btn
 * @param {uint16_t} ms
 * @return {*}
******************************************/
void set_par_lever_timermax(Button_t *btn , uint16_t cnt)
{
  if(cnt < BUTTON_LEVEL_STABLE)
  {
    btn->level_timermax = BUTTON_LEVEL_STABLE;
  }
  else
  {
    btn->level_timermax = cnt;
  }
}
void set_par_long_timermax(Button_t *btn , uint16_t cnt)
{
  if(cnt >= 99990/BUTTON_CYCE - 20)
  {
    btn->long_timermax = UINT16_MAX;
  }
  else
  {
    btn->long_timermax = cnt;
  }
}
void set_par_longcyc_timermax(Button_t *btn , uint16_t cnt)
{
  btn->longcyc_timermax = cnt;
}
void set_par_sleep_timermax(Button_t *btn , uint16_t cnt)
{
  btn->sleep_timermax = cnt;
}
/* ------------------------------------------- funtion ----------------------------------------- */
//内部函数
/* ------------------------------------------- funtion ----------------------------------------- */
/************************************************************
  * @brief   按键周期处理函数
  * @param   btn:处理的按键
  * @return  NULL
  * @author  jiejie
  * @github  https://github.com/jiejieTop
  * @date    2018-xx-xx
  * @version v1.0
  * @note    必须以一定周期调用此函数，建议周期为20~50ms
  ***********************************************************/
void Button_Cycle_Process(Button_t *btn)
{
  uint8_t current_level = (uint8_t)btn->Read_Button_Level();
  //按键电平发生变化，消抖
    if((current_level != btn->Button_Last_Level)&&(++(btn->level_timercnt) > BUTTON_LEVEL_STABLE)) 
    {
        btn->Button_Last_Level = current_level; //更新当前按键电平
        btn->level_timercnt = 0;                 //确定了是按下
          
         //如果按键是没被按下的，改变按键状态为按下(首次按下/双击按下)
        if(btn->Button_State == NONE_TRIGGER && btn->Button_Last_Level == btn->Button_Trigger_Level)
        {
            btn->Button_State = BUTTON_DOWN;
        }
        //释放按键
        else if(btn->Button_State == BUTTON_DOWN)
        {
            btn->Button_State = BUTTON_UP;
        }
        //双击检测
   #if SINGLE_AND_DOUBLE_TRIGGER == 1
        else if(btn->Button_State == BUTTON_DOUBLE_WAIT)
        {
            btn->Button_State = BUTTON_DOWN;
        }
    #endif
    }
    else if(current_level == btn->Button_Last_Level)
    {
        //重置消抖寄存器
        btn->level_timercnt = 0;
    }
  
  switch(btn->Button_State)
  {
    case BUTTON_DOWN :            // 按下状态
    {
	    //按键按下电平和我们设置电平相一致时
        if(btn->Button_Last_Level == btn->Button_Trigger_Level) 
        {
            //连按
            #if CONTINUOS_TRIGGER     

            if(++(btn->cycle_timercnt) >= BUTTON_CONTINUOS_CYCLE)
            {
              btn->cycle_timercnt = 0;
              btn->Button_Trigger_Event = BUTTON_CONTINUOS; 
              TRIGGER_CB(BUTTON_CONTINUOS);    //连按
              //PRINT_DEBUG("连按");
            }
            
            #else	    
    	    //按下定时器计数
    	    btn->down_timecnt++;
    	    
    	    //单击
            if (btn->down_timecnt < BUTTON_LONG_TIME && btn->Button_Trigger_Event != BUTTON_DOUBLE_WAIT)
            {
                btn->Button_Trigger_Event = BUTTON_DOWN; 
            }
    	    //长按释放
            #if LONG_FREE_TRIGGER == 1
            else if(btn->Long_Time == BUTTON_LONG_TIME)     
            {
                btn->Button_Trigger_Event = BUTTON_LONG_FREE; 
            } 
            #else
    	    //长按
            else if(btn->down_timecnt == BUTTON_LONG_TIME)      //释放按键前更新触发事件为长按
            {
                btn->Button_Trigger_Event = BUTTON_LONG; 
                TRIGGER_CB(BUTTON_LONG);                //第一次长按
            }
            
            //长按后
            else if(btn->down_timecnt > BUTTON_LONG_TIME)
            {
                  if(++(btn->cycle_timercnt) >= BUTTON_LONG_CYCLE)    //连续触发长按的周期
                  {
                    btn->cycle_timercnt = 0;
                    btn->Button_Trigger_Event = BUTTON_LONG; 
                    TRIGGER_CB(BUTTON_LONG);                        //长按连续触发
                  }
             }
            #endif
            //更新按下计数器时间  
            if(btn->down_timecnt == 0xFF)  
            {
                //更新长按后
                btn->down_timecnt = BUTTON_LONG_TIME+1;
            }
        }
          
      #endif
    

      break;
    } 
    
    case BUTTON_UP :        // 弹起状态
    {
            //触发单击
            if(btn->Button_Trigger_Event == BUTTON_DOWN)  
            {
                //单击
            #if (SINGLE_AND_DOUBLE_TRIGGER == 0)
                TRIGGER_CB(BUTTON_DOWN);    
                btn->down_timecnt=0;
                btn->Button_State = NONE_TRIGGER;
                btn->Button_Trigger_Event = NONE_TRIGGER;
            #else
                //双击检测
                if(btn->Button_Trigger_Event = BUTTON_DOWN)
                {
                    btn->down_timecnt=0;
                    btn->cycle_timercnt = 0;
                    btn->double_timecnt = 0;
                    btn->Button_State = BUTTON_DOUBLE_WAIT;
                    btn->Button_Trigger_Event = BUTTON_DOUBLE_WAIT;
                }
                esle if(btn->Button_Trigger_Event = BUTTON_DOUBLE_WAIT)
                {
                    //双击检测
                    btn->down_timecnt=0;
                    btn->cycle_timercnt = 0;
                    btn->double_timecnt = 0;
                    TRIGGER_CB(BUTTON_DOUBLE); 
                    btn->Button_Last_State = BUTTON_DOUBLE;
                    btn->Button_State = NONE_TRIGGER;
                    btn->Button_Trigger_Event = NONE_TRIGGER;
                }
            #endif 
            }
            else if(btn->Button_Trigger_Event == BUTTON_CONTINUOS)
            {
                btn->down_timecnt = 0;
                btn->cycle_timercnt = 0;
                //在按下那边已经触发了
                btn->Button_State = NONE_TRIGGER;
                btn->Button_Trigger_Event = NONE_TRIGGER;

            }
            //长按
            else if(btn->Button_Trigger_Event == BUTTON_LONG)
            {
                TRIGGER_CB(BUTTON_LONG_FREE);
                btn->down_timecnt = 0;
                btn->cycle_timercnt = 0;
                //在按下那边已经触发了
                btn->Button_State = NONE_TRIGGER;
                btn->Button_Trigger_Event = NONE_TRIGGER;
            }
            #if LONG_FREE_TRIGGER == 1
            //长按释放
            else if(btn->Button_Trigger_Event == BUTTON_LONG_FREE)
            {
                TRIGGER_CB(BUTTON_LONG_FREE);
                btn->down_timecnt = 0;
                btn->cycle_timercnt = 0;
                //在按下那边已经触发了
                btn->Button_Last_State = BUTTON_LONG_FREE;
                btn->Button_State = NONE_TRIGGER;
                btn->Button_Trigger_Event = NONE_TRIGGER;
            }
            #endif
            #if CONTINUOS_TRIGGER
            else if(btn->Button_Trigger_Event == BUTTON_CONTINUOS)  //连按
            {
              btn->Long_Time = 0;
              TRIGGER_CB(BUTTON_CONTINUOS_FREE);    //连发释放
              btn->Button_State = NONE_TRIGGER;
              btn->Button_Last_State = BUTTON_CONTINUOS;
            } 
            #endif
      
      break;
    }
    //双击检测
    #if (SINGLE_AND_DOUBLE_TRIGGER == 1)
    case BUTTON_DOUBLE_WAIT :		//双击中间间隔的超时判断
    {
        btn->double_timecnt++;     //时间记录 
        //超时
        if(btn->double_timecnt>=BUTTON_DOUBLE_TIME)
        {
            btn->double_timecnt = 0;
            btn->Button_Trigger_Event = BUTTON_DOWN;
            TRIGGER_CB(BUTTON_DOWN);
            btn->Button_State = NONE_TRIGGER;
            btn->Button_Trigger_Event = NONE_TRIGGER;
        }
      break;
    }
    #endif

    
    default :
      break;
  }

}
/******************************************
 * @description: 
 * @param {Button_t} *btn
 * @return {*}
******************************************/
void Button_Cycle_Process_add(Button_t *btn)
{
  if(btn->Button_State == BUTTON_SLEEP)
  {
    btn->sleep_timecnt ++;
    if(btn->sleep_timecnt < btn->sleep_timermax)
    {
      return;
    }
    else
    {
      btn->Button_State = NONE_TRIGGER;
    }
  }
  //upadta level state
  uint8_t current_level = (uint8_t)btn->Read_Button_Level();
  //rise
  if(btn->Button_Last_Level == LOW && current_level == HIGHT)
  {
    btn->level_timercnt++;
    if(btn->level_timercnt > btn->level_timermax)
    {
      btn->Button_Last_Level = current_level;
      btn->level_timercnt = 0;
      btn->Button_State   = BUTTON_DOWN;
    }
  }
  //fall
  else if(btn->Button_Last_Level == HIGHT && current_level == LOW)
  {
    btn->level_timercnt++;
    if(btn->level_timercnt > BUTTON_LEVEL_STABLE)
    {
      btn->Button_Last_Level = current_level;
      btn->level_timercnt = 0;
      btn->Button_State   = BUTTON_UP;
    }
  }
  //other
  else if(current_level == btn->Button_Last_Level)
  {
    btn->level_timercnt = 0;
  }
  
  switch(btn->Button_State)
  {
    case BUTTON_DOWN :           
      //按下定时器计数
      if(btn->down_timecnt <= btn->long_timermax)
      {
        btn->down_timecnt++;   
        if(btn->long_timermax == UINT16_MAX && btn->down_timecnt > INT16_MAX)
        {
            btn->down_timecnt = INT16_MAX;
        }
      }
      //单击
      if (btn->down_timecnt < btn->long_timermax)
      {
        btn->Button_Trigger_Event = BUTTON_DOWN; 
      }
      //长按
      else if(btn->down_timecnt == btn->long_timermax)      //释放按键前更新触发事件为长按
      {
        btn->Button_Trigger_Event = BUTTON_LONG; 
        TRIGGER_CB(BUTTON_DOWN);                //第一次长按
      }            
      //长按后
      else if(btn->down_timecnt > btn->long_timermax)
      {
        btn->cycle_timercnt++;
        if(btn->cycle_timercnt >= btn->longcyc_timermax)    //连续触发长按的周期
        {
          btn->cycle_timercnt = 0;
          btn->Button_Trigger_Event = BUTTON_LONG; 
          TRIGGER_CB(BUTTON_DOWN);                        //长按连续触发
        }
      }
      break;

    case BUTTON_UP :        // 弹起状态
      //触发单击
      if(btn->Button_Trigger_Event == BUTTON_DOWN)  
      {
          //单击
          TRIGGER_CB(BUTTON_DOWN);    
      }
      if(btn->Button_Trigger_Event == BUTTON_LONG)  
      {
        if(btn->cycle_timercnt > btn->longcyc_timermax*0.7)
          TRIGGER_CB(BUTTON_DOWN);    
      }      
      btn->sleep_timecnt = 0;
      btn->cycle_timercnt = 0;
      btn->down_timecnt=0;
      btn->Button_State = BUTTON_SLEEP;
      btn->Button_Trigger_Event = NONE_TRIGGER;
      break;
    default :
      break;
  }

}
/**************************************************************************************************
* function	:                                   Button_Process
* brief	:  			   scan each button and each button's each button event
* param	:  			   none
* return			:  none
* author			:  rinanfang  3/2/2020
**************************************************************************************************/
void Button_Process(void)
{
  struct button* pass_btn;
  for(pass_btn = Head_Button; pass_btn != NULL; pass_btn = pass_btn->Next)
  {
      if(pass_btn == &sw_add)
      {
        Button_Cycle_Process_add(pass_btn);
      }
      else
      {
        Button_Cycle_Process(pass_btn);
      }
  }
}

/**************************************************************************************************
* function	:                                   Add_Button
* brief	:   add button node to button linear list
* param	:  button node
* return			:  none
* author			:  rinanfang  3/2/2020
**************************************************************************************************/
void Add_Button(Button_t* btn)
{
  struct button *pass_btn = Head_Button;
  
  while(pass_btn)
  {
    pass_btn = pass_btn->Next;
  }
  
  btn->Next = Head_Button;
  Head_Button = btn;
}

/**************************************************************************************************
* function	:                                   Button_Delete
* brief	:  delete button node from button linear list
* param	:  button node
* return			:  none
* author			:  rinanfang  3/2/2020
**************************************************************************************************/
void Button_Delete(Button_t *btn)
{
  struct button** curr;
  for(curr = &Head_Button; *curr;) 
  {
    struct button* entry = *curr;
    if (entry == btn) 
    {
      *curr = entry->Next;
    } 
    else
    {
      curr = &entry->Next;
    }
  }
}
/**************************************************************************************************
* function	:                                   Button_Create
* brief	:  create a new button nod and add it to button linear list
* param	:  button name||button node||button level||button trigger level		
* return			:  TRUE FALSE
* author			:  rinanfang  3/2/2020
**************************************************************************************************/
boolean_t Button_Create(const char *name,Button_t *btn,uint8_t(*read_btn_level)(void))
{
  if( btn == NULL)
  {
	  return FALSE;
  }
  //"string.h"
  memset(btn, 0, sizeof(struct button));  //
  StrnCopy(btn->Name, name, BTN_NAME_MAX);
  
  //set button param to no trigger status
  btn->Button_State = NONE_TRIGGER;           //按键状态
  btn->Button_Trigger_Event = NONE_TRIGGER;   //按键触发事件
  btn->Read_Button_Level = read_btn_level;    //按键读电平函数
//	  btn->Button_Trigger_Level = HIGHT;  //按键触发电平
//	  btn->Button_Last_Level = LOW; 			//按键当前电平
  btn->Button_Trigger_Level = HIGHT;  //按键触发电平
  btn->Button_Last_Level = btn->Read_Button_Level(); //按键当前电平
	//debug_printf("btn:%d",btn->Button_Last_Level);
  btn->level_timercnt   = 0;
	btn->level_timermax   = BUTTON_LEVEL_STABLE;
  btn->long_timermax    = BUTTON_LONG_TIME;
  btn->longcyc_timermax = BUTTON_LONG_CYCLE;
  //add to line tabe
  Add_Button(btn);          //add button line
  
  return TRUE;
}

/**************************************************************************************************
* function	:                                   Button_Attach
* brief	:		attach button event to  corresponding button node
* param	:  		button node||button event's array idex||button event's callback
* return			:  TRUE FALSE
* author			:  rinanfang  3/2/2020
**************************************************************************************************/
boolean_t Button_Attach(Button_t *btn,Button_Event btn_event,Button_CallBack btn_callback)
{
  uint8_t i=0;
  if( btn == NULL)
  {
	  return FALSE;
  }
  
  if(BUTTON_ALL_RIGGER == btn_event)
  {
    for( i = 0 ; i < number_of_event-1 ; i++)
      btn->CallBack_Function[i] = btn_callback; //
  }
  else
  {
    btn->CallBack_Function[btn_event] = btn_callback; //
  }
  return TRUE;
}

/**************************************************************************************************
* function	:                                   StrnCopy
* brief	:  
* param	:  dst str || src str || str line
* return			:  dst str 
* author			:  rinanfang  3/2/2020
**************************************************************************************************/
static char *StrnCopy(char *dst, const char *src, uint32_t n)
{
  if (n != 0)
  {
    char *d = dst;
    const char *s = src;
    do
    {
        if ((*d++ = *s++) == 0)
        {
            while (--n != 0)
                *d++ = 0;
            break;
        }
    } while (--n != 0);
  }
  return (dst);
}



