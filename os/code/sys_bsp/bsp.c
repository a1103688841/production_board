/******************************************
 * @Author: rnf
 * @Date: 2022-04-05 19:19:44
 * @LastEditTime: 2022-04-19 21:46:59
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board\os\code\sys_bsp\bsp.c
 * @rnf wrote this code
******************************************/
#include "base_typle.h"
#include "gd32f30x.h"
#include "systick.h"
#include "remote.h"
#include "button.h"
#include "bsp_i2c.h"
#include "bsp_uart.h"
#include "bsp_rtc.h"
#include "hc595.h"
#include "main.h"
#include "disp.h"

/******************************************
 * @description: 
 * @param {*}
 * @return {*}
******************************************/
void bsp_init()
{
	uint8_t read;
	nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
	rcu_periph_clock_enable(RCU_AF);

	systick_config();

	uart0_interrupt_init();

	led_gpio_init();

	remote_timer2ch1_init();
	remote_timer3ch2_init();

	i2c0_simulation_init();

	buttonAttachInit();

	rtc_init();
	
	relay_init();
	
	switch_init();
	
	hc595_init();
	hc595_2_init();
	disp_read_store();
    link_parameter_init();

	set_accumulative_prev(accum_yield.disp);


set_par_lever_timermax(&sw_add,accum_yield.store_n[1]*10/BUTTON_CYCE);
	set_par_sleep_timermax(&sw_add, accum_yield.store_n[2]*10/BUTTON_CYCE);		
	set_par_long_timermax(&sw_add,accum_yield.store_n[3]*10/BUTTON_CYCE);
	set_par_longcyc_timermax(&sw_add, accum_yield.store_n[3]*10/BUTTON_CYCE);

	flash.ms_max = 300;
	sta = STA_NORMAL;
}

