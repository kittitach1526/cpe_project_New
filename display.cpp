#include "display.h"
display dp;
#include "public_lib.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

display::display(){

}
void display::initDP()
{
  lcd.begin();
  lcd.backlight();
}
void display::clear()
{
  lcd.clear();
}
void display::setbacklight()
{
  
}
void display::print(byte c, byte r,String data)
{
  lcd.setCursor(c, r);
  lcd.print(data);
}