#include<Timer.h>

Timer timer0;

void callback0() {
    Serial.println("Millis  : " + String( Timer::getTimeMillis()));
    Serial.println("Second  : " + String( Timer::getTimeSecond()));
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("Welcome to Timer class..."));
  Serial.println(F("rhalfcaacbay@gmail.com"));

  timer0.set(Timer::FOREVER, 1000, callback0);
  timer0.start();
}

void loop() {
  // put your main code here, to run repeatedly:
  timer0.run();
}