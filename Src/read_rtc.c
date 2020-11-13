///*
// * rtc.c
// *
// *  Created on: Nov 12, 2020
// *      Author: ludivineo
// */
//
////#include "stm32f4xx_hal_i2c.h"
//#include "main.h"
//
//
//extern I2C_HandleTypeDef hi2c1;
//
//
//void extract_rtc_data(){
//	int buffer[100] = { 0 };
//	uint16_t addr = 1101000;
//	//uint8_t *pData;
//	uint16_t size = 100;
//	uint32_t timeout = 10;
//
//	HAL_I2C_Master_Transmit(&hi2c1, addr, (uint8_t*)buffer, size, timeout);
//
//}
