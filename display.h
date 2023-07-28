#ifndef display_H
#define display_H
#include <Arduino.h>
class display{
  public:
    display();
    void initDP();
    void clear();
    void setbacklight();
    void print(byte c,byte r,String data);


  private:


};
extern display dp;
#endif