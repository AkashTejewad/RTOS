#ifndef OUTPUT_CONFIG
#define OUTPUT_CONFIG

#include "Arduino.h"

#define MAX_OUTPUT 2

#define PIN_OUT1 14
#define PIN_OUT2 13

// extern "C"
// {
    class Output
    {
    public:
        byte pin;
        byte ltime;
        byte OnTime;
        bool cstate;
        bool invert;
        String oname;
        Output(byte pin, bool invert, String oname);
        void init();
        void on();
        void off();
        void OnForTime(char ontime);
    };
// }

extern Output OutRelay[MAX_OUTPUT];

#endif