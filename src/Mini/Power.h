#ifndef __Power_h
#define __Power_h

#include "Timer.h"


class Power {
  public:
    Power(Timer* timer);
    void thinkAboutGoingToSleep();
    void sleep();
  private:
    Timer* _timer;
    void powerDown();
    void wakeUp();
    void setupInterrupt();
    void clearInterrupt();
    void reenableInterrupt();
    void resetPins();
    void reset();
};

#endif
