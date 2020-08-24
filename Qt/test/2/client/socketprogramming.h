#ifndef SOCKETPROGRAMMING_H
#define SOCKETPROGRAMMING_H

#include <QObject>
#include <QTcpSocket>

class socketProgramming : public QObject
{
    Q_OBJECT
public:
    explicit socketProgramming(QObject *parent = nullptr);

signals:

public slots:

private:
    void mySocket();
    void myConnect();
    void myClose();
};

#endif // SOCKETPROGRAMMING_H
