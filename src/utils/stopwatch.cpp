/**
 * @file stopwatch.cpp
 *
 * @brief Impementaiton of a smple stopwatch, which can be started and
 *        stopped multiple times.
 *
 *        It basically gets the current time on each start and stop press
 *        and stores it internally.
 *
 * @copyright Copyright (c) 2022 by Peter Bestler
 */
#include "stopwatch.h"

#include <chrono>

/**
 * @brief Construct a new Stop Watch:: Stop Watch object
 */
StopWatch::StopWatch():
    _startTime(std::chrono::steady_clock::time_point::min()),
    _elapsedTime(std::chrono::seconds::zero())
{}

/**
 * @brief Destroy the Stop Watch:: Stop Watch object
 */
StopWatch::~StopWatch() {}

/**
 * @brief Start the stop watch.
 */
void StopWatch::start()
{

    /** We already started, first do a stop */
    if (this->_startTime != std::chrono::steady_clock::time_point::min())
    {
        return;
    }

    this->_startTime = std::chrono::steady_clock::now();
}

/**
 * @brief Stops the stop watch
 *
 * @return const std::time_t returns the accumulated elapsed time.
 */
const std::chrono::seconds StopWatch::stop()
{
    if (this->_startTime == std::chrono::steady_clock::time_point::min())
    {
        return std::chrono::seconds::zero();
    }

    auto endTime = std::chrono::steady_clock::now();

    this->_elapsedTime +=
        std::chrono::duration_cast<std::chrono::seconds>(
            endTime - this->_startTime);
    this->_startTime = std::chrono::steady_clock::time_point::min();

    return this->_elapsedTime;

}

/**
 * @brief Resets the stop watch, especially the
 *        elapsed time to '0'.
 */
void StopWatch::reset()
{
    this->_startTime = std::chrono::steady_clock::time_point::min();
    this->_elapsedTime = std::chrono::seconds::zero();
}

 /**
  * @brief Gettter of the eleapsed time.
  *
  * @return elapsed time.
  */
 const std::chrono::seconds StopWatch::getElapsedTime()
{

    if (this->_startTime != std::chrono::steady_clock::time_point::min())
    {
        auto currentTime = std::chrono::steady_clock::now();
        auto current_elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            currentTime - this->_startTime);
        return (this->_elapsedTime + current_elapsed);
    }

   return this->_elapsedTime;
}