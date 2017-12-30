#include "Input.h"
#include "Display.h"
#include "Power.h"
#include "Audio.h"

Audio audio = Audio();
Input input = Input(&audio);
Display display = Display(&audio);
Power power = Power();

void setup() {
  display.initialize();
  sleep();
}

void loop() {
  input.read();
  audio.update();
  display.update();
}

void sleep() {
  display.shutdown();
  power.sleep();
  
  input.wakeUp();
  display.wakeUp();
  audio.wakeUp();
}

