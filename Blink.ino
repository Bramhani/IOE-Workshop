int count=0;
void setup() {
  pinMode(D2, OUTPUT);   
  Serial.begin(9600);  
}

void loop() {
  digitalWrite(D2, HIGH);                               
  delay(1000);                      
  digitalWrite(D2, LOW); 
  delay(1000);
  count+=1;  
  Serial.print("No. of times LED blinked -- ");
  Serial.println(count);                  
}
