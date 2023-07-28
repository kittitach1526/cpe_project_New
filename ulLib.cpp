#include "ulLib.h"
ulLib ul;

ulLib::ulLib() {
}

void ulLib::initUL() {
  pinMode(ul.trig, OUTPUT);
  pinMode(ul.ec, INPUT);
}

float ulLib::read_ul() {
  digitalWrite(ul.trig, LOW);
  delayMicroseconds(2);

  digitalWrite(ul.trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ul.trig, LOW);

  ul.duration = pulseIn(ul.ec, HIGH);
  ul.distance = ul.duration * 0.034 / 2;
  //Serial.print("Distance: ");
  //Serial.print(ul.distance);
  delay(100);
  return ul.distance;
}