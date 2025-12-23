#include "output-config.h"

Output::Output(byte pin, bool invert, String oname) {
  ltime = 0;
  cstate = 0;
  this->oname = oname;
  this->invert = invert;
  this->pin = pin;
  init();
}
void Output::init() {
  pinMode(pin, OUTPUT);
  off();
}
void Output::on() {
  cstate = 1;
  if (invert)
    digitalWrite(pin, LOW);
  else
    digitalWrite(pin, HIGH);
}

void Output::off() {
  cstate = 0;
  //  Debug.print(DBG_INFO, "ping %d LED OFF  %d",pin,OffTime);
  if (invert)
    digitalWrite(pin, HIGH);
  else
    digitalWrite(pin, LOW);
}

void Output::OnForTime(char ontime) {
  OnTime = 1;
}

Output OutRelay[MAX_OUTPUT] = { Output(PIN_OUT1, 0, "OUT1"), Output(PIN_OUT2, 0, "OUT2") };
