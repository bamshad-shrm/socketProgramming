#ifndef MYPROCESS_H
#define MYPROCESS_H


#include <QObject>
#include <QThread>
#include <QDebug>

class myProcess
{
public:
    myProcess();

    QString firstProcessLableText;

public slots:
    void processRun();
};

#endif // MYPROCESS_H
