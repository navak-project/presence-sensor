#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Mqtt.h>

#define HAPTIC_ADDR 0x04

void initHaptic() {
    Wire.begin();
}

void pulseToMotor(byte duration = 50, byte speed = 255) {
    Wire.beginTransmission(HAPTIC_ADDR);
    // byte 1: duration
    Wire.write(duration);
    // byte 2: speed
    Wire.write(speed);
    // send
    Wire.endTransmission();
}