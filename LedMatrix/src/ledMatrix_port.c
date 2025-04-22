/*
 * ledMatrix_port.c
 *
 */
#include "ledMatrix_port.h"

static max7219_config_t* port;

bool MAX7219_setup(max7219_config_t* config){
	if(!config)return false;
	port = config;
	return true;
}

bool MAX7219_Write(uint8_t reg, uint8_t data)
{
    uint16_t frame = (reg << 8) | data;

    HAL_GPIO_WritePin(port->CS_GPIO_PORT, port->CS_GPIO_PIN, GPIO_PIN_RESET);

    bool ret = HAL_SPI_Transmit(port->hspi, (uint8_t*)&frame, 1, 100) == HAL_OK;

    HAL_GPIO_WritePin(port->CS_GPIO_PORT, port->CS_GPIO_PIN, GPIO_PIN_SET);

    return ret;
}
