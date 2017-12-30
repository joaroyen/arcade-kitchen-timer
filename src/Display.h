#ifndef __Display_h
#define __Display_h

#include "Timer.h"


class Display {
  public:
    Display(Timer* timer);
    void initialize();
    void update();
    void wakeUp();
    void shutdown();
  private:
    Timer* _timer;
    int _previousUpdateSeconds;
    bool _previousState;
    int _previousIntensity;
    void on();
    void off();
    void writeHoursAndMinutes(int seconds);
    void writeMinutesAndSeconds(int seconds);
    void writeTime(int upper, int lower);
    void spiTransfer(byte opcode, byte data);
    void flashDisplay();
    void adjustIntensity(int seconds);
};

#endif
