#ifndef INPUT_CONFIG
#define INPUT_CONFIG

#include "Arduino.h"

#define CONFIG_PIN 0
#define PIN_IN1 5   //Input 1 digital pin
#define PIN_IN2 18  //Input 2 digital pin
#define MAX_INPUT 2


// extern "C"
// {
    class Input
    {
    public:
        byte pin;
        bool invert;
        bool current;
        bool previnput;
        bool change;
        byte debouncet;
        byte tcount;
        char inname[10];
        Input(byte pin, bool invert, byte dtime, char *inname); // constructor
        void Poll();                                            // method
        bool readraw();                                         // method
        void init();                                            // method
    };
// }

extern Input IN_Config;
extern Input IN_Pin[MAX_INPUT];
extern Input IN_Pin_Analog[MAX_INPUT];

#endif