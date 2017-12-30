#ifndef __Common_h
#define __Common_h

//#define DEBUG

#ifdef DEBUG
    static const int TIME_FACTOR = 1;
#else
    static const int TIME_FACTOR = 60;
#endif

static const int ALARM_DURATION_IN_SECONDS = 30;

static const byte DISPLAY_INTENSITY_LOW = 1;
static const byte DISPLAY_INTENSITY_HIGH = 10;


#define NOTE_E5  659
#define NOTE_A5  880
#define NOTE_C6  1047

#define NOTE_C4  262
#define NOTE_A4  440
#define NOTE_C5  523

static const int AUDIO_FREQUENCY_LOW_BEEP = NOTE_C5;
static const int AUDIO_FREQUENCY_HIGH_BEEP = NOTE_A5;
static const int AUDIO_FREQUENCY_ALARM = NOTE_E5;

#endif
