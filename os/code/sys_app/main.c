/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-17 15:08:45
 * @LastEditTime: 2022-03-04 22:03:33
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_app\main.c
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/


/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "my_print.h"
#include "button.h"
#include "remote.h"
#include "remote1.h"
#include "dhtc12_sensor.h"
#include "gd32f30x.h"
#include "bsp_i2c.h"
#include "main.h"
#include "hc595.h"
#include "disp.h"

int32_t sta;
/*
*************************************************************************
*                        函数声明&&任务句柄
*************************************************************************
*/
extern void bsp_init();/* 用于初始化板载相关资源 */
/* 用于创建任务 */
static TaskHandle_t AppTaskCreate_Handle = NULL;
static void AppTaskCreate(void);


static TaskHandle_t button_task_handle = NULL;
static void button_task(void* pvParameters);

static TaskHandle_t dhtc12_task_handle = NULL;
static void dhtc12_task(void* pvParameters);

static TaskHandle_t nixie_tube_task_handle = NULL;
static void nixie_tube_task(void* pvParameters);

int main()
{
  BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	
  /* 开发板硬件初始化 */
  bsp_init();
//  while (1)
//  {
//    uint64_t i;
//    for(i=0;i<10000;i++);
//    SCL_H();
//    for(i=0;i<10000;i++);
//    SCL_L();
//  }
  
/* 创建AppTaskCreate任务 */
  xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  /* 任务入口函数 */
                        (const char*    )"AppTaskCreate",/* 任务名字 */
                        (uint16_t       )512,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )1, /* 任务的优先级 */
                        (TaskHandle_t*  )&AppTaskCreate_Handle);/* 任务控制块指针 */ 
  /* 启动任务调度 */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* 启动任务，开启调度 */
  else
    return -1;  

  while(1);   /* 正常不会执行到这里 */    
}
/***********************************************************************
  * @ 函数名  ： AppTaskCreate
  * @ 功能说明： 为了方便管理，所有的任务创建函数都放在这个函数里面
  * @ 参数    ： 无  
  * @ 返回值  ： 无
  **********************************************************************/
static void AppTaskCreate(void)
{
  BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
  
  taskENTER_CRITICAL();           //进入临界区
  
  xReturn = xTaskCreate((TaskFunction_t )button_task, /* 任务入口函数 */
                        (const char*    )"button_task",/* 任务名字 */
                        (uint16_t       )128,   /* 任务栈大小 */
                        (void*          )NULL,	/* 任务入口函数参数 */
                        (UBaseType_t    )5,	    /* 任务的优先级 */
                        (TaskHandle_t*  )&button_task_handle);/* 任务控制块指针 */
  xReturn = xTaskCreate((TaskFunction_t )dhtc12_task, /* 任务入口函数 */
                        (const char*    )"dhtc12_task",/* 任务名字 */
                        (uint16_t       )128,   /* 任务栈大小 */
                        (void*          )NULL,	/* 任务入口函数参数 */
                        (UBaseType_t    )4,	    /* 任务的优先级 */
                        (TaskHandle_t*  )&dhtc12_task_handle);/* 任务控制块指针 */
 xReturn = xTaskCreate((TaskFunction_t )nixie_tube_task, /* 任务入口函数 */
                        (const char*    )"nixie_tube_task",/* 任务名字 */
                        (uint16_t       )128,   /* 任务栈大小 */
                        (void*          )NULL,	/* 任务入口函数参数 */
                        (UBaseType_t    )5,	    /* 任务的优先级 */
                        (TaskHandle_t*  )&nixie_tube_task_handle);/* 任务控制块指针 */
  if(pdPASS == xReturn)NULL;
  vTaskDelete(AppTaskCreate_Handle); //删除AppTaskCreate任务
  //hc595_send_data(unsigned char data)
  taskEXIT_CRITICAL();            //退出临界区
}
static void button_task(void* pvParameters)
{
		int32_t key;
//  用于保存上次时间。调用后系统自动更新
    static portTickType PreviousWakeTime; 
//  设置延时时间，将时间转为节拍数 
    const portTickType TimeIncrement = pdMS_TO_TICKS(BUTTON_CYCE); 
//  获取当前系统时间  
    PreviousWakeTime = xTaskGetTickCount(); 
    while(1)
    {
//=========================同步部分==================================== 
        vTaskDelayUntil( &PreviousWakeTime,TimeIncrement ); 
//=========================主体部分====================================
        //按键函数
				key = remote1_scan();
				if(remote_scan() != -1)
				{
					key = remote_scan();
				}
				set_matrix_button_code(key);
        Button_Process();
//				PRINT("key_cod,%x\n",get_remote_code());
//				PRINT("key1_cod,%x\n",get_remote1_code());
//				PRINT("keyf_cod,%x\n",key);
    }
}

/****************************************** 
 * @description: 
 * @param {void*} pvParameters
 * @return {*}
 ******************************************/
static void dhtc12_task(void* pvParameters)
{
		//Absolute time delay
    static portTickType PreviousWakeTime; 
    const portTickType TimeIncrement = pdMS_TO_TICKS(2000); 
    PreviousWakeTime = xTaskGetTickCount(); 
		//dhtc init
		int16_t tem_data;
		uint16_t hum_data;
		dhtc12_init();
    while(1)
    {
			//time synchronization 
      vTaskDelayUntil( &PreviousWakeTime,TimeIncrement);    
			//dhtc read			
			dhtc12_read_all(&tem_data, &hum_data);
      hum.data = hum_data;
      tem.data = tem_data;
			PRINT("dhtc:%d,%d,%d,%d\n",get_humA(),get_humB(),tem.data,hum.data);
    }
}
/****************************************** 
 * @description: 
 * @param {void*} pvParameters
 * @return {*}
 ******************************************/
static void nixie_tube_task(void* pvParameters)
{
  static portTickType PreviousWakeTime; 
  const portTickType TimeIncrement = pdMS_TO_TICKS(500); 
  PreviousWakeTime = xTaskGetTickCount();
  while(1)
  {
    vTaskDelayUntil( &PreviousWakeTime,TimeIncrement);    
    disp_refresh_task();
  }
}
