# ESP32 Pinout

This document contains the GPIO mapping for the 4-DOF Robotic Arm.

> **Note:** The pin assignments can be changed in `config.h`.

---

# Hardware

- ESP32 DevKit V1
- 4 × Servo Motors
- 4 × 10kΩ Potentiometers
- 5V 10A (50W) SMPS Power Supply
- Connecting Wires

---

# Servo Connections

| Servo | Function | ESP32 GPIO |
|--------|----------|-----------:|
| Servo 1 | Base Rotation | GPIO XX |
| Servo 2 | Shoulder | GPIO XX |
| Servo 3 | Elbow | GPIO XX |
| Servo 4 | Gripper | GPIO XX |

---

# Potentiometer Connections

| Potentiometer | Controls | ESP32 ADC Pin |
|---------------|----------|--------------:|
| Pot 1 | Base Rotation | GPIO XX |
| Pot 2 | Shoulder | GPIO XX |
| Pot 3 | Elbow | GPIO XX |
| Pot 4 | Gripper | GPIO XX |

---

# Power Connections

| Component | Supply |
|-----------|--------|
| ESP32 | USB / 5V |
| Servo Motors | 5V 10A SMPS |
| Potentiometers | 3.3V from ESP32 |

---

# Power Supply

This project uses a **5V 10A (50W) Switching Mode Power Supply (SMPS)** to power all servo motors.

### Connections

| SMPS Terminal | Connect To |
|---------------|------------|
| +5V | All Servo VCC (Red Wire) |
| GND | All Servo GND (Brown/Black Wire) |
| GND | ESP32 GND (Common Ground) |

> **Important:** Connect the **ESP32 GND** and the **SMPS GND** together. A common ground is required for proper PWM signal operation.

---

# Wiring Notes

- Use the 5V 10A SMPS to power all servos.
- Power the ESP32 separately using USB or a regulated 5V input.
- Connect all grounds together (ESP32, SMPS, and Servos).
- Connect potentiometers between **3.3V** and **GND**.
- Connect each potentiometer wiper to an ESP32 ADC pin.
- Keep servo wires as short as practical to reduce electrical noise.
- Use adequately sized wires for the servo power distribution.

---

# Pin Configuration

The GPIO assignments are defined in:

```text
Firmware/ESP32/config.h
```

Modify this file to change the GPIO assignments.
