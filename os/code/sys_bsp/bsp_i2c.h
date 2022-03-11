/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-27 22:16:08
 * @LastEditTime: 2022-03-01 13:56:38
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_bsp\bsp_i2c.h
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#ifndef __BSP_I2C_H__
#define __BSP_I2C_H__
#include "base_typle.h"
#include "gd32f30x.h"

#define I2C_WRITE   0           
#define I2C_READ    1

#define SDA_PORT 	GPIOB
#define SCL_PORT	GPIOB
#define SDA_PIN		GPIO_PIN_7
#define SCL_PIN		GPIO_PIN_6

#define SDA_H()		gpio_bit_set	(SDA_PORT, SDA_PIN)
#define SCL_H()		gpio_bit_set	(SCL_PORT, SCL_PIN)
#define SDA_L()		gpio_bit_reset(SDA_PORT, SDA_PIN)
#define SCL_L()		gpio_bit_reset(SCL_PORT, SCL_PIN)
#define SDA_IN()	gpio_init(SDA_PORT,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,SDA_PIN)
#define SDA_OUT()   gpio_init(SDA_PORT,GPIO_MODE_OUT_OD,GPIO_OSPEED_50MHZ,SDA_PIN)
#define SDA_GET()   gpio_input_bit_get(SDA_PORT,SDA_PIN)
void delay();
#define DELAY()     delay()


void i2c0_simulation_init();
void i2c_start();
void i2c_stop();
uint8_t i2c_wait_ack();
void i2c_ack();
void i2c_nack();
void i2c_send_byte(uint8_t txd);
void i2c_send_addr(uint8_t addr, uint8_t rw);
uint8_t i2c_read_byte();


#endif 
