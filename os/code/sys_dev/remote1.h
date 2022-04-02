/****************************************** 
 * @Author: your name
 * @Date: 2022-03-24 22:02:45
 * @LastEditTime: 2022-03-24 22:06:50
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \GD32F303\code\sys_dev\remote2.c
 ******************************************/


#ifndef _REMOTE_H_
#define _REMOTE_H_
#include "base_typle.h"



	   

void remote_timer3ch2_init();
static void time3ch2_capture_rise_init();
static void time3ch2_capture_fall_init();
static void remote_var_init();
int32_t get_remote1_code();
int32_t remote1_scan(void);
void TIMER3_IRQHandler(void);

#endif

