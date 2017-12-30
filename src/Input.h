#ifndef __Input_h
#define __Input_h

#include "Timer.h"


const int COMMAND_NONE = 0;
const int COMMAND_1 = 1;
const int COMMAND_10 = 10;
const int COMMAND_60 = 60;

class Input {
  public:
    Input(Timer* timer);
    void wakeUp();
    void read();
  private:
    Timer* _timer;
    int _previousReadTime;
    long _totalReadValue;
    int _numberOfReadValues;
    int initialize();
    int readCommand();
    int valueToCommand();
    int readAnalogInput();
};

#endif
