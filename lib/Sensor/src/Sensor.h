#include <Wire.h>
#include <Mqtt.h>
#define FORCE_SENSOR_PIN 35

bool state;

void initSensor()
{
  setupMQTT();
}

void checkDistance()
{

  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();

  int analogReading = analogRead(FORCE_SENSOR_PIN);

  if (analogReading < 10)
  {
    if (state == true)
    {
      state = false;
      Serial.println(" -> no pressure");
      mqttClient.publish("/station/s001/presence", "{\"presence\":\"false\"}");
    }
  }
  else if (analogReading > 10)
  {

    if (state == false)
    {
      state = true;
      mqttClient.publish("/station/s001/presence", "{\"presence\":\"true\"}");
    }
  }

  Serial.println();
}
