/******************************************
 * @Author: rnf
 * @Date: 2022-04-17 15:32:49
 * @LastEditTime: 2022-04-17 15:42:52
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board\os\code\sys_dev\relay_24v.h
 * @rnf wrote this code
******************************************/
#ifndef _RELAY_24V_H_
#define _RELAY_24V_H_

void relay_init();
void relay_lever(uint8_t uid, uint8_t lever);

#endif 