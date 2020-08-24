#ifndef SERVERPROGRAMMING_H
#define SERVERPROGRAMMING_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class serverProgramming : public QObject
{
    Q_OBJECT
public:
    explicit serverProgramming(QObject *parent = nullptr);

signals:

public slots:
    void serverStart();
};

#endif // SERVERPROGRAMMING_H
