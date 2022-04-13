#include <Wire.h>
#include <Mqtt.h>

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

  int data = touchRead(4);

  if (touchRead(4) > 15 && state == true)
  {
    state = false;
    Serial.println("no pressure");
    mqttClient.publish("/station/s002/presence", "{\"presence\":\"false\"}");
    return;
  }
  if (touchRead(4) < 10 && state == false)
  {
    state = true;
    Serial.println("pressure");
    mqttClient.publish("/station/s002/presence", "{\"presence\":\"true\"}");
    return;
  }
  delay(100);
}
