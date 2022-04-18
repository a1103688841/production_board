#include "base_typle.h"
#include "relay_24v.h"
#include "gd32f30x.h"

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