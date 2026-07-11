# 🥄 Parkinson's Spoon Stabilizer

An ESP32-based smart spoon stabilization prototype that minimizes hand tremors using an MPU6050 Inertial Measurement Unit (IMU) and a dual-axis servo stabilization mechanism.

> **Status:** Prototype Development

---

## Project Preview

<p align="center">
  <img src="Images/Parkinson_spoon_ai.png">
</p>

---

## Overview

This project demonstrates a low-cost assistive technology prototype capable of stabilizing a spoon against unwanted hand movements.

Using real-time orientation data from an MPU6050 sensor, an ESP32 estimates the spoon's pitch and roll angles using a Complementary Filter. The controller then drives two SG90 servo motors to compensate for unwanted motion and maintain a stable spoon orientation.

The project focuses on embedded systems, real-time control, IMU sensor fusion, and adaptive servo stabilization.

---

## Features

- Dual-axis stabilization (Pitch & Roll)
- ESP32-based real-time processing
- MPU6050 motion sensing
- Complementary Filter
- Adaptive Servo Gain
- Servo Motion Smoothing
- Adjustable Deadband
- Lightweight prototype design
- Modular and expandable architecture

---

## Hardware

| Component | Quantity |
|-----------|----------|
| ESP32 Dev Module | 1 |
| MPU6050 IMU | 1 |
| SG90 Micro Servo | 2 |
| 3.7V Li-ion Battery | 1 |
| XL6009 Boost Converter | 1 |
| Plastic Spoon | 1 |

---

## Software

- Arduino IDE
- ESP32Servo Library
- MPU6050 Library
- Wire Library

---

## Control Architecture

```
MPU6050
      │
      ▼
Complementary Filter
      │
      ▼
Pitch & Roll Error Calculation
      │
      ▼
Deadband Compensation
      │
      ▼
Adaptive Gain
      │
      ▼
Servo Smoothing
      │
      ▼
Pitch Servo + Roll Servo
```

---

## Current Progress

- ✅ MPU6050 Integration
- ✅ Pitch Stabilization
- ✅ Roll Stabilization
- ✅ Adaptive Gain Control
- ✅ Servo Smoothing
- ✅ Real-Time Serial Monitoring
- ⏳ Mechanical Optimization
- ⏳ PID Controller
- ⏳ Tremor Frequency Detection
- ⏳ 3D Printed Enclosure

---

## Repository Structure

```
Parkinsons_spoon/
│
├── combined_pitch_roll_stabilizer.ino
├── README.md
├── LICENSE
│
└── Images/
    ├── img_1.jpg
    ├── img_2.jpg
    └── Parkinson_spoon_ai.png
```

---

## Prototype Images

### Hardware Prototype

<p align="center">
<img src="Images/img_1.jpg" width="650">
</p>

---

### Working Prototype

<p align="center">
<img src="Images/img_2.jpg" width="650">
</p>

---

## Future Improvements

- PID-Based Stabilization
- Kalman Filter
- Tremor Frequency Detection (4–6 Hz)
- Bluetooth Configuration
- OLED Display
- Rechargeable Battery Management
- Compact PCB Design
- Lightweight 3D Printed Gimbal
- AI-Based Tremor Severity Analysis

---

## Applications

- Parkinson's Disease Assistance
- Essential Tremor Compensation
- Biomedical Engineering
- Embedded Systems Research
- Assistive Robotics
- Medical Device Prototyping

---

## Author

**Muthuram**

Electronics and Communication Engineering (ECE)

Embedded Systems • IoT • Robotics • AI

GitHub: https://github.com/Muthuram30

---

## License

This project is licensed under the MIT License.
