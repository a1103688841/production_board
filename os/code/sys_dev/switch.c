/******************************************
 * @Author: rnf
 * @Date: 2022-04-17 16:03:46
 * @LastEditTime: 2022-04-19 00:29:48
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board\os\code\sys_dev\switch.c
 * @rnf wrote this code
******************************************/
#include "base_typle.h"
#include "switch.h"
#include "gd32f30x.h"
#include "disp.h"

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

uint8_t switch_scan(int16_t cyc_ms)
{
    static int32_t ms1 = 0;
    static int8_t i1 = 0;
    static int8_t i2 = 0;
    uint8_t l1 = (gpio_input_bit_get(SWITCH_CLEAR_PORT,SWITCH_CLEAR_PIN)== RESET);
    uint8_t l2 = gpio_input_bit_get(SWITCH_ADD_PORT,SWITCH_ADD_PIN);
    if(l1  && ms1 < 1)
    {
        ms1 = poto_switch_p->store_n[1]*10+cyc_ms;
    }
    else if(l2 == RESET)
    {
        return 0x02;
    }
    if(ms1 > 1)
    {
        ms1 -= cyc_ms;
        if(ms1 <= 1 && l1)
        {
            i1=3;
        }
    }
    if(i1>0)
    {
        if(l1)
        {
            i1 = 3;
        }
        i1--;
        return 0x01;
    }
    return 0xff;
}