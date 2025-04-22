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

/**
 * @brief Estructura de configuración del puerto para MPU6050.
 */
typedef struct {
    I2C_HandleTypeDef *hi2c; /**< Handler del periférico I2C utilizado */
    bool ad0_state;          /**< Estado del pin AD0: false = 0x68, true = 0x69 */
} mpu6050_port_config_t;

/**
 * @brief Inicializa la configuración del puerto I2C y dirección del MPU6050.
 * @param config Puntero a la estructura de configuración del puerto.
 * @return true si fue exitoso, false si falló.
 */
bool MPU6050_setup(mpu6050_port_config_t *config);

/**
 * @brief Escribe un valor en un registro del MPU6050.
 * @param reg Dirección del registro.
 * @param data Valor a escribir.
 * @return true si fue exitoso, false si falló.
 */
bool MPU6050_WriteReg(uint8_t reg, uint8_t data);

/**
 * @brief Lee un único byte desde un registro del MPU6050.
 * @param reg Dirección del registro.
 * @param data Puntero donde se guardará el dato leído.
 * @return true si fue exitoso, false si falló.
 */
bool MPU6050_ReadReg(uint8_t reg, uint8_t *data);

/**
 * @brief Lee múltiples bytes desde el MPU6050.
 * @param reg Dirección inicial de lectura.
 * @param buffer Puntero al buffer de destino.
 * @param len Cantidad de bytes a leer.
 * @return true si fue exitoso, false si falló.
 */
bool MPU6050_ReadBytes(uint8_t reg, uint8_t *buffer, uint16_t len);


#endif /* INC_MPU6050_PORT_H_ */
