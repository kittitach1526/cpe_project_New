#include "pump.h"
pump p;
pump::pump()
{

}
void pump::initPump()
{
  pinMode(p.pin,OUTPUT);

}
void pump::pumpOn()
{
  digitalWrite(p.pin,HIGH);
}
void pump::pumpOff()
{
  digitalWrite(p.pin,LOW);
}
