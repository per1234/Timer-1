#ifndef _TIMER_H
#define _TIMER_H

#include "Timer.h"
#include "Arduino.h"

/// @author Rhalf Wendel D Caacbay <rhalfcaacbay@gmail.com>
typedef void (* CallBack)();

class Timer {

public:

  static uint32_t runTime;

  static const uint8_t FOREVER = -1;
  static const uint8_t NEVER = 0;
  static const uint8_t ONCE = 1;
  static const uint8_t TWICE = 2;



  static uint32_t getTimeMillis(void);
  static uint32_t getTimeSecond(void);

  void set(uint8_t frequency, uint32_t time, CallBack callback);
  void setTime(uint32_t time);
  


  void start();
  void stop();
  void run();
  void pause();

private:

  static const uint8_t STOPPED = -1;
  static const uint8_t PAUSED = 0;
  static const uint8_t RUNNING = 1;
  

  uint8_t _state = 0;
  uint8_t _frequency = 0;
  uint8_t _count = 0;

  uint32_t _timeStart = 0;
  uint32_t _time = 0;


  CallBack _callback = NULL;
};
#endif // _TIMER_H
