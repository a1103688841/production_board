/****************************************** 
 * @Author: your name
 * @Date: 2022-02-19 16:06:10
 * @LastEditTime: 2022-03-24 22:08:39
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \GD32F303\code\sys_dev\remote.h
 ******************************************/
#ifndef _REMOTE_H_
#define _REMOTE_H_
#include "base_typle.h"



	   

void remote_timer2ch1_init();
static void time2ch1_capture_rise_init();
static void time2ch1_capture_fall_init();
static void remote_var_init();
int32_t get_remote_code();
int32_t remote_scan(void);
void TIMER2_IRQHandler(void);

#endif
