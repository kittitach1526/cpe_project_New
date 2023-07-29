#include "DHTlib.h"
DHTlib dht;

#include "SHTC3.h"
SHTC3 s(Wire);


const int trigPin = D1;
const int echoPin = D2;

long duration;
int distance;

DHTlib::DHTlib() {}

void DHTlib::initDHT() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void DHTlib::readDHT()
{
  s.begin(true);
    s.sample();
    // Serial.print("  อุณหภูมิ ");
    // Serial.print(s.readTempC());
    // Serial.print("  °C    ความชื้น ");
    // Serial.print(s.readHumidity());
    dht.temp = s.readTempC();
    dht.hum = s.readHumidity();
    // Serial.println(" %");
    delay(500);
}
float DHTlib::getTemp()
{
  return dht.temp;
}
float DHTlib::getHum()
{
  return dht.hum;
}