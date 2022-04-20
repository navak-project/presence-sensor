#include <Mqtt.h>
#include <Haptic.h>

bool state;

void initSensor() {}

void checkDistance()
{
  // read value..
  int data = touchRead(4);

  if (data > 15 && state)
  {
    state = false;
    Serial.println("no pressure");
    mqttClient.publish(presenceTopic.c_str(), "{\"presence\":\"false\"}");
    return;
  }
  if (data < 10 && !state)
  {
    state = true;
    Serial.println("pressure");
    mqttClient.publish(presenceTopic.c_str(), "{\"presence\":\"true\"}");
    pulseToMotor(10, 255);
    return;
  }
  delay(100);
}
