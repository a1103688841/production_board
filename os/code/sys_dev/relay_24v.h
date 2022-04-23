/******************************************
 * @Author: rnf
 * @Date: 2022-04-17 15:32:49
 * @LastEditTime: 2022-04-23 15:27:35
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board\os\code\sys_dev\relay_24v.h
 * @rnf wrote this code
******************************************/
#ifndef _RELAY_24V_H_
#define _RELAY_24V_H_

void relay_init();
void relay_lever(uint8_t uid, uint8_t lever);
void set_accumulative_prev(int64_t accumulative);
void relay_response(int64_t accumulative, int32_t cyc_ms);


#endif 