#include "line.h"
line L;
#include <TridentTD_LineNotify.h>

line::line()
{

}
void line::setToken(String token)
{
  LINE.setToken(token);
}
void line::sendText(String data)
{
  LINE.notify(data);
}
void line::sendPic(String url)
{
  LINE.notifyPicture(url);
}
void line::sendPicText(String text,String url)
{
  LINE.notifyPicture(text,url);
}