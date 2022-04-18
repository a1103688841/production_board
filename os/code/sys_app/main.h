/******************************************
 * @Author: rnf
 * @Date: 2022-04-05 19:19:44
 * @LastEditTime: 2022-04-18 20:47:30
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board\os\code\sys_app\main.h
 * @rnf wrote this code
******************************************/
enum
{
    STA_OFF,
    STA_DATA_RST,
    STA_NORMAL,
    STA_EDIT,//设置[累计产量],[当前产量]
    STA_EDIT_REAR,
    STA_EDIT_CLEAR_TIME,
    STA_TIME,
    STA_CLEAR_TIME,
    STA_COMPENSATION,
    STA_CNT_PAR,
};

extern int32_t sta;