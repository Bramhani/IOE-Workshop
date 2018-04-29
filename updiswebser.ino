#include <ESP8266WiFi.h>
#define TRIGGER 4
#define ECHO 5
#define BLUE_LED_PIN 2

const char *ssid     = "Bramhani";
const char *password = "12345678";
int val=0;

WiFiServer server(80);

String header;
const int led = 2;

long readDistance()
  {
    long duration;
    digitalWrite(TRIGGER,LOW);
    digitalWrite(TRIGGER,HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER,LOW);
    duration=pulseIn(ECHO,HIGH);
    return(duration/2)/29.1;
  }
void setup() {
  Serial.begin(115200);
  while(!Serial){
  }
  Serial.println();
   pinMode(TRIGGER,OUTPUT);
  pinMode(ECHO,INPUT);
  pinMode(BLUE_LED_PIN,OUTPUT);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  int val=readDistance();
  String myString= String(val);
  if(val>10)
    {
      digitalWrite(BLUE_LED_PIN,HIGH);
    }
    else{
      digitalWrite(BLUE_LED_PIN,LOW);
    }
    delay(1000);
  WiFiClient client = server.available(); 

  if (client) {                            
    Serial.println("New Client.");          
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        header += c;
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><meta HTTP-EQUIV=\"refresh\"content=\"1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
           
            client.println("<body><h1>Finding the distance</h1>");
            client.print("<p>dis is "+myString+"</p>" );
             
           
            client.println("</body></html>");
            
            client.println(); 
            break;
          } 
          else 
          {
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;     
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

