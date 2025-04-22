/*
 * ledMatrix.h
 *
 *  Created on: Apr 18, 2025
 *      Author: Alejo Garcia Mata
 */

#ifndef INC_LEDMATRIX_H_
#define INC_LEDMATRIX_H_
#include "ledMatrix_port.h"

#define LED_MATRIX_MAX_INTENISITY_VALUE 0x0F


/**
 * @brief Códigos de error del driver LedMatrix.
 */
typedef enum{
	LEDMATRIX_OK,              /**< Operación exitosa */
	LEDMATRIX_INVALID_ARG,     /**< Argumento inválido */
	LEDMATRIX_ERROR,           /**< Error genérico */
}LedMatrix_err_t;

/**
 * @brief Actualiza solo las filas modificadas desde la última llamada.
 * @return LEDMATRIX_OK si tuvo éxito, LEDMATRIX_ERROR si falló.
 */
LedMatrix_err_t LedMatrix_Refresh(void);

/**
 * @brief Fuerza la actualización de todas las filas de la matriz.
 * @return LEDMATRIX_OK si tuvo éxito, LEDMATRIX_ERROR si falló.
 */
LedMatrix_err_t LedMatrix_ForceRefresh(void);

/**
 * @brief Configura el MAX7219 con los parámetros de hardware.
 * @param config Puntero a la estructura de configuración.
 * @return LEDMATRIX_OK o LEDMATRIX_INVALID_ARG si config es NULL.
 */
LedMatrix_err_t LedMatrix_setup(max7219_config_t* config);

/**
 * @brief Inicializa el MAX7219 con parámetros por defecto.
 * @return LEDMATRIX_OK o LEDMATRIX_ERROR.
 */
LedMatrix_err_t LedMatrix_Init(void);

/**
 * @brief Establece la intensidad de brillo de la matriz.
 * @param intensity Valor entre 0 y 15.
 * @return LEDMATRIX_OK o LEDMATRIX_ERROR.
 */
LedMatrix_err_t LedMatrix_intensity(uint8_t intensity);

/**
 * @brief Limpia todo el contenido de la matriz.
 */
void LedMatrix_Clear(void);


/**
 * @brief Setea o limpia un pixel específico.
 * @param x Coordenada horizontal (0–7).
 * @param y Coordenada vertical (0–7).
 * @param state 1 para encender, 0 para apagar.
 */
void LedMatrix_SetPixel(uint8_t x, uint8_t y, uint8_t state);

/**
 * @brief Enciende un único pixel y apaga el anterior encendido.
 * @param x Coordenada x del nuevo pixel.
 * @param y Coordenada y del nuevo pixel.
 */
void LedMatrix_SetSinglePixel(uint8_t x, uint8_t y);

/**
 * @brief Dibuja un bloque de 2x2 a partir de coordenadas dadas.
 * @param x Coordenada horizontal base.
 * @param y Coordenada vertical base.
 * @param state Reservado para futura implementación.
 */
void LedMatrix_SetBlock(uint8_t x, uint8_t y, uint8_t state);


/**
 * @brief Carga un bitmap en la matriz.
 * @param bitmap Array de 8 bytes, uno por fila.
 */
void LedMatrix_LoadBitmap(const uint8_t bitmap[8]);

/**
 * @brief Efecto de barrido circular hacia la izquierda.
 */
void LedMatrix_SweepLeft_Circular(void);

/**
 * @brief Efecto de barrido hacia la derecha.
 */
void LedMatrix_SweepRight(void);

#endif /* INC_LEDMATRIX_H_ */
