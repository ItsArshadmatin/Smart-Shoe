# 👟 Smart Shoe IoT Fitness & Safety System

An embedded IoT wearable system that integrates fitness tracking, fall detection, GPS safety monitoring, and real-time cloud synchronization using an ESP32 microcontroller and a custom mobile application.

This project demonstrates a full-stack wearable architecture combining hardware sensors, embedded firmware, cloud backend, and mobile UI for real-time monitoring and emergency response.

---

## 🚀 Overview

The Smart Shoe system is designed to:

- Track steps, distance, and calories
- Monitor gait and orientation
- Detect falls in real time
- Send emergency GPS alerts
- Sync activity data to the cloud
- Display live data in a mobile app

Applications include:

- Fitness tracking
- Elderly safety monitoring
- Rehabilitation support
- Athlete performance analysis
- Personal safety during outdoor activity

---

## ✨ Features

- Hybrid step detection (piezo + accelerometer)
- Fall detection using roll & pitch analysis
- Real-time GPS tracking
- Telegram emergency alert system
- Firebase Firestore cloud sync
- Flutter mobile application (We-Fit)
- OpenStreetMap live location display
- Battery-powered wearable module

---

## 🧠 System Architecture

Sensors → ESP32 → WiFi → Firebase → Mobile App  
              ↓  
          Telegram Alerts

- Piezoelectric sensor detects foot impact
- Accelerometer validates movement & orientation
- GPS module provides live coordinates
- ESP32 processes all sensor logic
- Firebase stores real-time data
- Mobile app visualizes activity
- Telegram bot handles emergency alerts

---

## 🔩 Hardware Components

| Component             |Purpose                            |
|-----------------------|-----------------------------------|
| ESP32 Microcontroller | Main controller + WiFi/Bluetooth  |
| GY-61 Accelerometer   | Motion + fall detection           |
| Piezo Sensor          | Step detection                    |
| Neo-6M GPS Module     | Location tracking                 |
| 3.7V Li-ion Battery   | Power supply                      |


Full hardware BOM → see `Hardware/components.md`

---

## 💻 Software Stack

- Firmware: Arduino IDE (C/C++)
- Cloud Backend: Firebase Firestore
- Mobile App: FlutterFlow (We-Fit)
- Maps: OpenStreetMap
- Alerts: Telegram Bot API
- Libraries: TinyGPS++, ArduinoJson, HTTPClient

---

## 🧮 Algorithms

Step Detection  
Interrupt-based piezo trigger + acceleration validation

Distance Calculation  
distance = stepCount / 1.25

Calories Estimation  
calories = stepCount × 0.04

Fall Detection  
Roll & pitch threshold + time persistence filtering

Emergency Protocol  
Automatic Telegram alert with GPS link

---

## 📊 Performance Results

| Parameter       | Result   |
|-----------------|----------|
| Step Accuracy   | 95–98%   |
| Distance Error  | < 2%     |
| Alert Delay     | 2–3 sec  |
| GPS Accuracy    |5–10 m    |
| Battery Runtime | ~7 hours |
| Bluetooth Range | ~9 m     |

Tested across indoor & outdoor real-world conditions.

---

## 📱 Mobile Application

The We-Fit mobile app provides:

- Real-time step tracking
- Distance & calorie display
- Live GPS location
- Emergency alert status
- Cloud sync with Firebase

(Add screenshots in `/media/screenshots`)

---

## 🛠 How to Run

1. Clone repo

git clone https://github.com/yourusername/smart-shoe-iot

2. Open firmware

firmware/smartshoe.ino

3. Create config.h

#define WIFI_SSID "your_wifi"
#define WIFI_PASS "your_password"
#define FIREBASE_KEY "your_key"
#define TELEGRAM_TOKEN "your_token"

4. Upload to ESP32 using Arduino IDE

---

## 📷 Demo

(Add photos & demo video in `/media`)

- Prototype shoe
- PCB inside casing
- App interface
- Live test

---

## 🔮 Future Improvements

- USB charging module
- Solar/kinetic energy harvesting
- Heart-rate sensor integration
- ML-based gait analysis
- Water-resistant enclosure
- Cloud dashboard

---

## 📄 Documentation

Full technical report available in:

Documents/report.pdf

Includes algorithms, experiments, and testing results.

---

## 🤝 Contributors

Smart Shoe System developed as an embedded wearable project  
Department of Electronics & Telecommunication Engineering
 Arshad Shaikh 
 Om Ingle 
 Aryavart Dahenkar
 Prachi Untwale 

---

## 📜 License

MIT License — open for research and educational use.
