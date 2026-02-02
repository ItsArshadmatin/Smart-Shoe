# Hardware Components – Smart Shoe System

This document lists all physical components used to build the Smart Shoe IoT Fitness & Safety System. The goal is to provide a clear Bill of Materials (BOM) for reproduction, repair, or future upgrades.

---

## Core Processing Unit

### ESP32 Microcontroller

* Dual-core 32-bit microcontroller with built-in Wi-Fi & Bluetooth
* Operating voltage: 3.3V
* Used as the main controller for sensor processing and wireless communication
* Handles step detection, fall detection, GPS parsing, Firebase sync, and Telegram alerts

---

## Sensors

### GY-61 Accelerometer (ADXL335)

* 3-axis analog accelerometer
* Measures motion, orientation, roll & pitch
* Used for gait analysis and fall detection
* Output connected to ESP32 ADC pins

### Piezoelectric Pressure Sensor

* Passive pressure sensor embedded in shoe sole
* Generates voltage spike on foot impact
* Used for step detection and pressure analysis
* No external power required

### Neo-6M GPS Module

* u-blox GPS receiver
* Provides real-time latitude & longitude
* UART serial communication with ESP32
* Used for live tracking and emergency location alerts

---

## Power System

### 3.7V Lithium-Ion Battery

* Rechargeable Li-ion cell
* Powers the entire wearable system
* Lightweight and compact for wearable integration

### Voltage Regulation Components

* Capacitors and passive components for stable power delivery
* Ensures safe 3.3V operation for ESP32 and sensors

---

## Structural Hardware

### Custom PCB Board

* Single-layer compact PCB
* Designed using Fritzing/Proteus
* Mounts ESP32, sensors, and regulators
* Embedded inside waterproof shoe enclosure

### Wiring & Connectors

* Flexible insulated wires
* Embedded into sole for piezo sensor routing
* Shock-resistant cable management

---

## Optional / Future Upgrades

### TP4056 Charging Module (Planned)

* Lithium battery charging controller
* USB charging capability
* For future portable charging integration

---

## Summary BOM

| Component             | Quantity |
| --------------------- | -------- |
| ESP32 Microcontroller | 1        |
| GY-61 Accelerometer   | 1        |
| Piezoelectric Sensor  | 1        |
| Neo-6M GPS Module     | 1        |
| 3.7V Li-ion Battery   | 1        |
| Custom PCB            | 1        |
| Passive Components    | Multiple |

---

This hardware configuration enables real-time wearable fitness tracking, fall detection, GPS safety monitoring, and cloud communication.
