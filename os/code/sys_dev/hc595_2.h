/******************************************
 * @Author: rnf
 * @Date: 2022-04-08 22:19:12
 * @LastEditTime: 2022-04-08 22:23:28
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board\os\code\sys_dev\hc595_2.h
 * @rnf wrote this code
******************************************/

#ifndef _HC595_2_H_
#define _HC595_2_H_

#include "gd32f30x.h"
#include "base_typle.h"


void hc595_2_init();
void hc595_2_send2register(uint8_t data);
void hc595_2_parallel_output();

#endif


