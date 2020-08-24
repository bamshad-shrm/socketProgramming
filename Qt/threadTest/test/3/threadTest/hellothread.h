#ifndef HELLOTHREAD_H
#define HELLOTHREAD_H

#include <QThread>
#include <QDebug>

class hellothread : public QThread
{
    Q_OBJECT
public:

    hellothread();

QThread *processThread;


private:
    void run();

};

#endif // HELLOTHREAD_H
