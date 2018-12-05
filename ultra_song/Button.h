/*
Button.h - library for buttons
*/

#ifndef Button_h
#define Button_h
#include "Arduino.h"

const int BUTTONPRESSED=LOW;
const int BOUNCE=20;

class Button
{
  public:
    Button(int pin);
    bool pressed();
    void downButton();
    void enterButton();
    void upButton();
  private:
    int _pin;
    int _prevState;
};

#endif
