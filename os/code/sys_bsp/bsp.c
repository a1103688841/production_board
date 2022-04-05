/****************************************** 
 * @Author: your name
 * @Date: 2022-04-02 23:04:17
 * @LastEditTime: 2022-04-05 18:08:23
 * @LastEditors: rnf
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \production_board-master\os\code\sys_bsp\bsp.c
 ******************************************/
/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-18 15:06:48
 * @LastEditTime: 2022-03-04 21:46:18
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_bsp\bsp.c
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
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
	
	hc595_init();
	disp_read_store();
	disp_all_link();
	link_parameter_init();
	flash.toggle=0;
	flash.ms=0;
	flash.ms_max = 1000;

	sta = STA_NORMAL;
}

