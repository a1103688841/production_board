/******************************************
 * @Author: rnf
 * @Date: 2022-04-03 15:32:33
 * @LastEditTime: 2022-04-05 17:30:28
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board-master\os\code\sys_dev\hc595.c
 * @rnf wrote this code
******************************************/
#include "base_typle.h"
#include "hc595.h"

/******************************************
 * @description: 
 * @param {*}
 * @return {*}
******************************************/
static void hc595_delay()
{
    uint64_t i;
    for(i=0; i<500; i++);
}
/******************************************
 * @description: 
 * @param {*}
 * @return {*}
******************************************/
void hc595_init()
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
void hc595_parallel_output()
{
	hc595_delay();
	RCK_L;
	hc595_delay();
	RCK_H;
	hc595_delay();
	RCK_L;
	hc595_delay();
}
	
