#include <Arduino.h>

#include "Common.h"
#include "Display.h"
#include "Audio.h"

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

Display::Display(Audio* audio) {
  _audio = audio;
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
  int frequency = _audio->getFrequency();

  write(frequency);
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
  write(0);
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

void Display::write(int frequency) {
  spiTransfer(MAX7219_OP_DIGIT_0, LED_SEGMENTS_DIGITS[frequency / 1000]);
  spiTransfer(MAX7219_OP_DIGIT_1, LED_SEGMENTS_DIGITS[frequency / 100 % 10]);
  spiTransfer(MAX7219_OP_DIGIT_2, LED_SEGMENTS_DIGITS[frequency / 10 % 10]);
  spiTransfer(MAX7219_OP_DIGIT_3, LED_SEGMENTS_DIGITS[frequency % 10]);
}

void Display::spiTransfer(byte opcode, byte data) {
  digitalWrite(LOAD_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, opcode);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, data);
  digitalWrite(LOAD_PIN, HIGH);
}
