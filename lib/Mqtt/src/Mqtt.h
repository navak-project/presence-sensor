#pragma once

#include <WiFi.h>
#include <PubSubClient.h>
#include <Haptic.h>

// MQTT client
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

const char *mqttServer = "192.168.1.212";
int mqttPort = 1883;

String ipTopic, pulseTopic, presenceTopic;
String stationId;


// headers
void reconnect();
void postConnect();
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
      postConnect();
    }
  }
}

void postConnect() {
  // set callback function
  mqttClient.setCallback(&receiveMessage);

  // request station ID
  String ip = WiFi.localIP().toString();

  // prepare topic...
  ipTopic = String("/station/id/") + ip;
  //Serial.print("");
  mqttClient.subscribe(ipTopic.c_str());

  // request
  mqttClient.publish("/station/requestId", ip.c_str());
}


void receiveMessage(const char* topic, byte* payload, uint16_t length)
{
  // ID response
  if (strcmp(topic, ipTopic.c_str()) == 0)
  {
    // convert to string
    payload[length] = '\0';
    String id = String((char*)payload);
    // station id
    char temp[5];
    sprintf(temp, "s%03d", (int)id.toInt());
    stationId = String(stationId);

    // construct topics
    pulseTopic = "/station/" + stationId + "/pulse";
    presenceTopic = "/station/" + stationId + "/presence";
    // subscribe to topic
    mqttClient.subscribe(pulseTopic.c_str());

    // success!!!
    Serial.println("Connected.");
  }

  // motor pulse
  if (strcmp(topic, pulseTopic.c_str()) == 0)
  {
    Serial.println(pulseTopic);

    // convert to string
    payload[length] = '\0';
    char* out = (char*)payload;
    
    // Serial.println(out);

    pulseToMotor();
  }
}