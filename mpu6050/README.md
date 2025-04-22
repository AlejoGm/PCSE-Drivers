# Driver para Sensor MPU6050 (I2C)

Este proyecto implementa un driver modular en C para el sensor de 6 ejes **MPU6050**, que combina un acelerómetro y un giroscopio digital. El driver fue desarrollado siguiendo una arquitectura en capas, separando la lógica de aplicación del acceso directo al hardware.

## 🧩 Estructura del Proyecto

```
├── inc
│   ├── mpu6050.h            # API del driver de alto nivel
│   └── mpu6050_port.h       # Funciones específicas de hardware (I2C)
├── src
│   ├── mpu6050.c            # Implementación del driver
│   └── mpu6050_port.c       # Acceso al hardware I2C
├── README.md
```

## 🔧 Requisitos

- Sensor MPU6050 (con interfaz I2C)
- Microcontrolador STM32 (ej. NUCLEO-F446RE)
- Biblioteca HAL
- Periférico I2C habilitado

## ⚙️ Funcionalidades

- Configuración inicial del sensor (clock, sample rate, DLPF, rangos)
- Lectura de:
  - Aceleración en 3 ejes
  - Velocidad angular en 3 ejes
  - Temperatura
- Conversión a unidades físicas:
  - G para acelerómetro
  - °/s para giroscopio
  - °C para temperatura

## 🚀 Instrucciones de Uso

1. Configurar los parámetros del sensor:

```c
mpu6050_settings_t settings = {
    .port = {
        .hi2c = &hi2c1,
        .ad0_state = false
    },
    .clk_source = MPU6050_CLK_PLL_XGYRO,
    .sample_rate_div = 7,
    .dlpf_cfg = MPU6050_DLPF_94HZ,
    .gyro_range = MPU6050_GYRO_500DPS,
    .accel_range = MPU6050_ACCEL_4G
};
mpu6050_Init(&settings);
```

2. Leer datos:

```c
MPU6050_ReadAll();
const mpu6050_data_t* data = MPU6050_GetData();
```

3. Obtener datos en unidades físicas:

```c
float ax, ay, az;
float gx, gy, gz;

MPU6050_GetAccelG(&ax, &ay, &az);
MPU6050_GetGyroDPS(&gx, &gy, &gz);
```

## 🧪 Ejemplo de Integración

Puede integrarse fácilmente en proyectos embebidos periódicos o RTOS donde se requiera adquisición de datos inercial.


## 👨‍💻 Autor

Alejo García  

 
Proyecto desarrollado para la materia *Protocolos de Comunicación en Sistemas Embebidos* (Posgrado en Sistemas Embebidos)