# DFRobot FireBeetle 2 ESP32-C6

## Overview

The DFRobot FireBeetle 2 ESP32-C6 is a low-power IoT development board based on the ESP32-C6 chip. It supports Wi-Fi 6, Bluetooth 5, Zigbee 3.0, and Thread 1.3 protocols.

## Hardware Features

- **MCU:** ESP32-C6FH4 (RISC-V single-core, 160MHz)
- **Memory:** 512KB SRAM, 320KB ROM, 4MB Flash, 16KB RTC SRAM
- **Connectivity:** Wi-Fi 6, Bluetooth 5, Zigbee 3.0, Thread 1.3
- **Power:** Ultra-low power consumption, solar charging support
- **I/O:** 19 Digital I/O pins
- **Interfaces:** SPI, UART (3x), I2C (2x), I2S, ADC (12-bit, 7 channels)
- **Special Features:** Solar power management, battery level monitoring

## Pin Layout

- **LED:** GPIO15 (D13) - Onboard user LED
- **Button:** GPIO9 (D9) - Boot/User button  
- **Battery:** GPIO0 - Battery voltage detection
- **I2C:** GPIO19 (SDA), GPIO20 (SCL)
- **SPI:** GPIO21 (MISO), GPIO22 (MOSI), GPIO23 (SCLK), GPIO1 (CS)
- **UART:** GPIO16 (TX), GPIO17 (RX)

## Power Supply

- **Type-C:** 5V DC input
- **VCC:** 5V DC or solar panel input
- **Operating Voltage:** 3.3V
- **Sleep Current:** 16µA (V1.0), 36µA (V1.1)

## Building and Flashing

### Building

```bash
west build -b firebeetle2_esp32c6
```

### Flashing

```bash
west flash
```

### Monitoring

```bash
west espressif monitor
```

## Programming and Debugging

The board can be programmed via the onboard USB-to-Serial converter. If you encounter issues:

1. Hold BOOT button
2. Press RESET button  
3. Release BOOT button
4. Try flashing again

## Supported Features

| Interface | Controller | Driver/Component |
| --------- | ---------- | ---------------- |
| GPIO      | on-chip    | gpio_esp32       |
| UART      | on-chip    | serial_esp32     |
| I2C       | on-chip    | i2c_esp32        |
| SPI       | on-chip    | spi_esp32        |
| ADC       | on-chip    | adc_esp32        |
| Watchdog  | on-chip    | watchdog_esp32   |
| Timer     | on-chip    | timer_esp32      |

## References

- [DFRobot FireBeetle 2 ESP32-C6 Wiki](https://wiki.dfrobot.com/SKU_DFR1075_FireBeetle_2_Board_ESP32_C6)
- [ESP32-C6 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-c6_datasheet_en.pdf)
