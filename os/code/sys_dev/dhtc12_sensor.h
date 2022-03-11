/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-21 11:18:54
 * @LastEditTime: 2022-03-01 16:54:05
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_dev\dhtc12_sensor.h
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#ifndef _DHTC12_SENSOR_H_
#define _DHTC12_SENSOR_H_
#include "base_typle.h"

#define DHTC12_ADDR                     0X44
#define DHTC12_RESET            0X30A2
#define DHTC12_MEAS_ALL              0X2C10
#define DHTC12_TEMP             0XCC44
#define DHTC12_HUMIDITY         0XCC66
#define DHTC12_HUMAH            0XD208
#define DHTC12_HUMAL            0XD209
#define DHTC12_HUMBH            0XD210
#define DHTC12_HUMBL            0XD206

uint16_t get_humA();
uint16_t get_humB();
uint8_t SHT3x_CheckCrc(uint8_t data[], uint8_t nbrOfBytes);
int32_t dhtc12_read_reg(uint16_t command);
boolean_t dhtc12_rest();
boolean_t dhtc12_read_all(int16_t *tem,uint16_t *Hum);
boolean_t dhtc12_init();


#endif

