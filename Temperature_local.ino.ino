/*
 * Interface LDR with NodeMCU
 * By TheCircuit
 */
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

void loop() {
  // read the input on analog pin 0:
  int reading = analogRead(A0);
  
  float voltage = reading * 1.8;
  voltage /= 1024.0; 
  float temperatureC = (voltage - 0.5) * 100 ;
  Serial.print(temperatureC); 
  Serial.println(" degrees C");
  delay(1000); 
}
