#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6EV82d6Ta"
#define BLYNK_TEMPLATE_NAME "CPE6K"
#define BLYNK_AUTH_TOKEN "twP0LHSGQXBl8fBKjjC-cqIKEbwiYTgg"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include "DHTlib.h"
#include "display.h"
#include "line.h"
#include "ulLib.h"
#include <EasyScheduler.h>
#include "pump.h"
Schedular Task1;
Schedular Task2;
byte st = 0;
byte pump, backup_st;
char ssid[] = "4G-UFI-5C2";
char pass[] = "1234567890";
float dis, tem, humi, setLevel, now_level;
int maxLevel, minLevel, setLevelSW;

BLYNK_WRITE(V2)  //switch pump
{
  int dataV2 = param.asInt();
  pump = dataV2;
}
BLYNK_WRITE(V4)  // max level
{
  maxLevel = param.asInt();
}
BLYNK_WRITE(V5)  //min level
{
  minLevel = param.asInt();
}
BLYNK_WRITE(V7)  //min level
{
  st = param.asInt();
}

BLYNK_WRITE(V6)  //min level
{
  setLevelSW = param.asInt();
  if (setLevelSW == 1) {
    setLevel = dis;
  }
  if (setLevelSW == 0) {
    setLevel = 0;
  }
}
void setup() {
  Serial.begin(9600);
  Wire.begin();
  dht.initDHT();
  dp.initDP();
  ul.initUL();
  p.initPump();
  Task1.start();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  p.pumpOff();
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V4);
  Blynk.syncVirtual(V5);
  Blynk.syncVirtual(V6);
  Blynk.syncVirtual(V7);
  backup_st = 0;
  L.setToken("m0n35nvghOzI9Q1czQIcp64LkDwzV8XwUY2Q7MebPgH");
  L.sendText("ESP Ready !");
}
void readAll() {
  dht.readDHT();
  dis = ul.read_ul();
  tem = dht.getTemp();
  humi = dht.getHum();
  now_level = setLevel - dis;
  dp.clear();
  dp.print(0, 1, String(dis));
  dp.print(8, 1, String(now_level));
  dp.print(8, 0, String(tem) + "'C");
  dp.print(0, 0, String(humi) + "%");
  writeBlynk();
}
void writeBlynk() {
  Blynk.virtualWrite(V0, tem);
  Blynk.virtualWrite(V1, humi);
  Blynk.virtualWrite(V3, now_level);
}
void process_system() {
  if (now_level >= maxLevel) {
    p.pumpOff();
    Blynk.virtualWrite(V2, 0);
    if(L.sendHigh == 0)
    {
      L.sendText("high level");
      L.sendHigh = 1;
      L.sendReached=0;
    }
    
  }
  if (now_level < minLevel) {
    p.pumpOn();
    Blynk.virtualWrite(V2, 1);
    if(L.sendLow == 0)
    {
      L.sendText("low level");
      L.sendLow =1;
      L.sendReached=0;
    }
  }
  if ((now_level > minLevel) && (now_level < maxLevel)&&(now_level>=0 )) {
    Blynk.virtualWrite(V2, 0);
    p.pumpOff();
    if(L.sendReached == 0)
    {
      L.sendText("reached level ");
      L.sendReached =1;
      L.sendHigh=0;
      L.sendLow=0;
    }
  }
}
void loop() {
  Task1.check(readAll, 1000);
  if (st == 0) {
    if (pump == 0) p.pumpOff();
    if (pump == 1) p.pumpOn();
  }
  if (st == 1) {
    process_system();
  }
  if (st != backup_st) {
    Blynk.syncVirtual(V2);
    backup_st = st;
  }
  Blynk.run();
}

