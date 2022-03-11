/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-19 16:06:10
 * @LastEditTime: 2022-02-27 20:36:12
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_dev\remote.h
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#ifndef _REMOTE_H_
#define _REMOTE_H_
#include "base_typle.h"

#define REMOTE_GPIO     GPIOA
#define REMOTE_PIN      GPIO_PIN_1
#define REMOTE_CLOCK    RCU_GPIOA

//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0
#define REMOTE_ID 0x80      		   

void remote_timer4ch1_init();
static void time4ch1_capture_rise_init();
static void time4ch1_capture_fall_init();
static void remote_var_init();
int32_t remote_scan(void);
void TIMER4_IRQHandler(void);
int32_t get_key_code();

#endif
