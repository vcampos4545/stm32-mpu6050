# STM32 MPU6050 I2C Data Logger

Bare-metal C project for STM32F411CEU6 Black Pill to read accelerometer and gyroscope data from MPU6050 sensor via I2C and log it over UART.

## Hardware Connections

| Peripheral | Pin  | Function |
|------------|------|----------|
| I2C1 SCL   | PB6  | Clock line to MPU6050 |
| I2C1 SDA   | PB7  | Data line to MPU6050 |
| UART2 TX   | PA2  | Serial output (115200 baud) |
| LED        | PC13 | Built-in LED (active low) |

**MPU6050**: I2C address 0x68 (AD0 pin = GND)

## Project Structure

```
stm32-i2c/
├── inc/                    # Header files
│   ├── stm32f411.h        # STM32F411 register definitions
│   ├── i2c.h              # I2C driver interface
│   ├── uart.h             # UART driver interface
│   ├── mpu6050.h          # MPU6050 sensor interface
│   ├── led.h              # LED control interface
│   └── utils.h            # Utility functions (delay, etc.)
├── src/                    # Implementation files
│   ├── i2c.c              # I2C driver implementation
│   ├── uart.c             # UART driver implementation
│   ├── mpu6050.c          # MPU6050 sensor driver
│   ├── led.c              # LED control implementation
│   └── utils.c            # Utility functions
├── main.c                  # Application entry point
├── Makefile                # Build configuration
├── STM32F411CEU6.ld        # Linker script
└── startup_stm32f411xe.s   # Startup assembly code
```

## Building

```bash
make
```

Output files in `build/`:
- `stm32_mpu6050.elf` - ELF executable
- `stm32_mpu6050.hex` - Intel HEX format
- `stm32_mpu6050.bin` - Raw binary

## Flashing

### ST-Link
```bash
make flash
```

### OpenOCD
```bash
make flash-openocd
```

### DFU (USB, no ST-Link needed)
```bash
make flash-dfu
```

## Viewing Output

Connect a USB-to-Serial adapter:
- **STM32 PA2 (TX)** → Adapter RX
- **STM32 GND** → Adapter GND

Serial terminal settings: **115200 baud, 8N1**

Example output:
```
=== STM32 MPU6050 Data Logger ===
Initializing...
MPU6050 WHO_AM_I: 0x68
MPU6050 found! Starting data logging...

Accel: X=-1024 Y=256 Z=16384 | Gyro: X=12 Y=-45 Z=3
Accel: X=-1020 Y=260 Z=16380 | Gyro: X=10 Y=-42 Z=1
...
```

## Module Overview

### stm32f411.h
All STM32F411 hardware register addresses and bit definitions.

### i2c.c / i2c.h
I2C1 driver operating at 100 kHz in master mode.

### uart.c / uart.h
UART2 driver for serial logging at 115200 baud.

### mpu6050.c / mpu6050.h
MPU6050 6-axis IMU driver. Reads accelerometer and gyroscope data.

### led.c / led.h
Simple LED control for visual feedback.

### utils.c / utils.h
Utility functions like busy-wait delay.

## License

Public domain / MIT - use as you wish!
