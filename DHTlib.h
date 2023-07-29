#ifndef DHTlib_H
#define DHTlib_H
#include <Arduino.h>
class DHTlib{

  public:
    DHTlib();
    void initDHT();
    void readDHT();
    float getTemp();
    float getHum();
    float temp,hum;

  private:


};
extern DHTlib dht;
#endif