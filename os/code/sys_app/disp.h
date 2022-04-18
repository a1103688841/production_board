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

#define NDP 0
#define DP  1

#define SERIAL_MAX (6+1)
typedef struct data_bin_s
{
    int8_t flash;           //INT8_MAX is all flash  0 is no flash
    //display
    int64_t disp;       
    int64_t disp_n[SERIAL_MAX];
    int8_t  serial_max;     //array idex
    //peripheral refresh
    int64_t data;
    //store
    int64_t store;      //主要存储值
    int8_t  single;     //正负
    int64_t store_n[SERIAL_MAX];            
    //limit data
    int8_t  position_max;   //最多几位
    int64_t disp_max;       //数据最大显示多少
    //link node 
    struct data_bin_s* next;
    struct data_bin_s* prev;
}DATA_BIN_S;
typedef struct flash_flag_s
{
    //display doing refresh
    boolean_t   disp_doing;
    //flash toggle
    boolean_t   toggle;
    int16_t     ms;
    int16_t     ms_max;
    //time sec
    boolean_t   sec_toggle;
    int16_t     sec_ms;
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

//反逻辑 0->light
#define SEG_NDP 	0X80
#define SEG_DP 	    0X7F
//num
#define SMG_N0	    (SEG_A+SEG_B+SEG_C+SEG_D+SEG_E+SEG_F)
#define SMG_N1	    (SEG_B+SEG_C)
#define SMG_N2	    (SEG_A+SEG_B+SEG_G+SEG_E+SEG_D)
#define SMG_N3	    (SEG_A+SEG_B+SEG_G+SEG_C+SEG_D)
#define SMG_N4	    (SEG_F+SEG_G+SEG_B+SEG_C)
#define SMG_N5	    (SEG_A+SEG_F+SEG_G+SEG_C+SEG_D)
#define SMG_N6	    (SEG_A+SEG_F+SEG_E+SEG_D+SEG_C+SEG_G)
#define SMG_N7	    (SEG_A+SEG_B+SEG_C)
#define SMG_N8	    (SEG_A+SEG_F+SEG_G+SEG_C+SEG_D+SEG_E+SEG_B)
#define SMG_N9	    (SEG_G+SEG_F+SEG_A+SEG_B+SEG_C+SEG_D)
//Reverse num
#define SMG_RN0	(SEG_A+SEG_B+SEG_C+SEG_D+SEG_E+SEG_F)
#define SMG_RN1	(SEG_E+SEG_F)
#define SMG_RN2	(SEG_D+SEG_E+SEG_G+SEG_B+SEG_A)
#define SMG_RN3	(SEG_D+SEG_E+SEG_G+SEG_F+SEG_A)
#define SMG_RN4	(SEG_C+SEG_G+SEG_E+SEG_F)
#define SMG_RN5	(SEG_C+SEG_G+SEG_F+SEG_A+SEG_D)
#define SMG_RN6	(SEG_D+SEG_C+SEG_B+SEG_A+SEG_F+SEG_G)
#define SMG_RN7	(SEG_D+SEG_E+SEG_F)
#define SMG_RN8	(SEG_D+SEG_C+SEG_G+SEG_F+SEG_A+SEG_B+SEG_E)
#define SMG_RN9	(SEG_D+SEG_C+SEG_G+SEG_E+SEG_F+SEG_A)
//char
#define SMG_C_	    (SEG_D)
#define SMG_SPACK	SEG_NDP
#define SMG_SINGLE  (SEG_G)
#define SMG_RC_	    (SEG_A)


extern struct data_bin_s* head_p;
extern struct data_bin_s* cur_p;
extern struct data_bin_s* serial_p;
extern struct data_bin_s* serial_data_p;
extern struct data_bin_s* poto_switch_p;
extern struct data_bin_s* channel_num_p;

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
extern struct flash_flag_s flash;


void disp_clear_link();
void set_link_head(DATA_BIN_S* head);
void add_link_node(DATA_BIN_S* add);
void disp_var_init();
void disp_all_link();
void set_node_posintion_max(DATA_BIN_S* p, uint8_t max);
void link_parameter_init();
void link_parameter_first();
void syn_link_par_disp2store();
void syn_link_par_data2disp();
void syn_link_par_store2disp();
uint8_t search_link(DATA_BIN_S* data);
void cover_disp_permission(int8_t permission);
void cover_link_par_flash(int8_t flash);
int64_t set_data(int64_t data, int8_t pos, int8_t num);
void clear_button_stack();
void in_button_stack(int16_t sta);
int16_t out_button_stack();
void send_num(uint8_t num, boolean_t dot);
void send_reverse_num(uint8_t num, boolean_t dot);
void send_null(uint8_t num);
void send_char(uint8_t one_char, boolean_t dot, uint8_t num);
void send_reverse_char(uint8_t one_char, boolean_t dot, uint8_t num);
void num_deal(DATA_BIN_S* p, uint8_t position, uint8_t dot);
void num_reverse_deal(DATA_BIN_S* p, uint8_t position, uint8_t dot);
void single_deal(DATA_BIN_S* p, boolean_t dot);
void disp_refresh_task();

#endif
