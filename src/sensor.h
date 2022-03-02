

#include <Wire.h>
#include "mqtt.h"
#include "id.h"
#define FORCE_SENSOR_PIN 35

bool state;
bool canSend = true;
long samplesTaken = 0; //Counter for calculating the Hz or read rate
long unblockedValue; //Average IR at power up
long startTime; //Used to calculate measurement rate

void initSensor()
{
  setupMQTT();
  //mqttClient.publish("/station/s001/presence", "{\"presence\":\"false\"}");
  
  

}

void checkDistance()
{

  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();
  
  samplesTaken++;

  int analogReading = analogRead(FORCE_SENSOR_PIN);
  //Serial.print("Force sensor reading = ");
 // Serial.print(analogReading); // print the raw analog reading

   if (analogReading < 10 )  {    // from 0 to 9
 
    if(state == true) {
      state = false;
      Serial.println(" -> no pressure");
      mqttClient.publish("/station/s001/presence", "{\"presence\":\"false\"}");
      canSend = true;
      
    }
   } else if (analogReading > 10 ){

    if(state == false){
       state = true;
      mqttClient.publish("/station/s001/presence", "{\"presence\":\"true\"}");
      canSend = true;
     
      }
    }
   

  //delay(100);

 /* if (currentDelta >= (long)252615)
  {
    const char* val = "{\"presence\":\"true\"}";
    Serial.print(" Something is there!");
    mqttClient.publish("/station/"+ID+"/presence", val);
  }else{
    const char* val = "{\"presence\":\"false\"}";
    mqttClient.publish("/station/"+ID+"/presence", val);
  }*/

  Serial.println();
}
