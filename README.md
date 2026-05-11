# Wearable-IOT-System-for-Real-Time-Hand-Fatigue-Detection-using-MPU6500-sensor-during-smartphone-use
## Overview
This project presents a wearable IoT-based smart glove system designed to detect hand fatigue during prolonged smartphone usage. The system continuously monitors grip force, thumb movement, and wrist posture using FSR and MPU6500 sensors.

An ESP32 microcontroller processes sensor data in real time and calculates a fatigue score using a lightweight rule-based algorithm. When fatigue exceeds a predefined threshold, the system sends alert notifications to the user through Telegram.

The system aims to reduce risks associated with prolonged smartphone usage such as:
- Wrist strain
- Repetitive strain injury (RSI)
- Thumb fatigue
- Musculoskeletal discomfort
- Early signs of carpal tunnel syndrome

---

## Features
- Real-time hand fatigue monitoring
- Grip force detection using FSR sensor
- Wrist posture and thumb motion tracking using MPU6500 IMU sensors
- Rule-based fatigue estimation algorithm
- Telegram alert notifications
- Low latency edge processing using ESP32
- Portable wearable glove design
- No cloud dependency for computation

---

## Hardware Components
- ESP32 Development Board
- FSR (Force Sensitive Resistor)
- 2 × MPU6500 IMU Sensors
- Breadboard / PCB
- Jumper Wires
- USB Power Supply / Battery
- Wearable Glove

---

## Software & Technologies Used
- Arduino IDE
- Embedded C / C++
- ESP32 WiFi Libraries
- Telegram Bot API
- I2C Communication Protocol

---

## System Architecture
The system consists of three major modules:

1. Sensing and Data Acquisition
2. Signal Processing and Fatigue Estimation
3. Wireless Feedback Communication

Sensors continuously collect:
- Grip force
- Thumb motion
- Wrist motion

The ESP32 processes the signals locally and calculates a fatigue score.

If:
Fatigue Score > Threshold

then:
- Telegram alert is sent to the user.

---

## Fatigue Parameters
The fatigue score is estimated using:
- Grip force intensity
- Repetitive thumb movements
- Wrist motion variability
- Continuous smartphone usage duration

---

## Working Principle
1. FSR sensor measures grip pressure.
2. MPU6500 sensors track thumb and wrist movements.
3. ESP32 filters and processes sensor data.
4. Fatigue score is calculated.
5. If fatigue exceeds threshold:
   - Telegram notification is triggered.

---

## Project Applications
- Ergonomic monitoring
- Healthcare wearables
- Smart rehabilitation systems
- Occupational safety
- Smartphone overuse monitoring
- Physiotherapy assistance

---

## Advantages
- Low-cost wearable solution
- Real-time monitoring
- Portable and lightweight
- Edge computing based
- Easy integration with IoT systems

---

## Future Improvements
- Rechargeable battery integration
- Haptic vibration feedback
- Mobile application dashboard
- AI/ML-based fatigue prediction
- Miniaturized wearable hardware
- Cloud analytics support

---
