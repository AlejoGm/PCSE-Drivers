# LedMatrix Driver para MAX7219

Este proyecto implementa un driver modular en C para el control de una matriz de LEDs 8x8 utilizando el chip controlador **MAX7219**, diseñado para plataformas **STM32**. El desarrollo sigue el enfoque de separación de capas y estructura orientada a drivers, según lo visto en la asignatura **Protocolos de Comunicación en Sistemas Embebidos**.

## 🧩 Estructura del Proyecto

```
├── inc
│   ├── ledMatrix.h          # API del driver
│   └── ledMatrix_port.h     # Funciones de bajo nivel (porting)
├── src
│   ├── ledMatrix.c          # Lógica de la matriz LED
│   └── ledMatrix_port.c     # Implementación hardware-dependiente
├── README.md
```

## 🔧 Requisitos

- Microcontrolador STM32 (ej. NUCLEO-F446RE)
- Biblioteca HAL
- Periférico SPI habilitado
- Matriz de LEDs controlada por MAX7219

## ⚙️ Funcionalidades

- Control por SPI del chip MAX7219
- Encendido y apagado de píxeles individuales
- Carga de bitmaps personalizados
- Efectos de desplazamiento (izquierda circular y derecha)
- Dibujo de bloques 2x2
- Configuración de intensidad
- Limpieza total de la matriz

## 🚀 Instrucciones de Uso

1. Inicializar el hardware:

```c
max7219_config_t config = {
    .hspi = &hspi1,
    .CS_GPIO_PORT = GPIOA,
    .CS_GPIO_PIN = GPIO_PIN_4
};
LedMatrix_setup(&config);
```

2. Iniciar el MAX7219:

```c
LedMatrix_Init();
```

3. Encender un pixel:

```c
LedMatrix_SetPixel(3, 5, 1);
LedMatrix_Refresh();
```

4. Cargar un bitmap:

```c
uint8_t smiley[8] = {0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C};
LedMatrix_LoadBitmap(smiley);
LedMatrix_Refresh();
```

## 🧪 Ejemplo de Integración

Este driver puede integrarse fácilmente en proyectos con bucles de polling, utilizando `LedMatrix_Refresh()` de manera periódica o tras cada cambio.

## 👨‍💻 Autor

Alejo García Mata 
Proyecto desarrollado para la materia *Protocolos de Comunicación en Sistemas Embebidos* (Posgrado en Sistemas Embebidos)