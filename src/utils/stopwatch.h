/**
 * @file stopwatch.h
 * @brief Declaration of stop watch.
 *
 * @copyright Copyright (c) 2022 Peter Bestler
 */
#ifndef _SRC_UTILS_STOPWATCH
#define _SRC_UTILS_STOPWATCH

#include "timeSync.h"
#include <chrono>

typedef std::chrono::time_point<std::chrono::steady_clock> steady_tp_t;

class StopWatch
{
private:
    /** Storage for the start time. */
    steady_tp_t _startTime;
    /** The total elapsed time */
    std::chrono::seconds _elapsedTime;

public:
    StopWatch(/* args */);
    ~StopWatch();
    void start();
    const std::chrono::seconds stop();
    void reset();
    const std::chrono::seconds getElapsedTime();
};

#endif /* _SRC_UTILS_STOPWATCH */
