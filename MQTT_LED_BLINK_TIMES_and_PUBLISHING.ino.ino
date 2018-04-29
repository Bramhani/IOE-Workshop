

//Headers or Packages

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Constant values

const char* ssid = "Sowjanya";
const char* password = "12345678";
const char* mqtt_server = "mqtt.dioty.co";
const char* email="bramhanimulugoju@gmail.com";
const char* e_password="a0360821";
int led_onoff_pin=2;
const char* led_topic_p="/bramhanimulugoju@gmail.com/Ledp";
int count=0;
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
    
}

//When mqtt broker is not connected,then here is re-again connection

void reconnect(){
  while (!client.connected()) {
    if (client.connect(email,email,e_password,led_topic_p,2,0,"f")) {
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
  digitalWrite(led_onoff_pin,HIGH);
  delay(1000);
  digitalWrite(led_onoff_pin,LOW);
  delay(1000);
  count+=1;
  Serial.print("No. of times LED blinked -- ");
  Serial.println(count);
  snprintf (mssg, 175, "#%ld times LED blinked",count);
  client.publish(led_topic_p,mssg );
}
