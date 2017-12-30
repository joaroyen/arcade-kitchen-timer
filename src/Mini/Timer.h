#ifndef __Timer_h
#define __Timer_h

#include "Arduino.h"

class Timer {
  public:
    Timer();
    void addMinutes(int seconds);
    void update();
    void stop();
    bool isRunning();
    int getSecondsRemaining();
    int getInitialInputSeconds();
  private:
    int _endTime;
    int _inputSeconds;
    unsigned long _lastInputTime;
    void start();
    int currentTimeInSeconds();
};

#endif
