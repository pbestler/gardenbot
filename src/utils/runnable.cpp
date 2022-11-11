/**
 * @file runnable.cpp
 * @brief Definition of runnable
 *
 * @copyright Copyright(c) 2022 Peter Bestler
 */
#include "runnable.h"

void RunnableContainer::run()
{
    for (auto& runnable: _runnables)
    {
        runnable->run();
    }
}

void RunnableContainer::add(Runnable& runnable)
{
    _runnables.emplace_back(&runnable);
}