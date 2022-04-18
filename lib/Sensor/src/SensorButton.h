#pragma once

#include <Mqtt.h>

#define FORCE_SENSOR_PIN 21

bool state;

void initSensor()
{
  pinMode(FORCE_SENSOR_PIN, INPUT_PULLUP);
}

void checkDistance()
{
  int analogReading = digitalRead(FORCE_SENSOR_PIN);

  // turn off
  if (analogReading == HIGH && state == true)
  {
    state = false;
    Serial.println(" -> no pressure");
    mqttClient.publish("/station/s002/presence", "{\"presence\":\"false\"}");
  }
  
  // turn on
  if (analogReading == LOW && state == false)
  {
    state = true;
    mqttClient.publish("/station/s002/presence", "{\"presence\":\"true\"}");
  }

  //Serial.println();
}
