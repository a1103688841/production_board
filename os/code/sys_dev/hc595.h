/******************************************
 * @Author: rnf
 * @Date: 2022-04-05 19:19:44
 * @LastEditTime: 2022-04-08 22:21:53
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board\os\code\sys_dev\hc595.h
 * @rnf wrote this code
******************************************/
 
#ifndef _HC595_H_
#define _HC595_H_

#include "gd32f30x.h"
#include "base_typle.h"


void hc595_init();
void hc595_send2register(uint8_t data);
void hc595_parallel_output();


#endif
