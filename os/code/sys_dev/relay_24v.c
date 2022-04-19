/******************************************
 * @Author: rnf
 * @Date: 2022-04-17 15:32:34
 * @LastEditTime: 2022-04-19 21:29:10
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board\os\code\sys_dev\relay_24v.c
 * @rnf wrote this code
******************************************/
#include "base_typle.h"
#include "relay_24v.h"
#include "disp.h"
#include "gd32f30x.h"
#include "main.h"

#define RELAY1_CLOCK       RCU_GPIOB
#define RELAY1_PORT        GPIOB
#define RELAY1_PIN         GPIO_PIN_0

#define RELAY2_CLOCK       RCU_GPIOA
#define RELAY2_PORT        GPIOA
#define RELAY2_PIN         GPIO_PIN_7

#define RELAY3_CLOCK       RCU_GPIOA
#define RELAY3_PORT        GPIOA
#define RELAY3_PIN         GPIO_PIN_6

#define RELAY4_CLOCK       RCU_GPIOB
#define RELAY4_PORT        GPIOB
#define RELAY4_PIN         GPIO_PIN_1


void relay_init()
{
    rcu_periph_clock_enable(RELAY1_CLOCK);
    gpio_init(RELAY1_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, RELAY1_PIN);    
    rcu_periph_clock_enable(RELAY2_CLOCK);
    gpio_init(RELAY2_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, RELAY2_PIN);    
    rcu_periph_clock_enable(RELAY3_CLOCK);
    gpio_init(RELAY3_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, RELAY3_PIN);    
    rcu_periph_clock_enable(RELAY4_CLOCK);
    gpio_init(RELAY4_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, RELAY4_PIN);    
}

/******************************************
 * @description: 
 * @param {uint8_t} uid
 * @param {uint8_t} lever
 * @return {*}
******************************************/
void relay_lever(uint8_t uid, uint8_t lever)
{
    if(uid == 1)
    {
        if(lever == 1)
        {
            gpio_bit_set(RELAY1_PORT, RELAY1_PIN);
        }
        else 
        {
            gpio_bit_reset(RELAY1_PORT, RELAY1_PIN);
        }
    }
    else if(uid == 2)
    {
        if(lever == 1)
        {
            gpio_bit_set(RELAY2_PORT, RELAY2_PIN);
        }
        else 
        {
            gpio_bit_reset(RELAY2_PORT, RELAY2_PIN);
        }
    }
    else if(uid == 3)
    {
        if(lever == 1)
        {
            gpio_bit_set(RELAY3_PORT, RELAY3_PIN);
        }
        else 
        {
            gpio_bit_reset(RELAY3_PORT, RELAY3_PIN);
        }       
    }
    else if(uid == 4)
    {
        if(lever == 1)
        {
            gpio_bit_set(RELAY4_PORT, RELAY4_PIN);
        }
        else 
        {
            gpio_bit_reset(RELAY4_PORT, RELAY4_PIN);
        }        
    }
}
#define PREV_GLUE_UP_RELAY_UID    1
#define PREV_GLUE_DOWM_RELAY_UID  2
#define NEXT_GLUE_UP_RELAY_UID    3
#define NEXT_GLUE_DOWM_RELAY_UID  4

#define PREV_GLUE_UP_STORE_UID    1
#define PREV_GLUE_DOWM_STORE_UID  2
#define NEXT_GLUE_UP_STORE_UID    3
#define NEXT_GLUE_DOWM_STORE_UID  4
/******************************************
 * @description: 
 * @param {int64_t} accumulative
 * @param {int32_t} cyc_ms
 * @return {*}
******************************************/
static int64_t accumulative_prev;
void set_accumulative_prev(int64_t accumulative)
{
    accumulative_prev = accumulative;
}
void relay_response(int64_t accumulative, int32_t cyc_ms)
{
    static int32_t ms1 = 0;
    static int32_t ms2 = 0;
    static int32_t ms3 = 0;
    static int32_t ms4 = 0;
    static int8_t  sta_prev;
    if(sta != STA_NORMAL)
    {
        relay_lever(1, RESET);
        relay_lever(2, RESET);
        relay_lever(3, RESET);
        relay_lever(4, RESET);
        return;
    } 
    if(sta == STA_NORMAL && sta_prev != STA_NORMAL)
    {
        accumulative_prev = accumulative;
    }
    if(accumulative == 0) return;
    if(accumulative_prev != accumulative)
    {
        if(accumulative%channel_num_p->store_n[PREV_GLUE_UP_STORE_UID] == 0)
        {
            ms1 += prev_glue_up.store*1000+cyc_ms;
        }
        if(accumulative%channel_num_p->store_n[PREV_GLUE_DOWM_STORE_UID] == 0)
        {
            ms2 += prev_glue_dowm.store*1000+cyc_ms;
        }
        if(accumulative%channel_num_p->store_n[NEXT_GLUE_UP_STORE_UID] == 0)
        {
            ms3 += next_glue_up.store*1000+cyc_ms;
        }
        if(accumulative%channel_num_p->store_n[NEXT_GLUE_DOWM_STORE_UID] == 0)
        {
            ms4 += next_glue_dowm.store*1000+cyc_ms;
        }    
    }
    if(ms1 > 1)
    {
        ms1 -= cyc_ms;
        relay_lever(PREV_GLUE_UP_RELAY_UID, SET);
    }else{
        relay_lever(PREV_GLUE_UP_RELAY_UID, RESET);
    }
    if(ms2 > 1)
    {
        ms2 -= cyc_ms;
        relay_lever(PREV_GLUE_DOWM_RELAY_UID, SET);
    }else{
        relay_lever(PREV_GLUE_DOWM_RELAY_UID, RESET);
    }
    if(ms3 > 1)
    {
        ms3 -= cyc_ms;
        relay_lever(NEXT_GLUE_UP_RELAY_UID, SET);
    }else{
        relay_lever(NEXT_GLUE_UP_RELAY_UID, RESET);
    }
    if(ms4 > 1)
    {
        ms4 -= cyc_ms;
        relay_lever(NEXT_GLUE_DOWM_RELAY_UID, SET);
    }else{
        relay_lever(NEXT_GLUE_DOWM_RELAY_UID, RESET);
    }
    accumulative_prev = accumulative;
    sta_prev = sta;
}
