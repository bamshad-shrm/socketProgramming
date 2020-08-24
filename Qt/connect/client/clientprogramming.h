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

    QString infoLableText;
    QHostAddress serverIp;
    quint16 serverPort;
    QString serverPortString;

    int socketState;

    bool disconnectButton;

    char readData[99];

    qint64 readReturnValue;



signals:

    void newEvent();

public slots:

    void myConnect();
    void myDisconnect();
    void serverClosed();

};

#endif // CLIENTPROGRAMMING_H
