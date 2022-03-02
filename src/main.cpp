#include <WiFi.h>
#include "wifi.h"
#include "sensor.h"

bool ConnectWifi(void)
{
  bool state = true;
  int i = 0;

  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    if (i > 20)
    {
      state = false;
      break;
    }
    i++;
  }
  if (state)
  {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("");
    Serial.println("Connection failed.");
  }

  return state;
}

void setup()
{
  Serial.begin(115200);
  ConnectWifi();
  initSensor();
}

void loop()
{

  checkDistance();
  if ((WiFi.status() == WL_CONNECTED))
  { // Check the current connection status
    // Serial.println("data received" + users);
    // delay(10000);
  }
  // Serial.println(value);
}
