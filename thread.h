#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include "aircondition.h"

class Thread : public QThread
{
public:
    Thread();

    void stop();

protected:
    void run();

private:
    volatile bool stopped;
};

#endif // THREAD_H
