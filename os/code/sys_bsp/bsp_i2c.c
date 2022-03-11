/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-27 22:16:00
 * @LastEditTime: 2022-03-02 14:08:25
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_bsp\bsp_i2c.c
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#include "base_typle.h"
#include "gd32f30x.h"
#include "bsp_i2c.h"
#include "systick.h"
//cyc
//    |----|
//    |    |
//----|    |
void delay()
{
    uint32_t i;
    for(i=0; i<1000; i++);
}

//初始化IIC
void i2c0_simulation_init()
{
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_init(SDA_PORT, GPIO_MODE_OUT_OD, GPIO_OSPEED_50MHZ, SDA_PIN);    
    gpio_init(SCL_PORT, GPIO_MODE_OUT_OD, GPIO_OSPEED_50MHZ, SCL_PIN);
    SDA_OUT();
    SDA_H();
}
//产生IIC起始信号
void i2c_start()
{
  DELAY();
	SDA_H();
	SCL_H();
	DELAY();
	SDA_L();
	DELAY();
	SCL_L();
}
//产生IIC停止信号
void i2c_stop()
{
	SDA_L();
	DELAY();
	SCL_H();
	DELAY();
	SDA_H();
	DELAY();
}
//等待应答信号到来
//返回值：0，接收应答失败
//        1，接收应答成功
uint8_t i2c_wait_ack()
{
	uint8_t over_time=0;			//timeout time
	SDA_IN();
	SCL_L();	
	DELAY();
	SCL_H();	
	while(((SDA_GET())!=RESET)&&over_time<250)over_time++;
	if(over_time>245) {
		SDA_OUT();
		return FALSE;
	}
	DELAY();
	DELAY();    //使应答信号更明显
	DELAY();
	SCL_L();
	SDA_OUT();
    SDA_H();
	return TRUE;
}
//产生ACK应答
void i2c_ack()
{
	SDA_L();
  SCL_L();		
	DELAY();
	SCL_H();
	DELAY();
	DELAY();		//使应答信号更明显
	DELAY();
	SCL_L();
	DELAY();	 
	SDA_H();		//释放SDA总线
}
//不产生ACK应答	
void i2c_nack()
{
	SDA_H();
    SCL_L();		
	DELAY();
	SCL_H();
	DELAY();
	DELAY();		//使应答信号更明显
	DELAY();
	SCL_L();
	DELAY();	 
	SDA_H();		//释放SDA总线
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void i2c_send_byte(uint8_t txd)
{                        
    uint8_t i;   	    
    SCL_L();//拉低时钟开始数据传输
    for(i=0; i<8; i++) 
    {              
        if((txd&0x80)==0x80){SDA_H();}else{SDA_L();}
        txd<<=1; 	  
		DELAY();  
		SCL_H();
		DELAY(); 
		SCL_L();	
    }	 
		SDA_H();		//释放SDA总线
} 
void i2c_send_addr(uint8_t addr, uint8_t rw)
{
    if(rw == I2C_WRITE) {
        i2c_send_byte(addr<<1);
    } else {
        i2c_send_byte(addr<<1|0x01);
    }
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t i2c_read_byte()
{
	uint8_t i,receive=0;
	SDA_IN();
	SDA_IN();
	SDA_IN();//SDA设置为输入
    for(i=0; i<8; i++ )
	{
        SCL_L(); 
        DELAY();
		SCL_H();
        DELAY();
        receive<<=1;
        if(SDA_GET())receive++;   
    }			
	SDA_OUT();	
    SDA_H();
    return receive;
}

