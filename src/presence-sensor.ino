#include <WiFi.h>
#include <SensorCapacitor.h>
#include <Mqtt.h>
#include <Haptic.h>

char* SSID = "Silva-WIFI";
char* PASSWORD = "silvaFTW";


void setup() {
  Serial.begin(115200);

  connectWiFi();
  setupMQTT();
  initSensor();
}

void loop() {
  updateMQTT();
  checkDistance();
}


// CONNECT TO WIFI
bool connectWiFi(void)
{
  bool state = true;
  int i = 0;

  WiFi.begin(SSID, PASSWORD);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false;
      break;
    }
    i++;
  }
  if (state) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  return state;
}