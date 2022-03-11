/************************************************** 
 * @Author: shuren
 * @Date: 2022-03-02 21:22:57
 * @LastEditTime: 2022-03-03 17:26:44
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_dev\hc595.c
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#include "base_typle.h"
#include "hc595.h"

static void delay()
{
    uint32_t i;
    for(i=0; i<100; i++);
}

void hc595_init()
{
    rcu_periph_clock_enable(SER_CLOCK);
    gpio_init(SER_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SER_PIN);    
    rcu_periph_clock_enable(RCK_CLOCK);
    gpio_init(RCK_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, RCK_PIN); 
		rcu_periph_clock_enable(SRCK_CLOCK);
    gpio_init(SRCK_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SRCK_PIN); 
}

void hc595_send2register(uint8_t data)
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
		delay();
		SRCK_H;
		delay();
	}
}
void hc595_parallel_output()
{
	RCK_L;
	delay();
	RCK_H;
	delay();
	RCK_L;
}
	
