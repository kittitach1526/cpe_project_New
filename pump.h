#ifndef pump_H
#define pump_H
#include <Arduino.h>
class pump
{
  public :
  pump();
  void initPump();
  void pumpOn();
  void pumpOff();
  



  private:
  byte pin = D5;


};
extern pump p;
#endif