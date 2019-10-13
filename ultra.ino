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
  WiFi.begin("Tylers iPhone", "Password");
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
  if(distance <= 80 && distance > 48){
    yellow();
  }
  else if(distance <= 48){
    red();
  }
  else{
    green();
  }
}

long calculate() {
  digitalWrite(D7, LOW);
  delayMicroseconds(5);
  digitalWrite(D7, HIGH);
  delayMicroseconds(10);
  digitalWrite(D7, LOW);

  duration = pulseIn(D6, HIGH);
 
  // Convert the time into a distance
  inches = (duration/2) / 74;
  
  delay(500);
  return inches;
}

void green(){
  Serial.println("green");
  client.begin("http://172.20.10.2/green");
  client.GET();
}

void yellow(){
  Serial.println("yellow");
  client.begin("http://172.20.10.2/yellow");
  client.GET();
}

void red(){
  Serial.println("red");
  client.begin("http://172.20.10.2/red");
  client.GET();
}
