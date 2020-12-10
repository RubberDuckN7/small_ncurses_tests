#pragma once

#include <chrono>
#include <ratio>

#define TIME std::chrono::system_clock::now();

using namespace std;
using namespace chrono_literals;

using seconds      = std::chrono::duration<double>;
using milliseconds = std::chrono::duration<double, std::ratio_multiply<seconds::period, std::milli>>;
using microseconds = std::chrono::duration<double, std::ratio_multiply<seconds::period, std::micro>>;

class Timer
{
public:
  Timer() {}

  long long getTotalTimeMilliSec();
  float getDeltaTime();
  void init();
  void tick();
  void endFrame();

private:
  std::chrono::system_clock::time_point currentTime;
  std::chrono::system_clock::time_point lastTime;
};