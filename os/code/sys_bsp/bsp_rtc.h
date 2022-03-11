/************************************************** 
 * @Author: shuren
 * @Date: 2022-03-02 14:07:23
 * @LastEditTime: 2022-03-02 14:07:24
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_bsp\bsp_rtc.h
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#ifndef _BSP_RTC_H_
#define _BSP_RTC_H_
#include "base_typle.h"

int64_t decode_rtc_cnt(uint32_t cnt);
uint32_t encoding_rtc();
void rtc_configuration(void);
void time_adjust(void);
void rtc_init();
void RTC_IRQHandler(void);

#endif