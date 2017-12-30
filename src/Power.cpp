#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>


#include "Common.h"
#include "Power.h"


Power::Power(Timer* timer) {
  _timer = timer;
  wdt_disable();
}

void Power::thinkAboutGoingToSleep() {
  if (_timer->getSecondsRemaining() < -ALARM_DURATION_IN_SECONDS) {
    reset();
  }
}

void Power::sleep() {
  powerDown();
  sleep_cpu();
  wakeUp();  
}

void Power::reset() {
  
  cli();
  _WD_CONTROL_REG = _BV(WDIE) | WDTO_15MS;
  sei();
  
  wdt_reset();
  while (true) {}
}

void Power::powerDown() {
  resetPins();  
  setupInterrupt();
  power_all_disable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_bod_disable();
}

void Power::wakeUp() {
  clearInterrupt();
  sleep_disable();
  power_all_enable();
  reenableInterrupt();
}

void Power::setupInterrupt() {
  bitSet(GIMSK, PCIE);
  bitSet(PCMSK, PCINT4);
  sei();
}

void Power::clearInterrupt() {
  cli();
  bitClear(PCMSK, PCINT4);
}

void Power::reenableInterrupt() {
  sei();
}

void Power::resetPins() {
  for (int pinNumber = 0; pinNumber < 5; pinNumber++) {
    digitalWrite(pinNumber, LOW);  
    pinMode(pinNumber, INPUT);
  }
}

ISR(PCINT0_vect) {
}
