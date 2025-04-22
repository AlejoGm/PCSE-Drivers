/*
 * mpu6050_port.c
 *
 *  Created on: Apr 18, 2025
 *      Author: User
 */


#include "mpu6050_port.h"

static mpu6050_port_config_t *port;

static uint8_t mpu_addr = 0;

#define MPU6050_BASE_ADDR 0x68

bool MPU6050_setup(mpu6050_port_config_t *config)
{
    if (!config) return false;
    port = config;
    mpu_addr = MPU6050_BASE_ADDR << 1 | (config->ad0_state ? 0x01 : 0x00); // I2C address shift incluido
    return true;
}

bool MPU6050_WriteReg(uint8_t reg, uint8_t data)
{
    return HAL_I2C_Mem_Write(port->hi2c, mpu_addr, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 100) == HAL_OK;
}

bool MPU6050_ReadBytes(uint8_t reg, uint8_t *buffer, uint16_t len)
{
    return HAL_I2C_Mem_Read(port->hi2c, mpu_addr, reg, I2C_MEMADD_SIZE_8BIT, buffer, len, 100) == HAL_OK;
}
