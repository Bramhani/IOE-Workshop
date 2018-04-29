

//Headers or Packages

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Constant values

const char* ssid = "UdayKasala";
const char* password = "uday&kasala1";
const char* mqtt_server = "mqtt.dioty.co";
const char* email="harivenkataprasadbilla@gmail.com";
const char* e_password="6369c538";
const char* temp_topic_p="/harivenkataprasadbilla@gmail.com/Tempp";

//Non initialize values

WiFiClient espClient;
PubSubClient client(espClient);
char mssg[175];
//Wifi Setup

void setup_wifi() {
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
}


//First setup block which executes at program start to settle loop function stable

void setup() {   
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
    
}

//When mqtt broker is not connected,then here is re-again connection

void reconnect(){
  while (!client.connected()) {
    if (client.connect(email,email,e_password,temp_topic_p,2,0,"f")) {
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// continuous execution means loop function

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  int reading = analogRead(A0);
  
  float voltage = reading * 1.8;
  voltage /= 1024.0; 
  float temperatureC = (voltage - 0.5) * 100 ;
  Serial.print(temperatureC); 
  Serial.println(" degrees C");
  delay(1000); 
  snprintf (mssg, 175, "#%ld degree Celsius",int(temperatureC));
  client.publish(temp_topic_p,mssg );
}
