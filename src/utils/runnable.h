#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <vector>

class Runnable
{
    public:
        virtual void run(void) = 0;
};

class RunnableContainer: public Runnable
{
    public:
        void run(void) override;
        void add(Runnable& runnable);

    private:
        std::vector<Runnable*> _runnables;
};

#endif
