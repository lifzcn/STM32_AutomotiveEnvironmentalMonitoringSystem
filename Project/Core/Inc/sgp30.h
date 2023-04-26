#ifndef __SGP30_H__
#define __SGP30_H__

#include "stm32f1xx_hal.h"
#include "main.h"
#include "i2c.h"

void SGP30_Init();
float SGP30_GetCO2andVOC();

#endif
