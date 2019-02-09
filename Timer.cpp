#include "Timer.h"
#include "Arduino.h"

typedef void (* CallBack)();

static uint32_t Timer::getMillis(void) { return millis(); } 
static uint32_t Timer::getSeconds(void) { return millis() / 1000; } 



void Timer::set(uint8_t frequency, uint32_t time, CallBack callback) { 
  this->_time = time;
  this->_frequency = frequency;
  this->_callback = callback;
}

void Timer::setTime(uint32_t time) { 
  this->_time = time;
}

void Timer::start() {
  this->_state = Timer::RUNNING;
}

void Timer::run() {
  if ((Timer::getMillis() - this->_timeStart) >= this->_time) {
    this->_timeStart = Timer::getMillis();
  } else {
    return;
  } 

  if (this->_state == Timer::PAUSED) {
    return;
  }


  if(this->_frequency == Timer::NEVER) {
    //do nothing
  } else if (this->_frequency == Timer::FOREVER ) {
    this->_callback();
  } else if (this->_frequency > this->_count) {
    this->_count++;
    this->_callback();
  }
}

void Timer::stop() {
  this->_frequency = Timer::NEVER;
}

void Timer::pause() {
  this->_state = Timer::PAUSED;
}