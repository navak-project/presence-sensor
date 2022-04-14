#pragma once

#include <PubSubClient.h>
#include <Haptic.h>

// MQTT client
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
const char *mqttServer = "192.168.1.212";
int mqttPort = 1883;


// headers
void reconnect();
void receiveMessage(const char* topic, byte* payload, uint16_t length);


void setupMQTT()
{
  mqttClient.setServer(mqttServer, mqttPort);
}

void updateMQTT()
{
  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();
}

void reconnect()
{
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected())
  {
    Serial.println("Reconnecting to MQTT Broker..");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str()))
    {
      mqttClient.subscribe("/station/s001/pulse");
      mqttClient.setCallback(&receiveMessage);

      Serial.println("Connected.");
    }
  }
}

void receiveMessage(const char* topic, byte* payload, uint16_t length) {
  if (strcmp(topic, "/station/s001/pulse") == 0) {
    // TODO: figure this out
    char* p = (char*)malloc(length);
    memcpy(p,payload,length);

    pulseToMotor();
  }
}