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

    QString queueClientIp;
    QString queueClientPort;

    bool myServerClosed = true;
    bool weHaveAClient = false;

    QTcpServer *myServer;
    QTcpSocket *clientSocket;
    QTcpSocket *queueClientSocket;

    quint16 serverPort;

    int clientSocketState;

    QString clientSocketDescriptor;

    QString queueClientSocketDescriptor;

    QString clientSocketError;

    qint64 writeReturnValue;

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
