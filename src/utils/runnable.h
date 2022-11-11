#ifndef _SRC_UTILS_RUNNABLE
#define _SRC_UTILS_RUNNABLE

#include <vector>

class Runnable
{
    public:
        virtual ~Runnable() {};
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

#endif /* _SRC_UTILS_RUNNABLE */
