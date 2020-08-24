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


    QString infoLableText;
    QString clientIp;
    QString clientPort;

    bool myServerClosed;
    bool myServerStarted;
    bool weHaveAClient;

    QTcpServer *myServer;
    QTcpSocket *clientSocket;

    quint16 serverPort;

signals:

    void newEvent();

public slots:

    void serverStart();
    void aConnectionArrived();
    void connectionState();
    void aConnectionLeft();
    void serverStop();

};

#endif // SERVERPROGRAMMING_H
