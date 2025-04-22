/*
 * mpu6050_ort.h
 *
 *  Created on: Apr 18, 2025
 *      Author: User
 */

#ifndef INC_MPU6050_PORT_H_
#define INC_MPU6050_PORT_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

typedef struct {
    I2C_HandleTypeDef *hi2c;
    bool ad0_state;  // false = GND (0x68), true = VCC (0x69)
} mpu6050_port_config_t;


bool MPU6050_setup(mpu6050_port_config_t *config);
bool MPU6050_WriteReg(uint8_t reg, uint8_t data);
bool MPU6050_ReadReg(uint8_t reg, uint8_t *data);
bool MPU6050_ReadBytes(uint8_t reg, uint8_t *buffer, uint16_t len);


#endif /* INC_MPU6050_PORT_H_ */
