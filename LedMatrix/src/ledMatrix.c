/*
 * ledMatrix.c
 *
 *  Created on: Apr 18, 2025
 *      Author: Alejo Garcia Mata
 */

#include "ledMatrix.h"

static uint8_t max7219_buffer[8] = {0};  // Cada byte representa una fila (DIG1–DIG8)
static uint8_t update_flags = 0;         // Bit i = 1 → fila i necesita actualización

static void LedMatrix_WriteRow(uint8_t row, uint8_t value)
{
    if (row >= 8) return;
    if (max7219_buffer[row] != value) {
        max7219_buffer[row] = value;
        update_flags |= (1 << row);
    }
}

LedMatrix_err_t LedMatrix_Refresh(void){
    bool ret = true;
    for (uint8_t row = 0; update_flags; row++){
        if (update_flags & (1 << row)){
            ret &= MAX7219_Write(row + 1, max7219_buffer[row]);
            update_flags &= ~(1 << row);
        }
    }
    return ret ? LEDMATRIX_OK : LEDMATRIX_ERROR;
}

LedMatrix_err_t LedMatrix_ForceRefresh(void){
    update_flags = 0xFF;  // Marcar todas las filas a cambiar
    return LedMatrix_Refresh();
}

LedMatrix_err_t LedMatrix_setup(max7219_config_t* config){
    if (!config) {
        return LEDMATRIX_INVALID_ARG;
    }
    return MAX7219_setup(config) ? LEDMATRIX_OK : LEDMATRIX_ERROR;
}

LedMatrix_err_t LedMatrix_Init(void) {
	bool ret = true;
	ret &= MAX7219_Write(0x0F, 0x00); // Display test: off
	ret &= MAX7219_Write(0x0C, 0x01); // Shutdown: normal operation
	ret &= MAX7219_Write(0x0B, 0x07); // Scan limit: digits 0–7
	ret &= LedMatrix_intensity(LED_MATRIX_MAX_INTENISITY_VALUE) == LEDMATRIX_OK;
	ret &= MAX7219_Write(0x09, 0x00); // No decode
	ret &= LedMatrix_ForceRefresh() == LEDMATRIX_OK;
	return ret ? LEDMATRIX_OK : LEDMATRIX_ERROR;
}

LedMatrix_err_t LedMatrix_intensity(uint8_t intensity) {
	if (intensity > LED_MATRIX_MAX_INTENISITY_VALUE)
		intensity = LED_MATRIX_MAX_INTENISITY_VALUE;
	return MAX7219_Write(0x0A, intensity) ? LEDMATRIX_OK : LEDMATRIX_ERROR;
}

void LedMatrix_Clear(void){
    for (int i = 0; i < 8; i++) LedMatrix_WriteRow(i, 0);
}

void LedMatrix_SetPixel(uint8_t x, uint8_t y, uint8_t state){
    if (x > 7 || y > 7) return;

    uint8_t mask = 1 << x;
    uint8_t value = max7219_buffer[y];

    if (state) value |= mask;
    else value &= ~mask;

    LedMatrix_WriteRow(y, value);
}

void LedMatrix_SetSinglePixel(uint8_t x, uint8_t y)
{
    static int last_x = -1;
    static int last_y = -1;

    if (x > 7 || y > 7) return;

    // Apagar el punto anterior si era válido
    if (last_x >= 0 && last_y >= 0){
        LedMatrix_SetPixel(last_x, last_y, 0);
    }

    // Encender el nuevo punto
    LedMatrix_SetPixel(x, y, 1);

    // Actualizar el estado actual
    last_x = x;
    last_y = y;
}

void LedMatrix_SetBlock(uint8_t virtual_x, uint8_t virtual_y, uint8_t state)
{
	uint8_t p[4];
	p[0]=virtual_x;
	p[1]=virtual_x-1;
	p[2]=virtual_y;
	p[3]=virtual_y-1;
	for(int i=0;i<2;i++){
		for(int ii=2;ii<4;ii++){
		  LedMatrix_SetPixel(p[i], p[ii], state);
		}
	}
}

void LedMatrix_LoadBitmap(const uint8_t bitmap[8]){
    for (int i = 0; i < 8; i++) {
        LedMatrix_WriteRow(i, bitmap[i]);
    }
}

void LedMatrix_SweepLeft_Circular(void){
    for (int i = 0; i < 8; i++) {
        uint8_t msb = (max7219_buffer[i] & 0x80) >> 7;
        uint8_t value = (max7219_buffer[i] << 1) | msb;
        LedMatrix_WriteRow(i, value);
    }
}

void LedMatrix_SweepRight(void){
    for (int i = 0; i < 8; i++) {
        uint8_t value = max7219_buffer[i] >> 1;
        LedMatrix_WriteRow(i, value);
    }
}
