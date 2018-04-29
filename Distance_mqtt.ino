

//Headers or Packages

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Constant values

const char* ssid = "Sowjanya";
const char* password = "12345678";
const char* mqtt_server = "mqtt.dioty.co";
const char* email="bramhanimulugoju@gmail.com";
const char* e_password="a0360821";
int led_onoff_pin=D2;
const char* distance_topic_p="/bramhanimulugoju@gmail.com/Distancep";
int count=0;
#define TRIGGER 4
#define ECHO    5
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
  pinMode(led_onoff_pin, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
    
}

//When mqtt broker is not connected,then here is re-again connection

void reconnect(){
  while (!client.connected()) {
    if (client.connect(email,email,e_password,distance_topic_p,2,0,"f")) {
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
  long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;
  
  Serial.print(distance);
  Serial.println("Centimeter:");
  delay(1000);
  snprintf (mssg, 175, "#%ld Centimeter",distance);
  client.publish(distance_topic_p,mssg );
}
