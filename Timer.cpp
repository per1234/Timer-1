#include "Timer.h"
#include "Arduino.h"

typedef void (* CallBack)();

static uint32_t Timer::getMicros(void) { return micros(); } 
static uint32_t Timer::getMillis(void) { return millis(); } 
static uint32_t Timer::getSeconds(void) { return millis() / 1000; } 


Timer::Timer(uint8_t unit){
  _unit = unit;
}


void Timer::set(uint8_t frequency, uint32_t time, CallBack callback) { 
  _time = time;
  _frequency = frequency;
  _callback = callback;
}

void Timer::setTime(uint32_t time) { 
  _time = time;
}

void Timer::start() {
  _state = Timer::RUNNING;
}

uint32_t Timer::getCount(void) {
  if (_unit == Timer::MICROS) return Timer::getMicros();
  else if (_unit == Timer::MILLIS) return Timer::getMillis();
  else if (_unit == Timer::SECONDS) return Timer::getSeconds();
}

void Timer::run() {
  uint32_t time = getCount();
  uint32_t timeElapse = time - _timeStart;

  if (timeElapse >= _time) _timeStart = getCount();
  else return; 

  if (_state == Timer::PAUSED) return;

  if (_frequency == Timer::NEVER) { /*do nothing */ } 
  else if (_frequency == Timer::FOREVER ) _callback(); 
  else if (_frequency > _count) { _count++; _callback(); }

}

void Timer::stop() {
  _frequency = Timer::NEVER;
}

void Timer::pause() {
  _state = Timer::PAUSED;
}