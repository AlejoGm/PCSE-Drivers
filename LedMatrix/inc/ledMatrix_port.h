/**
 * @file ledMatrix_port.h
 * @brief Funciones de bajo nivel para comunicación con el controlador MAX7219.
 **  Created on: Apr 18, 2025
 *      Author: Alejo Garcia Mata
 */

#ifndef INC_LEDMATRIX_PORT_H_
#define INC_LEDMATRIX_PORT_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

/**
 * @brief Estructura de configuración para el dispositivo MAX7219.
 */
typedef struct{
	SPI_HandleTypeDef* hspi;         /**< Handler del periférico SPI */
	GPIO_TypeDef * CS_GPIO_PORT;     /**< Puerto GPIO para Chip Select */
	uint16_t CS_GPIO_PIN;            /**< Pin GPIO para Chip Select */
}max7219_config_t;

/**
 * @brief Inicializa el contexto de configuración del MAX7219.
 * @param config Puntero a la configuración del dispositivo.
 * @return true si fue exitoso, false en caso de error.
 */
bool MAX7219_setup(max7219_config_t* config);

/**
 * @brief Envía un byte de datos al MAX7219.
 * @param reg Dirección del registro del MAX7219.
 * @param data Valor a escribir.
 * @return true si la transmisión SPI fue exitosa, false en caso contrario.
 */
bool MAX7219_Write(uint8_t reg, uint8_t data);

#endif /* INC_LEDMATRIX_PORT_H_ */
