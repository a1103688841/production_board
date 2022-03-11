/************************************************** 
 * @Author: shuren
 * @Date: 2022-03-02 17:31:10
 * @LastEditTime: 2022-03-03 20:28:48
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_app\disp.h
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#ifndef __DISP_H__
#define __DISP_H__
#include "base_typle.h"
#include "bsp_uart.h"
#include "bsp_i2c.h"
#include "bsp_rtc.h"
#include "bsp_fmc.h"

typedef struct data_bin_s
{
    int8_t permission;
    int8_t flash; //INT8_MAX 全闪  0是不闪
    int8_t num_max;
    uint32_t disp;
    int64_t data;
    int64_t compensation;
    int64_t store;
    struct data_bin_s* next;
    struct data_bin_s* prev;
}DATA_BIN_S;
typedef struct flash_flag_s
{
    boolean_t   flag;
    int16_t     ms;
    int16_t     toggle_ms;
}FLASH_FLAG_S;
typedef struct stack_s
{
    int16_t sta[8];
    int8_t  i;
    int8_t max;
}STACK_S;

#define FLASH_ALL   INT8_MAX
#define FLASH_NULL    0


#define SEG_A 	0X01
#define SEG_B 	0X02
#define SEG_C 	0X04
#define SEG_D 	0X08
#define SEG_E 	0X10
#define SEG_F 	0X20
#define SEG_G 	0X40
//反逻辑
#define SEG_DP 	0X7F

#define SMG_NUL	0X80

#define SMG_N0	(SEG_A+SEG_B+SEG_C+SEG_D+SEG_E+SEG_F)
#define SMG_N1	(SEG_B+SEG_C)
#define SMG_N2	(SEG_A+SEG_B+SEG_G+SEG_E+SEG_D)
#define SMG_N3	(SEG_A+SEG_B+SEG_G+SEG_C+SEG_D)
#define SMG_N4	(SEG_F+SEG_G+SEG_B+SEG_C)
#define SMG_N5	(SEG_A+SEG_F+SEG_G+SEG_C+SEG_D)
#define SMG_N6	(SEG_A+SEG_F+SEG_E+SEG_D+SEG_C+SEG_G)
#define SMG_N7	(SEG_A+SEG_B+SEG_C)
#define SMG_N8	(SEG_A+SEG_F+SEG_G+SEG_C+SEG_D+SEG_E+SEG_B)
#define SMG_N9	(SEG_G+SEG_F+SEG_A+SEG_B+SEG_C+SEG_D)
#define SMG_F_	(SEG_D)

extern struct data_bin_s* head_p;
extern struct data_bin_s* cur_p;
extern struct data_bin_s time;
extern struct data_bin_s accum_yield;
extern struct data_bin_s prev_glue_up;
extern struct data_bin_s cur_yield_front;
extern struct data_bin_s prev_glue_dowm;
extern struct data_bin_s tem;
extern struct data_bin_s hum;
extern struct data_bin_s cur_yield_rear;
extern struct data_bin_s next_glue_up;
extern struct data_bin_s next_glue_dowm;
extern struct data_bin_s bank;


void disp_clear_link();
void disp_set_head(DATA_BIN_S* head);
void disp_add_link(DATA_BIN_S* add);
void disp_var_init();
void disp_all_link();
void disp_read_store();
void disp_write_store();
void disp_num_max_init();
void syn_disp_data2store();
void syn_disp_store2data();
void cover_disp_permission(int8_t permission);
void cover_disp_flash(int8_t flash);
int32_t set_data(int32_t data, int8_t pos, int8_t num);
void clear_button_stack();
void in_button_stack(int16_t sta);
int16_t out_button_stack();


#endif