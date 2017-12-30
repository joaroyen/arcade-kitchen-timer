#include "Common.h"
#include "Audio.h"

const uint8_t BUZZER_PIN = 3;
const unsigned long DURATION = 50;

Audio::Audio(Timer* timer) {
  wakeUp();
  _timer = timer;
  _previousUpdateSeconds = 0;
}

void Audio::wakeUp() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void Audio::update() {
  if (!_timer->isRunning()) return;
  int currentSeconds = _timer->getSecondsRemaining();
  if (currentSeconds == _previousUpdateSeconds && currentSeconds > 0) return;
  _previousUpdateSeconds = currentSeconds;
  if (currentSeconds < 0 && abs(currentSeconds) >= ALARM_DURATION_IN_SECONDS) return;

  if (currentSeconds == TIME_FACTOR * 10 && _timer->getInitialInputSeconds() >= TIME_FACTOR * 60) {
    beep(AUDIO_FREQUENCY_HIGH_BEEP);
  }
  else if (currentSeconds == TIME_FACTOR && _timer->getInitialInputSeconds() >= TIME_FACTOR * 10) {
    beep(AUDIO_FREQUENCY_HIGH_BEEP);
  }
  else if (currentSeconds == 30) {
    beep(AUDIO_FREQUENCY_LOW_BEEP);
  }
  else if (currentSeconds == 5) {
    beep(AUDIO_FREQUENCY_HIGH_BEEP);
  }
  else if (currentSeconds <= 4 && currentSeconds > 0) {
    beep(AUDIO_FREQUENCY_LOW_BEEP);
  }
  else if (currentSeconds <= 0) {
    int currentTimeTenth = millis() % 1000 / 100;
    if (currentTimeTenth == _previousTimeTenth) return;
    _previousTimeTenth = currentTimeTenth;
    
    if (currentTimeTenth < 3) {
      beep(AUDIO_FREQUENCY_ALARM);
    }
  }
}

void Audio::beep(unsigned int frequency) {
  tone(BUZZER_PIN, frequency, DURATION);
}

