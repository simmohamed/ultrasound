/*
Button.cpp - library for button
*/

#include "Arduino.h"
#include "Button.h"

Button::Button(int pin)
{
  pinMode(pin, INPUT_PULLUP);
  _pin=pin;
  _prevState=digitalRead(pin);
}



bool Button::pressed(){
  bool ret=0;
  int x=digitalRead(_pin);
  if(x!=_prevState && x==BUTTONPRESSED){
    ret=1;
    delay(BOUNCE);
  }
  _prevState=x;
  return ret;
} 
