/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-27 17:18:00
 * @LastEditTime: 2022-03-01 21:15:16
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_bsp\bsp_uart.h
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#ifndef __BSP_UART_H__
#define __BSP_UART_H__


void uart_queue_init();
void usart0_transmit(char txd);
void uart0_interrupt_init();
void USART0_IRQHandler(void);


#endif
