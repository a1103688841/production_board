/******************************************
 * @Author: rnf
 * @Date: 2022-04-08 22:19:02
 * @LastEditTime: 2022-04-19 21:45:40
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board\os\code\sys_dev\hc595_2.c
 * @rnf wrote this code
******************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "base_typle.h"
#include "hc595_2.h"

/******************************************
 * @Author: rnf
 * @Date: 2022-04-03 15:32:33
 * @LastEditTime: 2022-04-08 22:20:08
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board\os\code\sys_dev\hc595.c
 * @rnf wrote this code
******************************************/
#include "base_typle.h"
#include "hc595.h"

#define SER_CLOCK       RCU_GPIOB
#define SER_PORT        GPIOB
#define SER_PIN         GPIO_PIN_10

#define RCK_CLOCK       RCU_GPIOB
#define RCK_PORT        GPIOB
#define RCK_PIN         GPIO_PIN_15

#define SRCK_CLOCK      RCU_GPIOA
#define SRCK_PORT       GPIOA
#define SRCK_PIN        GPIO_PIN_8

#define SER_H           gpio_bit_set(SER_PORT, SER_PIN)
#define SER_L           gpio_bit_reset(SER_PORT, SER_PIN)
#define SRCK_H          gpio_bit_set(SRCK_PORT, SRCK_PIN)
#define SRCK_L          gpio_bit_reset(SRCK_PORT, SRCK_PIN)
#define RCK_H           gpio_bit_set(RCK_PORT, RCK_PIN)
#define RCK_L           gpio_bit_reset(RCK_PORT, RCK_PIN)

/******************************************
 * @description: 
 * @param {*}
 * @return {*}
******************************************/
static void hc595_delay()
{
    uint32_t i;
	for(i=0; i<10000; i++);
}
/******************************************
 * @description: 
 * @param {*}
 * @return {*}
******************************************/
void hc595_2_init()
{
    rcu_periph_clock_enable(SER_CLOCK);
    gpio_init(SER_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SER_PIN);    
    rcu_periph_clock_enable(RCK_CLOCK);
    gpio_init(RCK_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, RCK_PIN); 
	rcu_periph_clock_enable(SRCK_CLOCK);
    gpio_init(SRCK_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SRCK_PIN); 
 
}

/******************************************
 * @description: 
 * @param {uint8_t} data
 * @return {*}
******************************************/
void hc595_2_send2register(uint8_t data)
{
	unsigned char data_i;
	//初始下降沿保持准备
	SRCK_L;
	for(data_i=0;data_i<8;data_i++)
	{
		SRCK_L;
		if(data&0x80)
		{
			SER_H;
		}else{
			SER_L;
		}
		data=data<<1;
		hc595_delay();
		SRCK_H;
		hc595_delay();
	}
}
/******************************************
 * @description: 
 * @param {*}
 * @return {*}
******************************************/
void hc595_2_parallel_output()
{
	RCK_L;
	hc595_delay();
	RCK_H;
	hc595_delay();
	RCK_L;
}
	
