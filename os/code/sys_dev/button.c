/**************************************************************************************************
* fuction	:                              button     
* file		:  button.c     
* brief		:     
* author	: rinanfang  3/2/2020
**************************************************************************************************/

#define __BUTTON_C__
/* ------------------------------------------- include ----------------------------------------- */
#include "button.h"
#include "main.h"
#include "disp.h"

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
/**************************************************************************************************
*                                 SW call back
**************************************************************************************************/
void SW_OFF_Down_CallBack(void *btn)
{  
  switch (sta)
  {
      default:
      case STA_NORMAL:
        sta = STA_OFF;
        clear_button_stack();
        set_link_head(NULL);
        break;
      case STA_OFF:
        sta = STA_NORMAL;
        disp_all_link();
        break;
      case STA_EDIT2:
      case STA_EDIT:
          syn_disp_store2data();
          sta = STA_NORMAL;
          disp_all_link();
          break;
      case STA_COMPENSATION:
      case STA_TIME:
          syn_disp_store2data();
          sta = STA_NORMAL;
          disp_all_link();
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
          accum_yield.flash  = FLASH_ALL;
          break;
  }
}
void SW_TYPLE_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_TIME:
          if(out_button_stack() == STA_OFF) {
            sta = STA_CLEAR_TIME;
          }
          break;
      case STA_NORMAL:
        sta = STA_COMPENSATION;
        set_link_head(&tem);
        add_link_node(&hum);
        cover_disp_permission(TRUE);
        cover_disp_flash(FLASH_NULL);
        cur_p->flash = 1;
        break;
  }
}
void SW_METER_Down_CallBack(void *btn)
{
  switch (0)
  {
      default:
      case 0:
          buttonStaInit(btn);
          break;
  }
}
void SW_STEP_Down_CallBack(void *btn)
{
  switch (0)
  {
      default:
      case 0:
          buttonStaInit(btn);
          break;
  }
}
void SW_DEL_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_NORMAL:
        sta = STA_EDIT2;
        set_link_head(&accum_yield);
        add_link_node(&cur_yield_rear);
        add_link_node(&next_glue_up);
        add_link_node(&next_glue_dowm);
        cover_disp_permission(TRUE);
        cover_disp_flash(FLASH_NULL);
        accum_yield.flash  = FLASH_ALL;        
        break;
      case STA_EDIT2:
      case STA_COMPENSATION:
      case STA_EDIT:
          cur_p->disp = 0;
          break;
  }
}
void SW_F1_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_EDIT2:
      case STA_EDIT:
          cur_p->flash = FLASH_NULL;
          cur_p = cur_p->prev;
          cur_p->flash = FLASH_ALL;
          break;
      case STA_COMPENSATION:
        cur_p->flash = FLASH_NULL;
        cur_p = cur_p->prev;
        cur_p->flash = 1;
        break;
  }
}
void SW_TIME_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_OFF: 
        in_button_stack(STA_OFF);
        sta = STA_TIME;
        set_link_head(&time);
        cover_disp_permission(TRUE);
        cover_disp_flash(FLASH_NULL);
        cur_p->flash  = 12;
        break;
      case STA_NORMAL:
          sta = STA_TIME;
          set_link_head(&time);
          cover_disp_permission(TRUE);
          cover_disp_flash(FLASH_NULL);
          cur_p->flash  = 12;
          break;
  }
}
void SW_F2_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_TIME:
          cur_p->flash++;
          if(cur_p->flash > cur_p->position_max) cur_p->flash = 0;
          break;
      case STA_COMPENSATION:
          if(cur_p->disp > 0) cur_p->disp=-cur_p->disp;
          break;  
  }
}
void SW_OK_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_EDIT2:
      case STA_COMPENSATION:
      case STA_EDIT:
          //syn_disp_data2store();
          disp_write_store();
          store_sy

            


            
          sta = STA_NORMAL;
          break;
      case STA_TIME:
          if(cur_p->disp%100>60 || cur_p->disp/100%100>60)
          {
            syn_disp_store2data();
          }else if(cur_p->disp/10000%100>31 || cur_p->disp/1000000%100>12)
          {
            syn_disp_store2data();
          }else if(cur_p->disp/100000000%10000<2020 || cur_p->disp/100000000%10000>5000)
          {
            syn_disp_store2data();
          }else{
            syn_disp_data2store();
            disp_write_store();
          }
          disp_all_link();
          sta = STA_NORMAL;
          break;
  }
}
void SW_F3_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_COMPENSATION:
          if(cur_p->disp < 0) cur_p->disp=-cur_p->disp;
          break;
      case STA_TIME:
          cur_p->flash--;
          if(cur_p->flash <= 0) cur_p->flash = cur_p->position_max;
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
      case STA_EDIT2:
      case STA_EDIT:
          cur_p->disp = cur_p->disp *10;
          if(cur_p->disp>cur_p->data_max)cur_p->disp=cur_p->disp%(cur_p->data_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 0);
          break;      
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 0);
          break;
  }
}
void SW_F4_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_EDIT2:
      case STA_EDIT:
          cur_p->flash = FLASH_NULL;
          cur_p = cur_p->next;
          cur_p->flash = FLASH_ALL;
          break;
      case STA_COMPENSATION:
          cur_p->flash = FLASH_NULL;
          cur_p = cur_p->next;
          cur_p->flash = 1;
        break;
  }
}
void SW_DOT_Down_CallBack(void *btn)
{
}
void SW_N1_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_EDIT2:
      case STA_EDIT:
          cur_p->disp = cur_p->disp*10+1;
          if(cur_p->disp>cur_p->data_max)cur_p->disp=cur_p->disp%(cur_p->data_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 1);
          break;      
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 1);
          break;
  }
}
void SW_N2_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_EDIT2:
      case STA_EDIT:
          cur_p->disp = cur_p->disp*10+2;
          if(cur_p->disp>cur_p->data_max)cur_p->disp=cur_p->disp%(cur_p->data_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 2);
          break;      
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 2);
          break;
  }
}
void SW_N3_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_EDIT2:
      case STA_EDIT:
          cur_p->disp = cur_p->disp*10+3;
          if(cur_p->disp>cur_p->data_max)cur_p->disp=cur_p->disp%(cur_p->data_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 3);
          break;      
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 3);
          break;
  }
}
void SW_N4_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_EDIT2:
      case STA_EDIT:
          cur_p->disp = cur_p->disp*10+4;
          if(cur_p->disp>cur_p->data_max)cur_p->disp=cur_p->disp%(cur_p->data_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 4);
          break;      
       case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 4);
          break;
  }
}
void SW_N5_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_EDIT2:
      case STA_EDIT:
          cur_p->disp = cur_p->disp*10+5;
          if(cur_p->disp>cur_p->data_max)cur_p->disp=cur_p->disp%(cur_p->data_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 5);
          break;      
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 5);
          break;
  }
}
void SW_N6_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_EDIT2:
      case STA_EDIT:
          cur_p->disp = cur_p->disp*10+6;
          if(cur_p->disp>cur_p->data_max)cur_p->disp=cur_p->disp%(cur_p->data_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 6);
          break;      
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 6);
          break;
  }
}
void SW_N7_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_EDIT2:
      case STA_EDIT:
          cur_p->disp = cur_p->disp*10+7;
          if(cur_p->disp>cur_p->data_max)cur_p->disp=cur_p->disp%(cur_p->data_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 7);
          break;      
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 7);
          break;
  }
}
void SW_N8_Down_CallBack(void *btn)
{
  switch (sta)
  {
      default:
      case STA_EDIT2:
      case STA_EDIT:
          cur_p->disp = cur_p->disp*10+8;
          if(cur_p->disp>cur_p->data_max)cur_p->disp=cur_p->disp%(cur_p->data_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 8);
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
      case STA_EDIT2:
      case STA_EDIT:
          cur_p->disp = cur_p->disp*10+9;
          if(cur_p->disp>cur_p->data_max)cur_p->disp=cur_p->disp%(cur_p->data_max+1);
          break;
      case STA_COMPENSATION:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 9);
          break;          
      case STA_TIME:
          cur_p->disp = set_data(cur_p->disp, cur_p->flash, 9);
          break;
  }
}
void SW_SPACE_Down_CallBack(void *btn)
{
}
void SW_STOP_Down_CallBack(void *btn)
{
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

}

/**************************************************************************************************
* 函数:                                   mstaVarIni
* 说明:   修改函数状态转移初始化
**************************************************************************************************/
void buttonStaInit(void *btn)
{
	
}

/* -------------------------------------------sw down callback ----------------------------------------- */
//修改按键逻辑
/* ----------------------------------------------------------------------------------------------------- */
static void buttonRecord(SW_RECORDCODING_E btn_coding)
{
    //记录按键
    if (btn_coding == SW0_DOWN )
    {
        memset((void *)&sw_record, 0, sizeof(sw_record));
    }
    sw_record.bin[sw_record.i++] = btn_coding;
    if (sw_record.i > BTNRECORDMAX)
    {
        sw_record.i = 0;
    }
    
    //校准
    if (FALSE)
    {
        //清空密码
        memset((void *)&sw_record, 0, sizeof(sw_record));       
    }
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
      Button_Cycle_Process(pass_btn);
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
  btn->level_timercnt = 0;
	
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



