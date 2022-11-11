/**
 * @file stopwatch.cpp
 * @author Peter Bester (peter.bestler@gmail.com)
 *
 * @brief Impementaiton of a smple stopwatch, which can be started and
 *        stopped multiple times.
 *
 *        It basically gets the current time on each start and stop press
 *        and stores it internally.
 *
 * @copyright Copyright (c) 2022 by Peter Bestler
 *
 */
#include "stopwatch.h"
#include <chrono>

/**
 * @brief Construct a new Stop Watch:: Stop Watch object
 */
StopWatch::StopWatch():
    _startTime(std::chrono::steady_clock::time_point::min())
{
    if (timeSync.isSynced() == false)
    {
        timeSync.begin();

        //Wait for connection
        timeSync.waitForSyncResult(5000);
    }


    if (timeSync.isSynced())
    {
        time_t now = time(nullptr);
        Serial.print(PSTR("Current time in Berlin: "));
        Serial.print(asctime(localtime(&now)));

    }
    else
    {
        Serial.println("Timeout while receiving the time");
    }

}

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
        return std::chrono::seconds(0);
    }

    auto endTime = std::chrono::steady_clock::now();

    this->_elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - this->_startTime);
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
    this->_elapsedTime = std::chrono::steady_clock::time_point::max();
}

 /* Getter for the elapsed Time
 *
 * @return elapsed time.
 */
const std::chrono::seconds StopWatch::getElapsedTime()
{

    std::chrono::seconds current_elapsed = std::chrono::seconds::min();
    if (this->_startTime != std::chrono::steady_clock::time_point::min())
    {
        auto currentTime = std::chrono::steady_clock::now();
        current_elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - this->_startTime);
        return (this->_elapsedTime + current_elapsed);
    }

   return this->_elapsedTime;
}