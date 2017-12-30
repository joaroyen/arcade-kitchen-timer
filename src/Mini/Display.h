#ifndef __Display_h
#define __Display_h

#include <Arduino.h>
#include "Audio.h"


class Display {
  public:
    Display(Audio* audio);
    void initialize();
    void update();
    void wakeUp();
    void shutdown();
  private:
    Audio* _audio;
    int _previousUpdateSeconds;
    bool _previousState;
    int _previousIntensity;
    void on();
    void off();
    void write(int frequency);
    void Display::spiTransfer(byte opcode, byte data);
};

#endif
