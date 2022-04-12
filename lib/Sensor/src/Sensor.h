#include <Wire.h>
#include <Mqtt.h>
#define FORCE_SENSOR_PIN 21

bool state;

void initSensor()
{
  setupMQTT();
  pinMode(FORCE_SENSOR_PIN, INPUT_PULLUP);
}

void checkDistance()
{

  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();

  int analogReading = digitalRead(FORCE_SENSOR_PIN);

  if (analogReading == HIGH)
  {
    if (state == true)
    {
      state = false;
      Serial.println(" -> no pressure");
      mqttClient.publish("/station/s002/presence", "{\"presence\":\"false\"}");
    }
  }
  else if (analogReading == LOW)
  {

    if (state == false)
    {
      state = true;
      mqttClient.publish("/station/s002/presence", "{\"presence\":\"true\"}");
    }
  }

  Serial.println();
}
