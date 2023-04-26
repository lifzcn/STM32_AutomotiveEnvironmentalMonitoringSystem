#include "sgp30.h"

#define SGP30_Address 0x58

uint8_t data[2];
uint16_t SGP30_InitStatus;
float CO2Value = 0;
float VOCValue = 0;
unsigned char readCO2andVOC_Buffer[7];

void SGP30_Init()
{
	data[0] = (0x2003) >> 8;
	data[1] = (0x2003) & 0x00FF;
	HAL_I2C_Master_Transmit(&hi2c2, SGP30_Address << 1, data, 2, 50);
}

float SGP30_GetCO2andVOC()
{
	data[0] = (0x2008) >> 8;
	data[1] = (0x2008) & 0x00FF;
	SGP30_InitStatus = 0x2008;
	HAL_I2C_Master_Transmit(&hi2c2, SGP30_Address << 1, data, 2, 50);
	HAL_Delay(1000);
	HAL_I2C_Master_Receive(&hi2c2, SGP30_Address << 1, readCO2andVOC_Buffer, 6, 50);
	CO2Value = (readCO2andVOC_Buffer[0] << 8) | readCO2andVOC_Buffer[1];
	VOCValue = (readCO2andVOC_Buffer[3] << 8) | (readCO2andVOC_Buffer[4]);
	return VOCValue;
}
