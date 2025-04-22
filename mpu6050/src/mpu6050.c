#include "mpu6050.h"

static mpu6050_data_t mpu_data;
static mpu6050_settings_t mpu_settings;

bool mpu6050_Init(mpu6050_settings_t *settings)
{
    if (!settings) return false;

    mpu_settings = *settings; // Copiar la configuración

    switch (mpu_settings.accel_range) {
        case MPU6050_ACCEL_2G:  mpu_settings.accel_factor = 1.0f / COUNTS_PER_G_2G; break;
        case MPU6050_ACCEL_4G:  mpu_settings.accel_factor = 1.0f / COUNTS_PER_G_4G;  break;
        case MPU6050_ACCEL_8G:  mpu_settings.accel_factor = 1.0f / COUNTS_PER_G_8G;  break;
        case MPU6050_ACCEL_16G: mpu_settings.accel_factor = 1.0f / COUNTS_PER_G_16G;  break;
    }

    switch (mpu_settings.gyro_range) {
        case MPU6050_GYRO_250DPS:  mpu_settings.gyro_factor = 1.0f / 131.0f;  break;
        case MPU6050_GYRO_500DPS:  mpu_settings.gyro_factor = 1.0f / 65.5f;   break;
        case MPU6050_GYRO_1000DPS: mpu_settings.gyro_factor = 1.0f / 32.8f;   break;
        case MPU6050_GYRO_2000DPS: mpu_settings.gyro_factor = 1.0f / 16.4f;   break;
    }

    // Configurar port
    if(!MPU6050_setup(&settings->port))return false;

    // Salir de sleep y seleccionar fuente de clock
    if (!MPU6050_WriteReg(MPU6050_REG_PWR_MGMT_1, mpu_settings.clk_source)) return false;

    // Sample Rate Divider
    if (!MPU6050_WriteReg(MPU6050_REG_SMPLRT_DIV, mpu_settings.sample_rate_div)) return false;

    // Configurar DLPF
    if (!MPU6050_WriteReg(MPU6050_REG_CONFIG, mpu_settings.dlpf_cfg)) return false;

    // Configurar rango del giroscopio
    if (!MPU6050_WriteReg(MPU6050_REG_GYRO_CONFIG, mpu_settings.gyro_range)) return false;

    // Configurar rango del acelerómetro
    if (!MPU6050_WriteReg(MPU6050_REG_ACCEL_CONFIG, mpu_settings.accel_range)) return false;

    return true;
}

bool MPU6050_ReadAccel(void)
{
    uint8_t buffer[6];
    if (!MPU6050_ReadBytes(MPU6050_REG_ACCEL_XOUT_H, buffer, 6))
        return false;

    mpu_data.accel_x = (int16_t)(buffer[0] << 8 | buffer[1]);
    mpu_data.accel_y = (int16_t)(buffer[2] << 8 | buffer[3]);
    mpu_data.accel_z = (int16_t)(buffer[4] << 8 | buffer[5]);
    return true;
}

bool MPU6050_ReadGyro(void)
{
    uint8_t buffer[6];
    if (!MPU6050_ReadBytes(MPU6050_REG_GYRO_XOUT_H, buffer, 6))
        return false;

    mpu_data.gyro_x = (int16_t)(buffer[0] << 8 | buffer[1]);
    mpu_data.gyro_y = (int16_t)(buffer[2] << 8 | buffer[3]);
    mpu_data.gyro_z = (int16_t)(buffer[4] << 8 | buffer[5]);
    return true;
}

bool MPU6050_ReadTemp(void)
{
    uint8_t buffer[2];
    if (!MPU6050_ReadBytes(MPU6050_REG_TEMP_OUT_H, buffer, 2))
        return false;

    mpu_data.temp_raw = (int16_t)(buffer[0] << 8 | buffer[1]);
    return true;
}

bool MPU6050_ReadAll(void)
{
    return MPU6050_ReadAccel() && MPU6050_ReadTemp() && MPU6050_ReadGyro();
}

const mpu6050_data_t* MPU6050_GetData(void)
{
    return &mpu_data;
}

float MPU6050_ConvertTemp(int16_t raw)
{
    return raw / 340.0f + 36.53f;
}


void MPU6050_GetAccelG(float *x, float *y, float *z)
{
    *x = mpu_data.accel_x * mpu_settings.accel_factor;
    *y = mpu_data.accel_y * mpu_settings.accel_factor;
    *z = mpu_data.accel_z * mpu_settings.accel_factor;
}

void MPU6050_GetGyroDPS(float *x, float *y, float *z)
{
    *x = mpu_data.gyro_x * mpu_settings.gyro_factor;
    *y = mpu_data.gyro_y * mpu_settings.gyro_factor;
    *z = mpu_data.gyro_z * mpu_settings.gyro_factor;
}



