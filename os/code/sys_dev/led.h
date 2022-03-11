/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-19 16:58:12
 * @LastEditTime: 2022-02-21 11:21:18
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \GD32F303\code\sys_dev\led.h
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#ifndef _LED_H_
#define _LED_H_

#define LED_GPIO    GPIOE
#define LED_PIN     GPIO_PIN_3
#define LED_CLOCK   RCU_GPIOE

void led_gpio_init();
void led_off();
void led_on();
void led_toggle();

#endif
