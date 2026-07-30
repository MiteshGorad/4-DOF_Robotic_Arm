# ESP32 Pinout

This document contains the GPIO mapping and hardware connections for the **ESP32-based 4-DOF Robotic Arm**.

> **Note:** All GPIO assignments are configurable in `Firmware/ESP32/config.h`.

---

# Hardware

| Component | Quantity |
|-----------|---------:|
| ESP32 DevKit V1 | 1 |
| Servo Motors | 4 |
| 10kΩ Potentiometers | 4 |
| 100nF Ceramic Capacitors | 4 |
| 1kΩ Resistors | 4 |
| 5V 10A (50W) SMPS | 1 |
| Jumper Wires | As Required |

---

# ESP32 Connections

## Servo Connections

| Servo | Function | ESP32 GPIO |
|--------|----------|-----------:|
| Servo 1 | Base Rotation | GPIO XX |
| Servo 2 | Shoulder | GPIO XX |
| Servo 3 | Elbow | GPIO XX |
| Servo 4 | Gripper | GPIO XX |

---

## Potentiometer Connections

| Potentiometer | Controls | ESP32 ADC GPIO |
|---------------|----------|---------------:|
| Pot 1 | Base Rotation | GPIO XX |
| Pot 2 | Shoulder | GPIO XX |
| Pot 3 | Elbow | GPIO XX |
| Pot 4 | Gripper | GPIO XX |

---

# Potentiometer Circuit

Each potentiometer uses a simple RC filter to reduce ADC noise and improve servo stability.

## Components (Per Potentiometer)

- 10kΩ Potentiometer
- 1kΩ Series Resistor
- 100nF Ceramic Capacitor

### Wiring

```
3.3V
 │
 │
┌───────┐
│ 10kΩ  │
│  POT  │
└───────┘
 │
 │ (Wiper)
 │
 ├────── 100nF ────── GND
 │
 │
1kΩ
 │
 │
GPIO XX (ESP32 ADC)
 │
GND
```

### Purpose

| Component | Purpose |
|-----------|---------|
| 1kΩ Resistor | Protects the ESP32 ADC input and limits transient current. |
| 100nF Capacitor | Filters electrical noise from the potentiometer, providing smoother ADC readings. |

---

# Power Connections

| Component | Supply |
|-----------|--------|
| ESP32 | USB or Regulated 5V |
| Servo Motors | 5V 10A (50W) SMPS |
| Potentiometers | 3.3V from ESP32 |

---

# SMPS Connections

The robotic arm is powered using a dedicated **5V 10A (50W) Switching Mode Power Supply (SMPS)**.

## SMPS Wiring

| SMPS Terminal | Connect To |
|---------------|------------|
| +5V | Servo VCC (Red Wires) |
| GND | Servo GND (Brown/Black Wires) |
| GND | ESP32 GND |

> **Important:** The **ESP32 GND** and **SMPS GND** **must** be connected together to establish a common reference for the PWM control signals.

---

# Wiring Notes

- Use the **5V 10A SMPS** to power all servo motors.
- Power the ESP32 separately through USB or a regulated 5V source.
- Connect all grounds together (ESP32, SMPS, and Servos).
- Power potentiometers from the ESP32's **3.3V** output.
- Use one **100nF ceramic capacitor** per potentiometer for ADC noise filtering.
- Use one **1kΩ resistor** in series between each potentiometer wiper and the ESP32 ADC input.
- Keep servo power wires short and use sufficiently thick wire to minimize voltage drop.
- Keep signal wires away from servo power cables where possible to reduce electrical interference.

---

# Firmware Configuration

The GPIO assignments are configured in:

```text
Firmware/
└── ESP32/
    └── config.h
```

Modify `config.h` to change:

- Servo GPIO pins
- Potentiometer ADC pins
- Servo pulse limits
- Motion parameters

---

# Recommended ESP32 ADC Pins

The following ADC1 pins are recommended for potentiometer inputs because they remain available when Wi-Fi is enabled.

| GPIO | ADC Channel |
|------:|------------|
| GPIO32 | ADC1_CH4 |
| GPIO33 | ADC1_CH5 |
| GPIO34 | ADC1_CH6 *(Input Only)* |
| GPIO35 | ADC1_CH7 *(Input Only)* |

> Avoid using **ADC2** pins if Wi-Fi functionality will be added in future versions.

---

# Project Power Architecture

```
                 +----------------------+
                 |   5V 10A SMPS        |
                 +----------+-----------+
                            |
            +---------------+----------------+
            |               |                |
         Servo 1         Servo 2         Servo 3
            |                                |
         Servo 4                             |
            |                                |
            +------------ GND ---------------+
                         |
                     ESP32 GND
                         |
                 +-------+-------+
                 |     ESP32     |
                 +---------------+
                 | USB / 5V      |
                 | 3.3V → Pots   |
                 +---------------+
```

---

# Notes

- Always use a common ground between the ESP32 and the external servo power supply.
- Do not power multiple servos directly from the ESP32.
- The RC filter (1kΩ + 100nF) on each potentiometer helps produce more stable analog readings and smoother servo motion.
- Verify all GPIO assignments in `config.h` before uploading the firmware.
