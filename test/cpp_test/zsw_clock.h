#ifndef ZSW_CLOCK_H
#define ZSW_CLOCK_H

#include <chrono>

namespace zsw{
  namespace common {
    class Clock {
      typedef std::chrono::high_resolution_clock::steady_clock::time_point TimePoint;
    public:
      Clock() {
        cur_time_ = start_time_ = std::chrono::high_resolution_clock::now();
      }
      int time() {
        TimePoint pre_time = cur_time_;
        cur_time_ = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(cur_time_ - pre_time).count();
      }
      int totalTime() {
        cur_time_ = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(cur_time_ - start_time_).count();
      }
    private:
      TimePoint start_time_;
      TimePoint cur_time_;
    };
  }
}

#endif /* ZSW_CLOCK_H */