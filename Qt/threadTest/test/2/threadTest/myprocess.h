#ifndef MYPROCESS_H
#define MYPROCESS_H

#include <QThread>

class myProcess : public QThread
{

    Q_OBJECT

public:
    myProcess();
    void run();
    int number;

signals:
    void numberChanged(int);
};

#endif // MYPROCESS_H
