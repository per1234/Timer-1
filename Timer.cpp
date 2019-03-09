#include "Timer.h"
#include "Arduino.h"

typedef void (* Callback)();

static uint32_t Timer::getMicros(void) { return micros(); } 
static uint32_t Timer::getMillis(void) { return millis(); } 
static uint32_t Timer::getSeconds(void) { return millis() / 1000; } 


Timer::Timer(uint8_t unit){
  _unit = unit;
}


void Timer::begin(uint8_t frequency, uint32_t timeInterval, Callback callback) { 
  _timeInterval = timeInterval;
  _frequency = frequency;
  _callback = callback;
}

void Timer::setFrequency(uint8_t frequency) { 
  _frequency = frequency;
}

void Timer::setTimeInterval(uint32_t timeInterval) { 
  _timeInterval = timeInterval;
}

void Timer::setCallback(Callback callback) { 
  _callback = callback;
}

void Timer::start() {
  _state = Timer::STARTED;
}

uint32_t Timer::getTime(void) {
  if (_unit == Timer::MICROS) return Timer::getMicros();
  else if (_unit == Timer::MILLIS) return Timer::getMillis();
  else if (_unit == Timer::SECONDS) return Timer::getSeconds();
}

uint32_t Timer::getTimeElapse(void) {
    return getTime() - _timeStart;
}

void Timer::run() {
  if (getTimeElapse() >= _timeInterval) _timeStart = getTime();
  else return; 

  if (_state == Timer::STOPPED) return;

  if (_frequency == Timer::NEVER) { /*do nothing */ } 
  else if (_frequency == Timer::FOREVER ) { _callback(); } 
  else if (_frequency > _count) { _count++; _callback(); }

}

void Timer::stop() {
  _state = Timer::STOPPED;
}
