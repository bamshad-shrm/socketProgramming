#ifndef CLIENTPROGRAMMING_H
#define CLIENTPROGRAMMING_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>


class clientProgramming : public QObject
{
    Q_OBJECT
public:
    explicit clientProgramming(QObject *parent = nullptr);

    QTcpSocket mySocket;

    QString chatLableText;
    QString connectionLableText;

    QHostAddress serverIp;
    quint16 serverPort;
    QString serverPortString;
    QString userName;

    int socketState;

    bool disconnectButton;

    QString userMsg;
    // sendMessage is combination of userName and userMsg.
    QString sendMessage;
    char readData[99];
    char wirteData[99];

    qint64 readReturnValue;



signals:

    void newEvent();

public slots:

    void myConnect();
    void myDisconnect();
    void serverClosed();
    void recieveMsg();
    void sendMsg();

};

#endif // CLIENTPROGRAMMING_H
