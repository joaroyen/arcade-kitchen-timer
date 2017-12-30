#include <Arduino.h>

#include "Common.h"
#include "Audio.h"

const uint8_t BUZZER_PIN = 3;

Audio::Audio() {
  wakeUp();
  _frequency = NOTE_E5;
  _previousSecond = -1;

}

void Audio::wakeUp() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

int previousSecond;
void Audio::update() {
  int currentSecond = millis() / 1000;
  if (currentSecond > _previousSecond) {
    tone(BUZZER_PIN, _frequency, 200);
    _previousSecond = currentSecond;
  }
}

void Audio::up() {
  _frequency++;
}

void Audio::down() {
  _frequency--;
}

int Audio::getFrequency(){
  return _frequency;
}


