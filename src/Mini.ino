#include "Common.h"
#include "Timer.h"
#include "Input.h"
#include "Display.h"
#include "Power.h"
#include "Audio.h"

Timer timer = Timer();
Input input = Input(&timer);
Display display = Display(&timer);
Power power = Power(&timer);
Audio audio = Audio(&timer);

void setup() {
  OSCCAL = DEVICE_OSCILLATOR_CALIBRATION;

  display.initialize();
  sleep();
}

void loop() {
  timer.update();

  input.read();
  display.update();
  audio.update();
  
  power.thinkAboutGoingToSleep();
}

void sleep() {
  display.shutdown();
  power.sleep();
  
  input.wakeUp();
  display.wakeUp();
  audio.wakeUp();
}

