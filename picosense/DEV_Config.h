#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_
/***********************************************************************************************************************
                        ------------------------------------------------------------------------
                        |\\\
///|
                        |\\\					Hardware
interface							///|
                        ------------------------------------------------------------------------
***********************************************************************************************************************/
#include "Arduino.h"
#include "Debug.h"
#include "Wire.h"

#define DEV_SPI 0
#define DEV_I2C 1

/**
 * I2C config
 **/
#define OLED_I2C_PORT (1)
#define OLED_SDA_PIN (6)
#define OLED_SCL_PIN (7)

#define SENSOR_I2C_PORT (0)
#define SENSOR_SDA_PIN (8)
#define SENSOR_SCL_PIN (9)

/*------------------------------------------------------------------------------------------------------*/
void DEV_Delay_ms(uint32_t xms);

void DEV_I2C_Write_Byte(uint8_t i2c_num, uint8_t addr, uint8_t value);
void DEV_I2C_Write_nByte(uint8_t i2c_num, uint8_t addr, uint8_t *pData,
                         uint32_t len);

void DEV_I2C_Write_Reg_Byte(uint8_t i2c_num, uint8_t addr, uint8_t reg,
                            uint8_t value);
void DEV_I2C_Write_Reg_nByte(uint8_t i2c_num, uint8_t addr, uint8_t reg,
                             uint8_t *pData, uint32_t len);

uint8_t DEV_I2C_Read_Byte(uint8_t i2c_num, uint8_t addr);
void DEV_I2C_Read_nByte(uint8_t i2c_num, uint8_t addr, uint8_t *pData,
                        uint32_t len);

uint8_t DEV_I2C_Read_Reg_Byte(uint8_t i2c_num, uint8_t addr, uint8_t reg);
void DEV_I2C_Read_Reg_nByte(uint8_t i2c_num, uint8_t addr, uint8_t reg,
                            uint8_t *pData, uint32_t len);

uint8_t DEV_ModuleInit(void);
void DEV_ModuleExit(void);
#endif
