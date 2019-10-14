#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
long duration, inches, distance;

//Clinet
HTTPClient client;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);

  //Define inputs and outputs
  pinMode(D7, OUTPUT);
  pinMode(D6, INPUT);

  // WIFI Info and connect
  WiFi.begin("", "");
  while (WiFi.status() != WL_CONNECTED)
  {

    delay(500);
    Serial.println("Waiting to connect…");
  }

  // IP Addresses
  Serial.print("MY IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  distance = calculate();
  Serial.println(distance);
  // If distance is between 4-6 feet
  if(distance <= 80 && distance > 48){
    yellow();
  }
  // If distance is less than 4 feet
  else if(distance <= 48){
    red();
  }
  // Everything else
  else{
    green();
  }
}

long calculate() {
  // Open the sensor for 10 ms
  digitalWrite(D7, LOW);
  delayMicroseconds(5);
  digitalWrite(D7, HIGH);
  delayMicroseconds(10);
  digitalWrite(D7, LOW);

  // Duration of the echo pulse
  duration = pulseIn(D6, HIGH);
 
  // Convert the time into a distance
  inches = (duration/2) / 74;
  
  delay(500);
  return inches;
}
// call green
void green(){
  Serial.println("green");
  client.begin("http://IP_ADDRESS/green");
  client.GET();
}
// call yellow
void yellow(){
  Serial.println("yellow");
  client.begin("http://IP_ADDRESS/yellow");
  client.GET();
}
// call red
void red(){
  Serial.println("red");
  client.begin("http://IP_ADDRESS/red");
  client.GET();
}
