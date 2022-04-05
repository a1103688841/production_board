/******************************************
 * @Author: rnf
 * @Date: 2022-04-05 19:19:44
 * @LastEditTime: 2022-04-05 21:08:34
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board\os\code\sys_bsp\bsp_rtc.h
 * @rnf wrote this code
******************************************/
#ifndef _BSP_RTC_H_
#define _BSP_RTC_H_
#include "base_typle.h"

int64_t decode_rtc_cnt(uint32_t cnt);
uint32_t encoding_rtc(int64_t time);
boolean_t cheak_rtc(int64_t time);
void rtc_configuration(void);
void time_adjust(int64_t time);
void rtc_init();
void RTC_IRQHandler(void);


#endif
