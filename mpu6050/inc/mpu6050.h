/*
 * mpu6050.h
 *
 *  Created on: Apr 18, 2025
 *      Author: User
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "mpu6050_port.h"

#define MPU6050_REG_PWR_MGMT_1    0x6B
#define MPU6050_REG_SMPLRT_DIV    0x19
#define MPU6050_REG_CONFIG        0x1A
#define MPU6050_REG_GYRO_CONFIG   0x1B
#define MPU6050_REG_ACCEL_CONFIG  0x1C
#define MPU6050_REG_ACCEL_XOUT_H  0x3B
#define MPU6050_REG_TEMP_OUT_H    0x41
#define MPU6050_REG_GYRO_XOUT_H   0x43

#define COUNTS_PER_G_2G    16384.0f
#define COUNTS_PER_G_4G     8192.0f
#define COUNTS_PER_G_8G     4096.0f
#define COUNTS_PER_G_16G    2048.0f

#define COUNTS_PER_DPS_250   131.0f
#define COUNTS_PER_DPS_500    65.5f
#define COUNTS_PER_DPS_1000   32.8f
#define COUNTS_PER_DPS_2000   16.4f

/**
 * @brief Estructura que contiene los datos brutos del sensor MPU6050.
 */
typedef struct {
    int16_t accel_x; /**< Aceleración eje X */
    int16_t accel_y; /**< Aceleración eje Y */
    int16_t accel_z; /**< Aceleración eje Z */
    int16_t temp_raw; /**< Temperatura sin convertir */
    int16_t gyro_x; /**< Velocidad angular eje X */
    int16_t gyro_y; /**< Velocidad angular eje Y */
    int16_t gyro_z; /**< Velocidad angular eje Z */
} mpu6050_data_t;


/** @brief Opciones de fuente de reloj. */
typedef enum {
    MPU6050_CLK_INTERNAL = 0x00,
    MPU6050_CLK_PLL_XGYRO = 0x01,
    MPU6050_CLK_PLL_YGYRO = 0x02,
    MPU6050_CLK_PLL_ZGYRO = 0x03,
    MPU6050_CLK_PLL_EXT32K = 0x04,
    MPU6050_CLK_PLL_EXT19M = 0x05
} mpu6050_clock_source_t;

/** @brief Configuraciones posibles para el filtro DLPF. */
typedef enum {
    MPU6050_DLPF_260HZ = 0x00,
    MPU6050_DLPF_184HZ = 0x01,
    MPU6050_DLPF_94HZ  = 0x02,
    MPU6050_DLPF_44HZ  = 0x03,
    MPU6050_DLPF_21HZ  = 0x04,
    MPU6050_DLPF_10HZ  = 0x05,
    MPU6050_DLPF_5HZ   = 0x06
} mpu6050_dlpf_t;

/** @brief Rangos configurables del giroscopio. */
typedef enum {
    MPU6050_GYRO_250DPS  = 0x00,
    MPU6050_GYRO_500DPS  = 0x08,
    MPU6050_GYRO_1000DPS = 0x10,
    MPU6050_GYRO_2000DPS = 0x18
} mpu6050_gyro_range_t;

/** @brief Rangos configurables del acelerómetro. */
typedef enum {
    MPU6050_ACCEL_2G  = 0x00,
    MPU6050_ACCEL_4G  = 0x08,
    MPU6050_ACCEL_8G  = 0x10,
    MPU6050_ACCEL_16G = 0x18
} mpu6050_accel_range_t;

/**
 * @brief Configuración completa del sensor MPU6050.
 */
typedef struct {
	mpu6050_port_config_t port; /**< Configuración del puerto I2C */
    mpu6050_clock_source_t clk_source; /**< Fuente de reloj */
    uint8_t sample_rate_div; /**< Divisor de tasa de muestreo */
    mpu6050_dlpf_t dlpf_cfg; /**< Configuración del filtro DLPF */
    mpu6050_gyro_range_t gyro_range; /**< Rango del giroscopio */
    mpu6050_accel_range_t accel_range; /**< Rango del acelerómetro */
    float accel_factor; /**< Factor de conversión a G */
    float gyro_factor; /**< Factor de conversión a °/s */
} mpu6050_settings_t;

/**
 * @brief Inicializa el sensor MPU6050 con la configuración especificada.
 *
 * Esta función aplica todos los parámetros de configuración definidos en
 * la estructura `mpu6050_settings_t`, como el rango del acelerómetro, el
 * rango del giroscopio, la frecuencia de muestreo y el filtro DLPF.
 *
 * También se encarga de inicializar el puerto I2C y preparar el sensor para
 * lecturas posteriores. Es el primer paso obligatorio antes de utilizar el
 * sensor.
 *
 * @param settings Puntero a la estructura de configuración completa.
 * @return true si la inicialización fue exitosa, false en caso contrario.
 */
bool mpu6050_Init(mpu6050_settings_t *settings);

/** @brief Lee valores del acelerómetro. */
bool MPU6050_ReadAccel(void);

/** @brief Lee valores del giroscopio. */
bool MPU6050_ReadGyro(void);

/** @brief Lee la temperatura cruda del sensor. */
bool MPU6050_ReadTemp(void);

/** @brief Lee acelerómetro, giroscopio y temperatura. */
bool MPU6050_ReadAll(void);

/** @brief Retorna un puntero constante a los últimos datos leídos. */
const mpu6050_data_t* MPU6050_GetData(void);

/** @brief Convierte la temperatura cruda a grados Celsius. */
float MPU6050_ConvertTemp(int16_t raw);

/** @brief Devuelve aceleración en Gs. */
void MPU6050_GetAccelG(float *x, float *y, float *z);

/** @brief Devuelve velocidad angular en °/s. */
void MPU6050_GetGyroDPS(float *x, float *y, float *z);


#endif /* INC_MPU6050_H_ */
