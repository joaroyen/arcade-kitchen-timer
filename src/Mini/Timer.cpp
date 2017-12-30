#include <Arduino.h>
#include "Common.h"
#include "Timer.h"

static const int INITIAL_INPUT_DELAY_WINDOW = 2000;

Timer::Timer() {
  stop();
}

void Timer::addMinutes(int minutes) {
  _lastInputTime = millis();

  int seconds = minutes * TIME_FACTOR;

  if (_endTime == 0) {
    _inputSeconds += seconds;
  }
  else {
    if (getSecondsRemaining() <= 0) {
      _endTime = currentTimeInSeconds() + seconds;
    }
    else {
      _endTime += seconds;
    }
  }
}

void Timer::start() {
  _endTime = currentTimeInSeconds() + _inputSeconds;
}

void Timer::stop() {
  _endTime = 0;
  _inputSeconds = 0;
  _lastInputTime = 0;
}

void Timer::update() {
  if (isRunning()) {
    _lastInputTime = 0;
  }
  else if (millis() - _lastInputTime > INITIAL_INPUT_DELAY_WINDOW && _inputSeconds > 0) {
    start();
  }
}

bool Timer::isRunning() {
  return _endTime > 0;  
}

int Timer::getSecondsRemaining() {
  if (isRunning()) {
    return _endTime - currentTimeInSeconds();  
  }
  else {
    return _inputSeconds;
  }
}

int Timer::getInitialInputSeconds() {
  return _inputSeconds;
}

int Timer::currentTimeInSeconds() {
  return millis() / 1000;
}

