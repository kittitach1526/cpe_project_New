#ifndef line_H
#define line_H
#include <Arduino.h>

class line {


public:
  line();
  void setToken(String token);
  void sendText(String data);
  void sendPic(String url);
  void sendPicText(String text, String url);



private:
};
extern line L;
#endif