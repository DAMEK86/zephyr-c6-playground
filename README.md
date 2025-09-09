# DFRobot FireBeetle 2 ESP32-C6 LED Blink Application

Diese Zephyr-Anwendung lässt die onboard LED auf dem DFRobot FireBeetle 2 ESP32-C6 Board blinken.

## Übersicht

- **Board**: DFRobot FireBeetle 2 ESP32-C6 (kompatibel mit esp32c6_devkitc)
- **Zephyr Version**: 4.2.0
- **LED**: Onboard LED an GPIO15 (D13)
- **Typ**: Einfache Ein/Aus LED

## Funktionen

- LED blinkt alle 1 Sekunde
- Logging-Ausgabe über UART
- GPIO-basierte LED-Kontrolle

## Setup

### Erstmalige Einrichtung

```bash
west init -l .
west update
```

### Build und Flash

```bash
# Build
west build -b esp32c6_devkitc

# Flash
sudo west flash

# Monitor
west espressif monitor
```

## Projektstruktur

```
zephyr-c6-playground/
├── CMakeLists.txt          # Haupt-CMake-Datei
├── prj.conf                # Kconfig-Konfiguration
├── app.overlay             # Device Tree Overlay
├── west.yml                # West-Manifest
├── src/
│   └── main.c              # Hauptanwendung
└── README.md               # Diese Datei
```

## Konfiguration

### prj.conf
- `CONFIG_GPIO=y` - GPIO Unterstützung

### app.overlay
- Definiert LED an GPIO15 als led0
- GPIO_ACTIVE_HIGH Konfiguration

## Hardware

Das DFRobot FireBeetle 2 ESP32-C6 hat eine onboard LED an GPIO15 (D13 in Arduino-Notation).

## Troubleshooting

- Überprüfen Sie die USB-Verbindung
- Stellen Sie sicher, dass die richtigen Treiber installiert sind
- Bei Build-Fehlern: `west build -t pristine` ausführen