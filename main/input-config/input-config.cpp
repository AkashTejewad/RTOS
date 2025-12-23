#include <stdio.h>
#include "input-config.h"


void Input::init() {
  pinMode(pin, INPUT);
}

Input::Input(byte pin, bool invert, byte dtime, char *inname)  //constructor define here
{
  debouncet = dtime;
  tcount = 0;
  current = 0;
  previnput = 0;
  change = 1;
  strncpy(this->inname, inname, 9);
  this->inname[9] = 0;
  this->invert = invert;
  this->pin = pin;
  init();
}

bool Input::readraw()  //readraw method defined here
{
  bool state;
  state = digitalRead(pin);
  if (invert)
    state = !state;
  return (state);
}

void Input::Poll()  //poll method defined here
{
  bool st;
  st = readraw();
  if ((st != previnput) && (tcount == 0)) {
    previnput = st;
    tcount++;
  }
  if (tcount >= 1) {
    if (st == previnput)
      tcount++;
    else
      tcount = 0;
    if (tcount >= debouncet) {
      if (previnput != current) {
        current = previnput;
        change = 1;
      }
    }
  }
}

Input IN_Config(CONFIG_PIN, 0, 3, "CONF");
Input IN_Pin[MAX_INPUT] = {Input(PIN_IN1, 0, 3, "IN1"), Input(PIN_IN2, 0, 3, "IN2")};
Input IN_Pin_Analog[MAX_INPUT] = {Input(PIN_IN1, 1, 3, "IN1_AG"), Input(PIN_IN2, 1, 3, "IN2_AG")};