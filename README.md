# Bluetooth Controlled Manual and Automatic Floor Cleaning Robot

## Overview

The **Bluetooth Controlled Manual and Automatic Floor Cleaning Robot** is an Arduino-based automation project developed as a Third Year Engineering Mini Project under the Savitribai Phule Pune University curriculum.

The robot is designed to reduce human effort and improve cleaning efficiency by combining both **manual Bluetooth control** and **automatic obstacle detection**. The system uses an **Arduino Uno** as the main controller along with ultrasonic sensors, DC motors, a water pump, and a Bluetooth module to perform floor cleaning operations effectively.

This project was also presented at the **Tech Spectrum Technical Event** organized by our college.

---

## Features

- Manual robot control using Bluetooth mobile application
- Automatic obstacle detection and navigation
- Dual operating modes (Manual + Automatic)
- Water spraying and mopping mechanism
- Wireless operation using HC-05 Bluetooth module
- LCD display for system status
- Low-cost and efficient cleaning solution

---

## Technologies Used

- Arduino Uno
- Embedded C Programming
- Arduino IDE
- Bluetooth Communication
- Ultrasonic Sensor Technology
- Embedded Systems and Robotics

---

## Components Used

- Arduino Uno
- HC-05 Bluetooth Module
- HC-SR04 Ultrasonic Sensors
- Motor Driver Module
- DC Motors
- Water Pump
- Relay Module
- 16x2 LCD Display with I2C
- Lithium-ion Batteries
- Chassis and Wheels
- Breadboard / PCB
- Voltage Regulator (7805)

---

## Working Principle

The robot operates in two different modes:

### Manual Mode
The robot is controlled wirelessly using a smartphone application connected through the HC-05 Bluetooth module. The user can control the movement of the robot using directional buttons.

### Automatic Mode
The ultrasonic sensors continuously detect obstacles in front of the robot. Based on sensor input, the Arduino Uno automatically changes the robot’s direction to avoid collisions and continue the cleaning process.

The water pump and mop mechanism help in performing wet floor cleaning efficiently.

---

## Mobile Application

The mobile application is used to manually control the movement of the robot through Bluetooth communication. The interface provides directional controls such as forward, backward, left, right, rotate left, and rotate right for smooth operation of the robot.

---

## Project Structure

```bash
Floor_Cleaning_Robot/
│
├── Floor_Cleaning_Robot_Code/
│   └── Arduino source code files
│
├── Report/
│   └── Floor cleaning robot project report
│
├── Result images/
│   └── Images of prototype and final model
│
├── Result Videos/
│   └── Working demonstration videos
│
└── README.md
```
