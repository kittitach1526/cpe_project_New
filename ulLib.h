#ifndef ulLib_H
#define ulLib_H
#include <Arduino.h>
class ulLib {
public:
  ulLib();
  void initUL();
  float read_ul();



private:
  byte trig = D3;
  byte ec = D4;
  float distance;
  long duration;
};
extern ulLib ul;
#endif