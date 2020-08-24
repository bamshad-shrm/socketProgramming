#ifndef SERVERPROGRAMMING_H
#define SERVERPROGRAMMING_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

class serverProgramming : public QObject
{
    Q_OBJECT
public:
    explicit serverProgramming(QObject *parent = nullptr);

signals:

public slots:
    void aConnectionArrived();
    void aConnectionLeft();

private:
    QTcpServer *myServer;
    QTcpSocket *clientSocket;
};

#endif // SERVERPROGRAMMING_H
