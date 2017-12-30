#include "Common.h"
#include "Display.h"


static const byte SCAN_LIMIT = B011;

static const byte DATA_PIN = 2;
static const byte CLOCK_PIN = 1;
static const byte LOAD_PIN = 0;

static const byte MAX7219_OP_DIGIT_0 = 1;
static const byte MAX7219_OP_DIGIT_1 = 3;
static const byte MAX7219_OP_DIGIT_2 = 4;
static const byte MAX7219_OP_DIGIT_3 = 2;
static const byte MAX7219_OP_DECODEMODE = 9;
static const byte MAX7219_OP_INTENSITY = 10;
static const byte MAX7219_OP_SCANLIMIT = 11;
static const byte MAX7219_OP_SHUTDOWN = 12;
static const byte MAX7219_OP_DISPLAYTEST = 15;

static const byte LED_SEGMENTS_SPACE = B00000000;
// Not using one-to-one segment mapping to improve PCB routing
static const byte LED_SEGMENTS_DIGITS[] = { 
  B11111110, 
  B01010100, 
  B11101101,
  B11110101,
  B01010111,
  B10110111,
  B10111111,
  B01110100,
  B11111111,
  B11110111
};

Display::Display(Timer* timer) {
  _timer = timer;
}

void Display::wakeUp() {
  initialize(); 
  on();
}

void Display::shutdown() {
  off();
  pinMode(DATA_PIN, INPUT);
  pinMode(CLOCK_PIN, INPUT);
  pinMode(LOAD_PIN, INPUT);
}

void Display::update() {
  int seconds = _timer->getSecondsRemaining();
  if (seconds <= 0) {
    seconds = 0;
    if (_timer->isRunning()) {
      flashDisplay();
    }
  }
  else if (!_previousState){
    on();
    _previousState = true;
  }

  
  if (seconds == _previousUpdateSeconds) return;
  _previousUpdateSeconds = seconds;

  adjustIntensity(seconds);
  if (seconds >= 3600) {
    writeHoursAndMinutes(seconds);
  }
  else {
    writeMinutesAndSeconds(seconds);
  }
}

void Display::initialize() {
  _previousUpdateSeconds = -9999;
  _previousState = false;
  _previousIntensity = DISPLAY_INTENSITY_HIGH;

  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LOAD_PIN, OUTPUT);
  digitalWrite(LOAD_PIN, HIGH);

  spiTransfer(MAX7219_OP_DISPLAYTEST, 0);
  spiTransfer(MAX7219_OP_SCANLIMIT, SCAN_LIMIT);
  spiTransfer(MAX7219_OP_DECODEMODE, 0);
  spiTransfer(MAX7219_OP_INTENSITY, DISPLAY_INTENSITY_HIGH);
  writeTime(0, 0);
}

void Display::on() {
  spiTransfer(MAX7219_OP_DISPLAYTEST, 0);
  spiTransfer(MAX7219_OP_SCANLIMIT, SCAN_LIMIT);
  spiTransfer(MAX7219_OP_DECODEMODE, 0);

  spiTransfer(MAX7219_OP_SHUTDOWN, 1);
}

void Display::off() {
  spiTransfer(MAX7219_OP_SHUTDOWN, 0);
}

void Display::writeHoursAndMinutes(int seconds) {
  writeTime(seconds / 3600, (seconds / 60) % 60);
}

void Display::writeMinutesAndSeconds(int seconds) {
  writeTime((seconds / 60) % 60, seconds % 60);
}

void Display::writeTime(int upper, int lower) {
  byte firstDigit = upper / 10;
  if (firstDigit == 0) {
    spiTransfer(MAX7219_OP_DIGIT_0, LED_SEGMENTS_SPACE);
  }
  else {
    spiTransfer(MAX7219_OP_DIGIT_0, LED_SEGMENTS_DIGITS[firstDigit]);
  }
  spiTransfer(MAX7219_OP_DIGIT_1, LED_SEGMENTS_DIGITS[upper % 10]);
  spiTransfer(MAX7219_OP_DIGIT_2, LED_SEGMENTS_DIGITS[lower / 10]);
  spiTransfer(MAX7219_OP_DIGIT_3, LED_SEGMENTS_DIGITS[lower % 10]);
}

void Display::spiTransfer(byte opcode, byte data) {
  digitalWrite(LOAD_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, opcode);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, data);
  digitalWrite(LOAD_PIN, HIGH);
}

void Display::flashDisplay() {
  if (millis() % 1000 > 400) {
    if (!_previousState) {
      on();
      _previousState = true;
    }
  }
  else if (_previousState) {
    off();
    _previousState = false;
  }
}

void Display::adjustIntensity(int seconds) {
  if (!_timer->isRunning() || seconds <= 60 || seconds % 60 == 0) {
      if (_previousIntensity != DISPLAY_INTENSITY_HIGH) {
        spiTransfer(MAX7219_OP_INTENSITY, DISPLAY_INTENSITY_HIGH);
        _previousIntensity = DISPLAY_INTENSITY_HIGH;
      }
  }
  else {
      if (_previousIntensity != DISPLAY_INTENSITY_LOW) {
        spiTransfer(MAX7219_OP_INTENSITY, DISPLAY_INTENSITY_LOW);
        _previousIntensity = DISPLAY_INTENSITY_LOW;
      }
  }
}
