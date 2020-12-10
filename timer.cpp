#include "timer.h"

float Timer::getDeltaTime()
{
  std::chrono::duration<float, std::milli> dt = currentTime - lastTime;
  return dt.count();
}

void Timer::init()
{ 
  currentTime = TIME
  lastTime = TIME 
}

void Timer::tick()
{
  lastTime = currentTime;
  currentTime = TIME
}