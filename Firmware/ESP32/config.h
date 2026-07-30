#ifndef CONFIG_H      // Prevents this file from being included multiple times
#define CONFIG_H

#include <ESP32Servo.h>   // ESP32 Servo library

// ======================================================
// Number of Servos
// ======================================================

// #define creates a compile-time constant.
// No RAM is used for this value.
#define NUM_SERVOS 4

// ======================================================
// Servo Pins
// ======================================================

// uint8_t = Unsigned 8-bit integer (1 byte)
// Range: 0 to 255
//
// GPIO pin numbers on ESP32 are below 255, so 1 byte is enough.
// Using uint8_t saves RAM compared to int (4 bytes).
//
// Index:
// servoPins[0] -> Servo 1
// servoPins[1] -> Servo 2
// servoPins[2] -> Servo 3
// servoPins[3] -> Servo 4


const uint8_t servoPins[NUM_SERVOS] = { 13, 12, 14, 27 };

// ======================================================
// Potentiometer Pins
// ======================================================

// uint8_t is again sufficient because GPIO numbers fit
// within 0-255.

const uint8_t potPins[NUM_SERVOS] ={ 34, 35, 32, 33 };

// ======================================================
// Servo Pulse Width Limits
// ======================================================

// Servos are actually controlled using pulse widths
// (microseconds), not degrees.
//
// Typical servo:
// 500us  -> Minimum position
// 1500us -> Center
// 2500us -> Maximum position
//
// Every servo is slightly different, so each one has
// its own safe minimum and maximum pulse width.
//
// uint16_t = Unsigned 16-bit integer (2 bytes)
// Range: 0 to 65,535
//
// Pulse widths are around 500-2500, which is larger
// than uint8_t can store (255), so uint16_t is required.

const uint16_t minPulse[NUM_SERVOS] = { 500, 500, 521, 1133 };

const uint16_t maxPulse[NUM_SERVOS] = { 2400, 1788, 2294, 1365 };

// ======================================================
// Robot Control Mode
// ======================================================

// enum (Enumeration) creates named integer constants.
//
// Default values:
// MANUAL = 0
// REMOTE = 1
//
// Easier to read than using:
// mode = 0;
// mode = 1;

enum ControlMode { MANUAL, REMOTE };

#endif
