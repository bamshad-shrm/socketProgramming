#ifndef CLIENTSOCKETCLASS_H
#define CLIENTSOCKETCLASS_H

#include <QObject>
#include <QTcpSocket>

class clientSocketClass : public QObject
{
    Q_OBJECT
public:
    explicit clientSocketClass(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    void sendData(char Array[99]);
    char readData[99];
    QTcpSocket *m_serverSocket;

private slots:
    void receiveDataSlot();
    void disconnectedSlot();

signals:
    void iGotData(char Array[99]);
    void iAmDisconnected(QTcpSocket *);
};

#endif // CLIENTSOCKETCLASS_H
