#ifndef __BMP280_H__
#define __BMP280_H__

#include "stdint.h"
#include "stdbool.h"

#include "stm32f1xx_hal.h"

#define  BMP280_I2C_ADDRESS_0  0x76
#define  BMP280_I2C_ADDRESS_1  0x77

#define  BMP280_CHIP_ID  0x58
#define  BME280_CHIP_ID  0x60

typedef enum {
    BMP280_MODE_SLEEP = 0,
    BMP280_MODE_FORCED = 1,
    BMP280_MODE_NORMAL = 3
} BMP280_Mode;

typedef enum {
    BMP280_FILTER_OFF = 0,
    BMP280_FILTER_2 = 1,
    BMP280_FILTER_4 = 2,
    BMP280_FILTER_8 = 3,
    BMP280_FILTER_16 = 4
} BMP280_Filter;

typedef enum {
    BMP280_SKIPPED = 0,
    BMP280_ULTRA_LOW_POWER = 1,
    BMP280_LOW_POWER = 2,
    BMP280_STANDARD = 3,
    BMP280_HIGH_RES = 4,
    BMP280_ULTRA_HIGH_RES = 5
} BMP280_Oversampling;

typedef enum {
    BMP280_STANDBY_05 = 0,
    BMP280_STANDBY_62 = 1,
    BMP280_STANDBY_125 = 2,
    BMP280_STANDBY_250 = 3,
    BMP280_STANDBY_500 = 4,
    BMP280_STANDBY_1000 = 5,
    BMP280_STANDBY_2000 = 6,
    BMP280_STANDBY_4000 = 7,
} BMP280_StandbyTime;

typedef struct {
    BMP280_Mode mode;
    BMP280_Filter filter;
    BMP280_Oversampling oversampling_pressure;
    BMP280_Oversampling oversampling_temperature;
    BMP280_Oversampling oversampling_humidity;
    BMP280_StandbyTime standby;
} bmp280_params_t;

typedef struct {
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;
    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;

    uint8_t  dig_H1;
    int16_t  dig_H2;
    uint8_t  dig_H3;
    int16_t  dig_H4;
    int16_t  dig_H5;
    int8_t   dig_H6;

    uint16_t addr;

    I2C_HandleTypeDef* i2c;

    bmp280_params_t params;

    uint8_t id;

} BMP280_HandleTypedef;

void bmp280_init_default_params(bmp280_params_t *params);

bool bmp280_init(BMP280_HandleTypedef *dev, bmp280_params_t *params);

bool bmp280_force_measurement(BMP280_HandleTypedef *dev);

bool bmp280_is_measuring(BMP280_HandleTypedef *dev);

bool bmp280_read_fixed(BMP280_HandleTypedef *dev, int32_t *temperature, uint32_t *pressure, uint32_t *humidity);

bool bmp280_read_float(BMP280_HandleTypedef *dev, float *temperature, float *pressure, float *humidity);

#endif
