/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-27 17:17:51
 * @LastEditTime: 2022-02-27 20:15:35
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_bsp\bsp_uart.c
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#include "base_typle.h"
#include "gd32f30x.h"
#include "bsp_uart.h"
#include "my_print.h"
#include "my_queue.h"


#define UART_BUF_LEN  256
struct queue_s rx0_queue,tx0_queue;
void uart_queue_init()
{
    static char tx0_buf[UART_BUF_LEN];
    static char rx0_buf[UART_BUF_LEN];
    tx0_queue.buff     = tx0_buf;
    tx0_queue.max      = UART_BUF_LEN;
    init_queue(&tx0_queue);
    rx0_queue.buff     = rx0_buf;
    rx0_queue.max      = UART_BUF_LEN;
    init_queue(&rx0_queue);
}
void usart0_transmit(char txd)
{
    while (enQueue(&tx0_queue, txd) == FALSE);
    usart_interrupt_enable(USART0, USART_INT_TBE);
}
void uart0_interrupt_init()
{
    uart_queue_init();
    my_print_init((PUT_FUNC_T)usart0_transmit);

    rcu_periph_clock_enable(RCU_GPIOA);	
    rcu_periph_clock_enable(RCU_USART0);

		//PA9 TX, PA10 RX
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    usart_deinit(USART0);
    usart_baudrate_set(USART0, 115200U);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);
    //interrupt enable
    usart_interrupt_enable(USART0, USART_INT_RBNE);
    //NVIC
    nvic_irq_enable(USART0_IRQn, 0, 0);
}

void USART0_IRQHandler(void)
{
    union{uint8_t u8; char i8;}rec;
    if(SET == usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE)){
        rec.u8 = (uint8_t)usart_data_receive(USART0);
        enQueue(&rx0_queue, rec.i8);
    }       
    if(SET == usart_interrupt_flag_get(USART0, USART_INT_FLAG_TBE)){
        if(deQueue(&tx0_queue, &rec.i8) == TRUE){
            usart_data_transmit(USART0, rec.u8);
        }else{
            usart_interrupt_disable(USART0, USART_INT_TBE);
        }
    }
}
