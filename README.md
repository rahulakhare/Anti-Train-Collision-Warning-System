# Anti-Train Collision Warning System

This project demonstrates a **low-cost, microcontroller-based system** designed to improve train safety by preventing collisions. Built using Arduino Uno boards, NRF24L01 wireless transceivers, LCD displays, and buzzers, this system allows trains to **communicate wirelessly and issue real-time collision alerts** when another equipped train is within a set range.

## Project Objectives

- Achieve bidirectional, train-to-train wireless communication using NRF24L01 modules.
- Alert with a buzzer and LCD display whenever a train comes into proximity.
- Ensure the system is decentralized and functions without external infrastructure.

## Key Features

- **Independent of GPS or Internet**: Works in tunnels, remote locations, and areas with limited communication infrastructure.
- **Low Power Consumption**: Efficient hardware choices ensure extended operational life.
- **Expandable**: Easily scaled for multiple trains and can be upgraded in the future.

## Components List

- Arduino Uno
- NRF24L01 RF Transceiver Modules
- 16x2 I2C LCD Display
- Active Buzzer
- Capacitor (10uF)
- Power supply/battery
- Connecting wires

## How It Works

- Each train is equipped with an Arduino Uno and NRF24L01 module. 
- Trains exchange “heartbeat” pings every 500ms to detect proximity.
- When another train is detected, the system activates a buzzer and displays alert messages like “Train Detected” and “!!! WARNING !!!” on the LCD.
- Startup diagnostics check module connectivity and test the alert system.

## Testing & Results

- **Range:** 800–1000 meters between modules.
- **Latency:** Less than 500ms to detect another train.
- **Reliability:** Very few false positives, thanks to efficient RF channel selection and message filtering.

## For more information read the project report


