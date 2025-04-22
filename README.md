# PCSE-Drivers

Este repositorio contiene el desarrollo de drivers modulares en C para dos dispositivos ampliamente utilizados en sistemas embebidos:

- **MPU6050**: Sensor inercial de 6 ejes con comunicación I2C.
- **MAX7219**: Controlador de matriz LED con interfaz SPI.

Los drivers fueron desarrollados como parte del **Trabajo Integrador** de la materia *Protocolos de Comunicación en Sistemas Embebidos*, correspondiente al Posgrado en Sistemas Embebidos.

---

## 🧱 Estructura del repositorio

```
/PCSE-Drivers
├── mpu6050/
│   ├── inc/
│   │   └── mpu6050.h, mpu6050_port.h
│   └── src/
│       └── mpu6050.c, mpu6050_port.c
├── ledMatrix/
    ├── inc/
    │   └── ledMatrix.h, ledMatrix_port.h
    └── src/
        └── ledMatrix.c, ledMatrix_port.c
```

---

## 🔧 Características

- Drivers modulares con capa de porting (`*_port.c`) para facilitar su uso en distintas plataformas.
- Separación entre lógica de dispositivo y acceso al hardware.
- Compatible con HAL de STM32 (STM32CubeIDE).

---

## 📄 Documentación adicional

- [Datasheet MPU6050](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf)
- [Datasheet MAX7219](https://www.analog.com/media/en/technical-documentation/data-sheets/MAX7219-MAX7221.pdf)

---

## 👨‍💻 Autor

**Alejo S. García Mata**  
Proyecto desarrollado para el Posgrado en Sistemas Embebidos – 2025.
