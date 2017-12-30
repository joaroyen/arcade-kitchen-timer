#ifndef __Common_h
#define __Common_h

#define ATTINY_CORE
#define ATTINYX5 1

#include <arduino.h>
#include <avr/iotn85.h>


static const int DEVICE_OSCILLATOR_CALIBRATION = #INSERT OSCCAL HERE#;

//#define DEBUG

#ifdef DEBUG
    static const int TIME_FACTOR = 1;
#else
    static const int TIME_FACTOR = 60;
#endif

static const int ALARM_DURATION_IN_SECONDS = 30;

static const byte DISPLAY_INTENSITY_LOW = 1;
static const byte DISPLAY_INTENSITY_HIGH = 10;

static const int AUDIO_FREQUENCY_LOW_BEEP = 488;
static const int AUDIO_FREQUENCY_HIGH_BEEP = 970;
static const int AUDIO_FREQUENCY_ALARM = 673;

#endif