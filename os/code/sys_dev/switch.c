/******************************************
 * @Author: rnf
 * @Date: 2022-04-17 16:03:46
 * @LastEditTime: 2022-04-17 16:15:03
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board\os\code\sys_dev\switch.c
 * @rnf wrote this code
******************************************/
#include "base_typle.h"
#include "switch.h"
#include "gd32f30x.h"


#define SWITCH_CLEAR_CLOCK       RCU_GPIOA
#define SWITCH_CLEAR_PORT        GPIOA
#define SWITCH_CLEAR_PIN         GPIO_PIN_4

#define SWITCH_ADD_CLOCK       RCU_GPIOA
#define SWITCH_ADD_PORT        GPIOA
#define SWITCH_ADD_PIN         GPIO_PIN_5

void switch_init()
{
    rcu_periph_clock_enable(SWITCH_CLEAR_CLOCK);
    gpio_init(SWITCH_CLEAR_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, SWITCH_CLEAR_PIN); 
    rcu_periph_clock_enable(SWITCH_ADD_CLOCK);
    gpio_init(SWITCH_ADD_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, SWITCH_ADD_PIN);     
}

uint8_t switch_scan()
{
    if(gpio_input_bit_get(SWITCH_CLEAR_PORT,SWITCH_CLEAR_PIN) == RESET)
    {
        return 0x01;
    }
    else if(gpio_input_bit_get(SWITCH_ADD_PORT,SWITCH_ADD_PIN) == RESET)
    {
        return 0x02;
    }
    else
    {
        return 0xff;
    }
}