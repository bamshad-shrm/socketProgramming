#ifndef SERVERPROGRAMMING_H
#define SERVERPROGRAMMING_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "clientsocketclass.h"

class serverProgramming : public QTcpServer
{
    Q_OBJECT
public:
    explicit serverProgramming(QObject *parent = nullptr);
    QString infoLableText;
    QString chatLableText;
    bool myServerClosed = true;
    quint16 serverPort;
    QVector<clientSocketClass *> m_clients;

public slots:
    void serverStart();
    void serverStop();
    void aConnectionLeft(QTcpSocket *);
    void echo(char Array[99]);

protected:
    void incomingConnection(qintptr socketDescriptor);

signals:
    void newEvent();

};

#endif // SERVERPROGRAMMING_H
