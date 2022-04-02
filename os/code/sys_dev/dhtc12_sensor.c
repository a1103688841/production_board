/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-21 11:18:35
 * @LastEditTime: 2022-03-01 22:52:12
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_dev\dhtc12_sensor.c
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#include "base_typle.h"
#include "gd32f30x.h"
#include "systick.h"
#include "dhtc12_sensor.h"
#include "bsp_i2c.h"
#include "my_print.h"

static int32_t HumA,HumB;

uint16_t get_humA()
{
	return HumA;
}
uint16_t get_humB()
{
	return HumB;
}
const uint16_t POLYNOMIAL = 0x131;  //P(x)=x^8+x^5+x^4+1 = 100110001
uint8_t SHT3x_CheckCrc(uint8_t data[], uint8_t nbrOfBytes)  //跟SHT30一样只是将CRC值到会到data后返回
{
  uint8_t crc = 0xff;	//0
  uint8_t byteCtr,bit;
  //calculates 8-Bit checksum with given polynomial
  for (byteCtr = 0; byteCtr < nbrOfBytes; ++byteCtr)
  { crc ^= (data[byteCtr]);
    for (bit = 8; bit > 0; --bit)
    { if (crc & 0x80) crc = (crc << 1) ^ POLYNOMIAL;
      else crc = (crc << 1);
    }
  }
  if (crc != data[nbrOfBytes]) 
	{
		data[nbrOfBytes] = crc;
		return 0x01;
	}
  else return 0;
}
//读取寄存器数据
int32_t dhtc12_read_reg(uint16_t command)
{
	uint8_t error,data[3];
	uint16_t ReDat;
	i2c_start();
    i2c_send_addr(DHTC12_ADDR, I2C_WRITE);
	if(i2c_wait_ack() == FALSE){i2c_stop();return -1;} 
	i2c_send_byte((command&0XFF00)>>8);
	if(i2c_wait_ack() == FALSE){i2c_stop();return -1;} 
	i2c_send_byte((command&0X00FF));
	if(i2c_wait_ack() == FALSE){i2c_stop();return -1;} 
	DELAY();
    i2c_start();
    i2c_send_addr(DHTC12_ADDR, I2C_READ);
    if(i2c_wait_ack() == FALSE){i2c_stop();return -1;} 
	data[0] = i2c_read_byte();
	i2c_ack();
	data[1] = i2c_read_byte();
	i2c_ack();
	data[2] = i2c_read_byte();
	i2c_nack();
	i2c_stop();
	error = SHT3x_CheckCrc(data,2);
	if(error == FALSE) {
		return data[0];
	}else {
		return -1;
	}
}
boolean_t dhtc12_rest() 
{
    i2c_start();
    i2c_send_addr(DHTC12_ADDR, I2C_WRITE);
    if(i2c_wait_ack() == FALSE){i2c_stop();return FALSE;} 
    i2c_send_byte((DHTC12_RESET&0XFF00)>>8);
    if(i2c_wait_ack() == FALSE){i2c_stop();return FALSE;} 
    i2c_send_byte((DHTC12_RESET&0X00FF));
    i2c_wait_ack();
    i2c_stop();
    return TRUE;
}

boolean_t dhtc12_read_all(int16_t *tem,uint16_t *Hum) 
{
    uint8_t i;
    uint8_t error = FALSE;
	int32_t TemBuf,CapBuf;//s32
    uint8_t data[6],crc[3];
		union{uint16_t u16; int16_t i16;}ex;
    i2c_start();
    i2c_send_addr(DHTC12_ADDR, I2C_WRITE);
    DELAY();
    if(i2c_wait_ack() == FALSE){i2c_stop();return FALSE;} 
    i2c_send_byte((DHTC12_MEAS_ALL&0XFF00)>>8);
    if(i2c_wait_ack() == FALSE){i2c_stop();return FALSE;} 
    i2c_send_byte((DHTC12_MEAS_ALL&0X00FF));
    if(i2c_wait_ack() == FALSE){i2c_stop();return FALSE;} 
    i2c_stop();
    for(i=0; i<50; i++) {
        delay_1ms(4);
        i2c_start();
        i2c_send_addr(DHTC12_ADDR, I2C_READ);
        if(i2c_wait_ack() == TRUE) {
					break;
				}else{
					i2c_stop();
				}
    }
    if(i>45){return FALSE;} 
    data[0] = i2c_read_byte();
    i2c_ack();
    data[1] = i2c_read_byte();
    i2c_ack();
    data[2] = i2c_read_byte();
    i2c_ack();
    data[3] = i2c_read_byte();
    i2c_ack();
    data[4] = i2c_read_byte();
    i2c_ack();
    data[5] = i2c_read_byte();
    i2c_nack();
    i2c_stop();
    crc[0] = data[0];
    crc[1] = data[1];
    crc[2] = data[2];
    error  = SHT3x_CheckCrc(crc, 2);
    if(error == FALSE) {
				ex.u16 = (uint16_t)data[0]<<8|(data[1]);
				TemBuf = ex.i16;
        TemBuf = TemBuf*10/256+400;
        *tem = TemBuf;
    }
	crc[0] = data[3];
	crc[1] = data[4];
	crc[2] = data[5];
	error = SHT3x_CheckCrc(crc,2);
	if(error == FALSE) {
        ex.u16 = (uint16_t)data[3]<<8|(data[4]);
				CapBuf = ex.i16;
        CapBuf = (CapBuf-HumB)*600/(HumA-HumB)+300;
        //20℃为5个湿度点  即1℃为0.25个湿度点  0.1℃为0.025
        CapBuf = CapBuf+ 25*(TemBuf-250)/100;
        if(CapBuf>1000) {
            CapBuf = 999;
        } else if(CapBuf<0) {
            CapBuf = 0;
        }
        *Hum = (uint16_t)CapBuf;//同样结果*10
	}
	return !error;
}

boolean_t dhtc12_init()
{
	int32_t HumA_temp,HumB_temp;
		uint8_t i;
    dhtc12_rest();
		i = 0;
    do
		{
			i++;
			HumA = dhtc12_read_reg(DHTC12_HUMAH);
			PRINT("HumAH\n");
		}while(HumA==-1 && i<10);
		i = 0;
    do
		{
			i++;
			HumA_temp = dhtc12_read_reg(DHTC12_HUMAL);
			PRINT("HumAL\n");
		}while(HumA_temp==-1&& i<10);
		
    HumA = (HumA<<8)|HumA_temp;
		i = 0;
    do
		{
			i++;
			HumB = dhtc12_read_reg(DHTC12_HUMBH);
			PRINT("HumBH\n");
		}while(HumB==-1&& i<10);
		i = 0;
    do
		{
			i++;
			HumB_temp = dhtc12_read_reg(DHTC12_HUMBL);
			PRINT("HumBL\n");
		}while(HumB_temp==-1&& i<10);
    HumB = (HumB<<8)|HumB_temp;
//    do{HumA = dhtc12_read_reg(DHTC12_HUMAH);}while(HumA==-1);
//    HumA_temp = dhtc12_read_reg(DHTC12_HUMAL);
//    HumA = (HumA<<8)|(HumA_temp&0x00ff);
//    HumB = dhtc12_read_reg(DHTC12_HUMBH);
//    HumB_temp = dhtc12_read_reg(DHTC12_HUMBL);
//    HumB = (HumB<<8)|(HumB_temp&0x00ff);

	return TRUE;
}