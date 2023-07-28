#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6EV82d6Ta"
#define BLYNK_TEMPLATE_NAME "CPE6K"
#define BLYNK_AUTH_TOKEN "twP0LHSGQXBl8fBKjjC-cqIKEbwiYTgg"
#define LINE_TOKEN "m0n35nvghOzI9Q1czQIcp64LkDwzV8XwUY2Q7MebPgH"

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
char ssid[] = "thestrongest";
char pass[] = "77777777";
float dis, tem, humi, setLevel, now_level;
int maxLevel, minLevel, setLevelSW;

BLYNK_WRITE(V2)  //switch pump
{
  int dataV2 = param.asInt();
  pump = dataV2;
  Serial.println("Swithc PUMP  : " + String(dataV2));
  if (dataV2 == 1) {
    L.sendText("Pump : ON");
  }
  if (dataV2 == 0) {
    L.sendText("Pump : OFF");
  }
}
BLYNK_WRITE(V4)  // max level
{
  maxLevel = param.asInt();
  Serial.println("Set max level = " + String(maxLevel));
  String mes = "Set max level = " + String(maxLevel);
  L.sendText(mes);
}
BLYNK_WRITE(V5)  //min level
{
  minLevel = param.asInt();
  Serial.println("Set min level = " + String(minLevel));
  String mes = "Set min level = " + String(minLevel);
  L.sendText(mes);
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
    Serial.println("set lv : " + String(setLevel));
    L.sendText("Set Level water : " + String(setLevel));
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
  Task2.start();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  L.setToken(LINE_TOKEN);
  L.sendText("ESP on ");
  Serial.println("ESP on !! ");
  p.pumpOff();
  Blynk.syncVirtual(V2);
  delay(500);
  Blynk.syncVirtual(V4);
  delay(500);
  Blynk.syncVirtual(V5);
  delay(500);
  Blynk.syncVirtual(V6);
  delay(500);
  Blynk.syncVirtual(V7);
  delay(500);
  backup_st = 0;
}

void loop() {
  Task1.check(readAll, 1000);
  if (st == 0) {
    //Blynk.syncVirtual(V2);
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
    Serial.println("off");
    p.pumpOff();
    Blynk.virtualWrite(V2, 0);
  }
  if (now_level < minLevel) {
    Serial.println("on");
    p.pumpOn();
    Blynk.virtualWrite(V2, 1);
  }
  if ((now_level > minLevel) && (now_level < maxLevel)) {
    Serial.println("Bal");
    Blynk.virtualWrite(V2, 0);
    p.pumpOff();
  }
}