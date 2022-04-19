
/**************************************************************************************************
* 文件:  button.h
*        
* 说明:  
*        
* 作者:  rinanfang  3/2/2020
**************************************************************************************************/
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "base_typle.h"
// 标准库头文件 
#include <stdint.h>
#include <string.h>
//FreeRTOS头文件
#include "FreeRTOS.h"
#include "task.h"
// 芯片驱动头文件 
// bsp头文件 


//==================================modify define/typedef/enum=================================
#ifndef TRUE
	#define TRUE 1
#endif
#ifndef FALSE
	#define FALSE 0
#endif
#ifndef HIGHT
	#define HIGHT 1
#endif
#ifndef LOW
	#define LOW 0
#endif
#ifndef NULL
	#define NULL 0
#endif
//==============================================================================================

///修改
//SELECT        SW0 PC12
//RANGE         SW1 PA15
//REL/HZ/BT     SW2 PD07
//HOLD/LIGHT    SW3 PD06
// #define SW0PORT GPIOE
// #define SW0PIN  GPIO_Pin_4

// #define SW1PORT GPIOE
// #define SW1PIN  GPIO_Pin_3

// #define SW2PORT GPIOE
// #define SW2PIN  GPIO_Pin_2

// #define SW3PORT GPIOA
// #define SW3PIN  GPIO_Pin_0


// //Get button leve 
// #define GetSW0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
// #define GetSW1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)	//PE3 
// #define GetSW2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) //PE2
// #define GetSW3 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//PA0

/* 	按键消抖时间40ms, 建议调用周期为20ms
 	只有连续检测到40ms状态不变才认为有效，包括弹起和按下两种事件*/
#define BUTTON_CYCE 				 20

#define CONTINUOS_TRIGGER             0  //是否支持连续触发，连发的话就不要检测单双击与长按了	
/* 	是否支持单击&双击同时存在触发，如果选择开启宏定义的话，单双击都回调，只不过单击会延迟响应，
   	因为必须判断单击之后是否触发了双击否则，延迟时间是双击间隔时间 BUTTON_DOUBLE_TIME。
   	而如果不开启这个宏定义，建议工程中只存在单击/双击中的一个，否则，在双击响应的时候会触发一次单击，
   	因为双击必须是有一次按下并且释放之后才产生的 */
#define SINGLE_AND_DOUBLE_TRIGGER     0

/* 是否支持长按释放才触发，如果打开这个宏定义，那么长按释放之后才触发单次长按，
   否则在长按指定时间就一直触发长按，触发周期由 BUTTON_LONG_CYCLE 决定 */
#define LONG_FREE_TRIGGER             0 

#define BUTTON_LEVEL_STABLE 	  	40/BUTTON_CYCE   	//消抖时间      (1)*调用周期
#define BUTTON_LONG_TIME 	      	5000/BUTTON_CYCE		/* 持续n秒((n-1)*调用周期 ms)，认为长按事件 */
#define BUTTON_LONG_CYCLE       	5000/BUTTON_CYCE		//长按触发周期时间  (n-1)*调用周期 

#define BUTTON_CONTINUOS_CYCLE  	1	  									//连按触发周期时间  (n-1)*调用周期  
#define BUTTON_DOUBLE_TIME      	15 		//双击间隔时间  (n-1)*调用周期  建议在200-600ms



//=====================================按键================================================

#define BTN_NAME_MAX  10

//btn->CallBack_Function[event]是的函数的指针。简称函数指针数组。    
#define TRIGGER_CB(event)   \
        if(btn->CallBack_Function[event]) \
			btn->CallBack_Function[event]((Button_t*)btn)
//function pointer
typedef void (*Button_CallBack)(void*);

//trigger event array
typedef enum {
  BUTTON_DOWN = 0,
  BUTTON_UP,
  BUTTON_DOUBLE_WAIT,
  BUTTON_DOUBLE,
  BUTTON_LONG,
  BUTTON_LONG_FREE,
  BUTTON_CONTINUOS,
  BUTTON_SLEEP,
  //这个没写
  BUTTON_CONTINUOS_FREE,
  BUTTON_ALL_RIGGER,
  number_of_event,
  NONE_TRIGGER,
}Button_Event;

//每个按键对应1个全局的结构体变量。其成员变量是实现滤波和多种按键状态所必须的
typedef struct button
{
	/* 下面是一个函数指针，指向判断按键手否按下的函数 */
  	uint8_t (*Read_Button_Level)(void); /* 读取按键电平函数，需要用户实现 */
  
  	char Name[BTN_NAME_MAX];
  	
  	uint8_t Button_State				    ;	 	/* 按键当前状态（按下还是弹起） */
  	uint8_t Button_Trigger_Level      :   2 ;    	/* 按键触发电平 */
  	uint8_t Button_Last_Level         :   2 ;    	/* 按键当前电平 */
  
  	uint8_t Button_Trigger_Event;     				/* 按键触发事件，单击，双击，长按等 */
  
  	Button_CallBack CallBack_Function[number_of_event];	/*这是一组函数指针数组，用于存放触发事件的函数头地址*/
  
	uint16_t cycle_timercnt;	           				// 连续触发计数
  	uint16_t level_timercnt;						    // 电平消抖计时 
	uint16_t double_timecnt;						    // 双击间隔计数 
	uint16_t down_timecnt;		  					// 按键按下持续计数 
	uint16_t sleep_timecnt;

	uint16_t level_timermax;
	uint16_t long_timermax;
	uint16_t longcyc_timermax;
	uint16_t sleep_timermax;

  	struct button *Next;
}Button_t;

/* ------------------------------------------- varivable ----------------------------------------- */
#ifdef __BUTTON_C__
	#define BUTTON_EXT
#else
	#define BUTTON_EXT		extern
#endif

//按键单链表
static     Button_t*    Head_Button;
BUTTON_EXT Button_t 	sw_off;
BUTTON_EXT Button_t 	sw_edit;
BUTTON_EXT Button_t		sw_typle;
BUTTON_EXT Button_t 	sw_meter;
BUTTON_EXT Button_t 	sw_step;
BUTTON_EXT Button_t 	sw_del;
BUTTON_EXT Button_t 	sw_f1;
BUTTON_EXT Button_t 	sw_time;
BUTTON_EXT Button_t 	sw_f2;
BUTTON_EXT Button_t 	sw_ok;
BUTTON_EXT Button_t 	sw_f3;
BUTTON_EXT Button_t 	sw_n0;
BUTTON_EXT Button_t 	sw_f4;
BUTTON_EXT Button_t 	sw_dot;
BUTTON_EXT Button_t 	sw_n1;
BUTTON_EXT Button_t 	sw_n2;
BUTTON_EXT Button_t 	sw_n3;
BUTTON_EXT Button_t 	sw_n4;
BUTTON_EXT Button_t 	sw_n5;
BUTTON_EXT Button_t 	sw_n6;
BUTTON_EXT Button_t 	sw_n7;
BUTTON_EXT Button_t 	sw_n8;
BUTTON_EXT Button_t 	sw_n9;
BUTTON_EXT Button_t 	sw_space;
BUTTON_EXT Button_t 	sw_stop;
BUTTON_EXT Button_t 	sw_clr;
BUTTON_EXT Button_t 	sw_add;

/* ------------------------------------------- funtion ----------------------------------------- */


extern void set_switch_code(uint8_t code);
extern void set_par_lever_timermax(Button_t *btn , uint16_t ms);
extern void set_par_long_timermax(Button_t *btn , uint16_t ms);
extern void set_par_longcyc_timermax(Button_t *btn , uint16_t ms);
extern void set_par_sleep_timermax(Button_t *btn , uint16_t cnt);
/* externs */
extern void Add_Button (Button_t* btn);
extern void buttonAttachInit (void);
extern void buttonIrqForRouseInit (void);
extern void buttonStaInit (void *btn);
extern boolean_t Button_Attach (Button_t *btn, Button_Event btn_event, Button_CallBack btn_callback);
extern boolean_t Button_Create (const char *name, Button_t *btn, uint8_t (*read_btn_level) (void));
extern void Button_Cycle_Process (Button_t *btn);
extern void Button_Delete (Button_t *btn);
extern void Button_Process (void);
extern void SW0_Down_CallBack (void *btn);
extern void SW0_Long_CallBack (void *btn);
extern void SW1_Down_CallBack (void *btn);
extern void SW1_Long_CallBack (void *btn);



extern void set_matrix_button_code(uint64_t code);

/* static function pre-declared */
static char *StrnCopy (char *dst, const char *src, uint32_t n);









                  
#endif /*  __BUTTON_H__  */
