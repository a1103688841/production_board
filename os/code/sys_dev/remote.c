/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-19 16:05:49
 * @LastEditTime: 2022-02-27 20:35:56
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_dev\remote.c
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#include "base_typle.h"
#include "gd32f30x.h"
#include "remote.h"

//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0
#define REMOTE_ID 0x80      

#define RMT_PORT 	GPIOB
#define RMT_PIN 	GPIO_PIN_5

struct rmt_sta_s{
    uint8_t leader      :1;
    uint8_t complete    :1;
    uint8_t bank        :1;
    uint8_t rise        :1;
    uint8_t overflow    :4;
};    //遥控器接收状态


void remote_timer2ch1_init()
{   
    timer_parameter_struct timer_initpara;
    
    remote_var_init();

    rcu_periph_clock_enable(RCU_GPIOB);
    
    gpio_init(RMT_PORT,GPIO_MODE_IN_FLOATING,GPIO_OSPEED_50MHZ,RMT_PIN);
    gpio_pin_remap_config(GPIO_TIMER2_PARTIAL_REMAP, ENABLE);

    rcu_periph_clock_enable(RCU_TIMER2);
    timer_deinit(TIMER2);

    /* TIMER2 configuration */
    timer_initpara.prescaler         = 119;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 10000;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER2,&timer_initpara);

    time2ch1_capture_rise_init();

    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER2);
    /* clear channel 1 interrupt bit */
    timer_interrupt_flag_clear(TIMER2,TIMER_INT_FLAG_CH1);
    /* channel 1 interrupt enable */
    timer_interrupt_enable(TIMER2,TIMER_INT_CH1|TIMER_INT_UP);

    /* TIMER2 counter enable */
    timer_enable(TIMER2);

    //NVIC
    nvic_irq_enable(TIMER2_IRQn, 1, 1);
}

static void time2ch1_capture_rise_init()
{
    timer_ic_parameter_struct timer_icinitpara;
    /* TIMER2 CH1 input capture configuration */
    timer_icinitpara.icpolarity  = TIMER_IC_POLARITY_RISING;
    timer_icinitpara.icselection = TIMER_IC_SELECTION_DIRECTTI;
    timer_icinitpara.icprescaler = TIMER_IC_PSC_DIV1;
    timer_icinitpara.icfilter    = 0x3;
    timer_input_capture_config(TIMER2,TIMER_CH_1,&timer_icinitpara);
}
static void time2ch1_capture_fall_init()
{
    timer_ic_parameter_struct timer_icinitpara;
    /* TIMER2 CH1 input capture configuration */
    timer_icinitpara.icpolarity  = TIMER_IC_POLARITY_FALLING;
    timer_icinitpara.icselection = TIMER_IC_SELECTION_DIRECTTI;
    timer_icinitpara.icprescaler = TIMER_IC_PSC_DIV1;
    timer_icinitpara.icfilter    = 0x3;
    timer_input_capture_config(TIMER2,TIMER_CH_1,&timer_icinitpara);
}


  

static struct rmt_sta_s     rmt_sta;
static uint16_t             high_time;	//下降沿时计数器的值
static uint32_t             rmt_rec;	//红外接收到的数据	   		    
static uint8_t              rmt_repet;	//按键按下的次数
static int32_t              key_code;


static void remote_var_init() {
    rmt_sta.leader = FALSE;
    rmt_sta.complete = FALSE;
    rmt_sta.bank = 0;
    rmt_sta.rise = FALSE;
    rmt_sta.overflow = 0;
    high_time = 0;
    rmt_rec = 0;
    rmt_repet = 0;
}

/****************************************** 
 * @description: 
 * @param {*}
 * @return {*}
 ******************************************/
int32_t get_remote_code()
{
	return key_code;
}
/************************************************** 
 * @description: 
 * @param {*}
 * @return {*}
 **************************************************/
int32_t remote_scan(void)
{        
	int32_t sta=-1;       
    uint8_t t1,t2;  
	if(rmt_sta.complete == TRUE)//得到一个按键的所有信息了
	{ 
	    t1=rmt_rec>>24;			//得到地址码
	    t2=(rmt_rec>>16)&0xff;	//得到地址反码 
 	    if((t1==(uint8_t)~t2) && t1== REMOTE_ID)//检验遥控识别码(ID)及地址 
	    { 
	        t1=(rmt_rec>>8)&0xff;
	        t2=(rmt_rec)&0xff; 	
	        if(t1==(uint8_t)~t2) sta=t1;//键值正确	 
		}   
		if((sta==-1)||(rmt_sta.leader==FALSE))//按键数据错误/遥控已经没有按下了
		{
		 	rmt_sta.complete=FALSE; //清除接收到有效按键标识
			rmt_repet=0;		    //清除按键次数计数器
		}
	}
	key_code = sta;  
    return sta;
}

/************************************************** 
 * @description: 
 * @param {*}
 * @return {*}
 **************************************************/
void TIMER2_IRQHandler(void)
{
    timer_ic_parameter_struct timer_icinitpara;
    if(SET == timer_interrupt_flag_get(TIMER2,TIMER_INT_FLAG_CH1)){
        timer_interrupt_flag_clear(TIMER2,TIMER_INT_FLAG_CH1);
        //NEC编码上沿处理
        if(gpio_input_bit_get(RMT_PORT, RMT_PIN) == TRUE) {
            time2ch1_capture_fall_init();
            timer_counter_value_config(TIMER2, 0);
            rmt_sta.rise = TRUE;
        } else {
        //NEC编码下沿处理
			high_time = timer_counter_read(TIMER2);     //读取CCR1也可以清CC1IF标志位
			time2ch1_capture_rise_init();   //设置为上升沿捕获
			if(rmt_sta.rise == TRUE) {      //完成一次高电平捕获 
 				if(rmt_sta.leader == TRUE) {            //接收到了引导码
					if(300<high_time&&high_time<800){   //560为标准值,560us
						rmt_rec<<=1;	    //左移一位.
						rmt_rec|=0;	        //接收到0	   
					} else if (1400<high_time&&high_time<1800){ //1680为标准值,1680us
						rmt_rec<<=1;	    //左移一位.
						rmt_rec|=1;	        //接收到1
					} else if (2200<high_time&&high_time<2600){	//得到按键键值增加的信息 2500为标准值2.5ms
						rmt_repet++; 		        //按键次数增加1次
						rmt_sta.overflow = 0;	//清空计时器		
					}
 				}else if(4200<high_time&&high_time<4700) {  //4500为标准值4.5ms
                    rmt_sta.leader = TRUE;  //标记成功接收到了引导码
                    rmt_repet = 0;          //清除按键次数计数器	
				}						 
			}
            rmt_sta.rise = FALSE;
        }
    } else if(SET == timer_interrupt_flag_get(TIMER2,TIMER_INT_FLAG_UP)){
        timer_interrupt_flag_clear(TIMER2,TIMER_INT_FLAG_UP);
        //NEC编码10ms溢出处理
		if(rmt_sta.leader == TRUE) {  //上次有数据被接收到了
            rmt_sta.rise = FALSE;   //取消上升沿已经被捕获标记
            if(rmt_sta.overflow == 0) {
                rmt_sta.complete = TRUE;    //标记已经完成一次按键的键值信息采集
            }
            if(rmt_sta.overflow < 14) {
                rmt_sta.overflow ++;
            } else {
                rmt_sta.leader = FALSE;  //清空引导标识
                rmt_sta.overflow = 0;    //清空计数器
            }				 	   	
		}
    }
}