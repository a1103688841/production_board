/******************************************
 * @Author: rnf
 * @Date: 2022-04-05 19:19:44
 * @LastEditTime: 2022-04-18 23:27:50
 * @LastEditors: rnf
 * @Description: 
 * @FilePath: \production_board\os\code\sys_app\main.h
 * @rnf wrote this code
******************************************/
enum
{
    STA_OFF,        //软关机
    STA_DATA_RST,   //数据复位
    STA_NORMAL,     //正常显示模式
    STA_EDIT,       //设置[累计产量],[当前产量],[前加胶时间上],[前加胶时间下]
    STA_EDIT_REAR,  //设置[后当前产量],[后加胶时间上],[后加胶时间下]
    STA_CHANNEL_NUM,   //设置"前加胶数量上","前加胶数量下","后加胶数量上","后加胶数量下"
    STA_OPTO_SWITCH,   //设置"延时时间","闭合时间","补偿步进""
    STA_EDIT_CLEAR_TIME,
    STA_TIME,       //设置时间 
    STA_CLEAR_TIME,
    STA_COMPENSATION,   //设置温湿度补偿
    STA_CNT_PAR,
};

extern int32_t sta;