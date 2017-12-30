#include "Common.h"
#include "Input.h"


const int INPUT_PIN = A2;

const int INPUT_VALUE_DEVIATION = 20;
const int INPUT_1_VALUE = 609;
const int INPUT_10_VALUE = 769;
const int INPUT_1_AND_10_VALUE = 837;

Input::Input(Timer* timer) {
  _timer = timer;
  wakeUp();
}

void Input::wakeUp() {
  pinMode(INPUT_PIN, INPUT);
  initialize();
}

void Input::read() {
  int command = readCommand();
  if (command > COMMAND_NONE) {
    _timer->addMinutes(command);
  }
}


int Input::initialize() {
  _totalReadValue = 0;
  _numberOfReadValues = 0;
}

int Input::readCommand(){
  int value = readAnalogInput();
  if (value < 500) {
    initialize();
    return COMMAND_NONE;
  }
  _totalReadValue += value;
  _numberOfReadValues++;

  if (_numberOfReadValues == 10) {
    return valueToCommand();
  }
  else if (_numberOfReadValues % 150 == 0) {
    return valueToCommand();
  }
  else {
    return COMMAND_NONE;
  }
}

int Input::valueToCommand() {
  int inputValue = _totalReadValue / _numberOfReadValues;

  if (inputValue > INPUT_1_VALUE - INPUT_VALUE_DEVIATION && inputValue < INPUT_1_VALUE + INPUT_VALUE_DEVIATION) {
    return COMMAND_1;
  }
  else if (inputValue > INPUT_10_VALUE - INPUT_VALUE_DEVIATION && inputValue < INPUT_10_VALUE + INPUT_VALUE_DEVIATION) {
    return COMMAND_10;
  }
  else if (inputValue > INPUT_1_AND_10_VALUE - INPUT_VALUE_DEVIATION && inputValue < INPUT_1_AND_10_VALUE + INPUT_VALUE_DEVIATION) {
    return COMMAND_60;
  }
  else {
    return COMMAND_NONE;
  }
}

int Input::readAnalogInput() {
  delay(1);
  return analogRead(INPUT_PIN);
}
