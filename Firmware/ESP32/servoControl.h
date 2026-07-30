#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include "config.h"      // Includes pin numbers, pulse limits, and configuration

// ======================================================
// Global Variables
// ======================================================
// Servo objects.
//
// Creates an array of 4 Servo objects.
// Each object controls one physical servo.
//
// servos[0] -> Servo 1
// servos[1] -> Servo 2
// servos[2] -> Servo 3
// servos[3] -> Servo 4
//
Servo servos[NUM_SERVOS];
//
// Current pulse being sent to each servo.
//
// uint16_t = Unsigned 16-bit integer (2 bytes)
// Range: 0 - 65535
//
// Stores pulse width in microseconds.
//
// Example:
// Servo currently at 1500 µs
//
uint16_t servoPulse[NUM_SERVOS];
//
// Desired pulse.
//
// The servo does NOT jump directly to this value.
// updateServos() slowly moves servoPulse toward targetPulse.
//
uint16_t targetPulse[NUM_SERVOS];
//
// Raw ADC value read from potentiometers.
//
// ESP32 ADC range:
// 0 → 4095
//
// uint16_t is used because 4095 is larger than uint8_t (255).
//
uint16_t potValue[NUM_SERVOS];
//
// Current operating mode.
//
// enum ControlMode
// MANUAL = Potentiometers
// REMOTE = WiFi/WebSocket
//
ControlMode controlMode = MANUAL;
//
// ======================================================
// Servo Speed
// ======================================================
//
// Maximum pulse change every update.
//
// uint8_t (1 byte)
// Range: 0-255
//
// Example:
//
// Current = 1000
// Target  = 1500
//
// SERVO_SPEED = 8
//
// Updates:
//
// 1008
// 1016
// 1024
// ...
// 1500
//
const uint8_t SERVO_SPEED = 8;
//
// ======================================================
// Initialize Servos
// ======================================================
void initServos(){
    // Loop through every servo
    //
    // uint8_t is enough because
    // NUM_SERVOS = 4.
    //
    for (uint8_t i = 0; i < NUM_SERVOS; i++){
        // Standard servo PWM frequency
        // 50Hz = one pulse every 20ms
        servos[i].setPeriodHertz(50);
        // Attach servo to GPIO pin
        //
        // Parameters:
        // Pin
        // Minimum pulse
        // Maximum pulse
        //
        servos[i].attach( servoPins[i], minPulse[i], maxPulse[i] );
        //
        // Start at middle position
        //
        // (Minimum + Maximum)/2
        //
        servoPulse[i] = (minPulse[i] + maxPulse[i]) / 2;
        //
        // Target also begins at center
        targetPulse[i] = servoPulse[i];
        //
        // Send pulse immediately
        servos[i].writeMicroseconds( servoPulse[i] );
    }
}
// ======================================================
// Read Potentiometers
// ======================================================
void readPotentiometers(){
    // Ignore potentiometers when
    // robot is in REMOTE mode.
    if (controlMode != MANUAL) return;
    //
    for (uint8_t i = 0; i < NUM_SERVOS; i++){
        // Read ADC value
        //
        // Range:
        // 0 - 4095
        //
        potValue[i] = analogRead(potPins[i]);
        // Convert ADC value into
        // servo pulse width.
        //
        // map(value,
        //     fromLow,
        //     fromHigh,
        //     toLow,
        //     toHigh)
        //
        targetPulse[i] = map( potValue[i], 0, 4095, minPulse[i], maxPulse[i] );
    }
}
// ======================================================
// Smooth Servo Movement
// ======================================================
void updateServos(){
    for (uint8_t i = 0; i < NUM_SERVOS; i++){
        // Servo needs to move forward
        if (servoPulse[i] < targetPulse[i]){
            // Increase pulse
            //
            // min() prevents overshooting.
            //
            servoPulse[i] += min( (uint16_t)SERVO_SPEED, (uint16_t)( targetPulse[i] - servoPulse[i] ) );
        }
        // Servo needs to move backward
        else if (servoPulse[i] > targetPulse[i]){
            // Decrease pulse
            servoPulse[i] -= min( (uint16_t)SERVO_SPEED, (uint16_t)( servoPulse[i] - targetPulse[i] ) );
        }
        // Send updated pulse
        servos[i].writeMicroseconds( servoPulse[i] );
    }
}
// ======================================================
// Set Servo Position
// ======================================================
// id    = Servo number
// pulse = Desired pulse width
//
void setServoPulse( uint8_t id, uint16_t pulse){
    // Prevent invalid servo numbers.
    //
    // Valid:
    // 0 1 2 3
    //
    if (id >= NUM_SERVOS) return;
    // Keep pulse within safe limits.
    //
    // constrain(value,min,max)
    //
    pulse = constrain( pulse, minPulse[id], maxPulse[id] );
    // Update target.
    //
    // updateServos() moves there smoothly.
    //
    targetPulse[id] = pulse;
}
// ======================================================
// Serial Monitor Output
// ======================================================
void printServoData(){
    // static variable keeps its value
    // between function calls.
    //
    // uint32_t
    // Range:
    // 0 - 4,294,967,295
    //
    // millis() also returns uint32_t.
    //
    static uint32_t timer = 0;
    // Print only every 100ms.
    if (millis() - timer < 100) return;
    //
    timer = millis();
    //
    for (uint8_t i = 0; i < NUM_SERVOS; i++){
        // Example output:
        //
        // S1:1500 P1:2050
        //
        Serial.printf("S%d:%d  P%d:%d   ", i + 1, servoPulse[i], i + 1, potValue[i]);
       // Serial.print("S"); Serial.print(i + 1); Serial.print(":"); Serial.print(servoPulse[i]); Serial.print("  P"); Serial.print(i + 1); Serial.print(":"); Serial.print(potValue[i]); Serial.print("   ");
    }
    Serial.println();
}
#endif

