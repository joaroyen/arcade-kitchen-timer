#ifndef __Audio_h
#define __Audio_h

#include <Arduino.h>

class Audio {
  public:
    Audio();
    void wakeUp();
    void up();
    void down();
    void update();
    int getFrequency();
  private:
    int _frequency;
    int _previousSecond;
};

#endif
