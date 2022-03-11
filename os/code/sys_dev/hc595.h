/************************************************** 
 * @Author: shuren
 * @Date: 2022-03-02 21:23:14
 * @LastEditTime: 2022-03-03 17:42:51
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_dev\hc595.h
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
 
#ifndef _HC595_H_
#define _HC595_H_

#include "gd32f30x.h"
#include "base_typle.h"


#define SER_CLOCK       RCU_GPIOB
#define SER_PORT        GPIOB
#define SER_PIN         GPIO_PIN_12

#define RCK_CLOCK       RCU_GPIOB
#define RCK_PORT        GPIOB
#define RCK_PIN         GPIO_PIN_13

#define SRCK_CLOCK      RCU_GPIOB
#define SRCK_PORT       GPIOB
#define SRCK_PIN        GPIO_PIN_14

#define SER_H           gpio_bit_set(SER_PORT, SER_PIN)
#define SER_L           gpio_bit_reset(SER_PORT, SER_PIN)
#define SRCK_H          gpio_bit_set(SRCK_PORT, SRCK_PIN)
#define SRCK_L          gpio_bit_reset(SRCK_PORT, SRCK_PIN)
#define RCK_H           gpio_bit_set(RCK_PORT, RCK_PIN)
#define RCK_L           gpio_bit_reset(RCK_PORT, RCK_PIN)



static void delay();
void hc595_init();
void hc595_send2register(uint8_t data);
void hc595_parallel_output();


#endif
