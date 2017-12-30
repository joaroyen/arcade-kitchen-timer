#ifndef __Audio_h
#define __Audio_h

#include "Timer.h"


class Audio {
  public:
    Audio(Timer* timer);
    void wakeUp();
    void update();
  private:
    Timer* _timer;
    int _previousUpdateSeconds;
    int _previousTimeTenth;
    void beep(unsigned int frequency);
};

#endif
