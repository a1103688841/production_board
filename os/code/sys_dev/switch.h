/******************************************
 * @Author: rnf
 * @Date: 2022-04-17 16:03:58
 * @LastEditTime: 2022-04-19 00:08:28
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board\os\code\sys_dev\switch.h
 * @rnf wrote this code
******************************************/
#ifndef _SWITCH_H_
#define _SWITCH_H_

void switch_init();
uint8_t switch_scan(int16_t cyc_ms);

#endif 