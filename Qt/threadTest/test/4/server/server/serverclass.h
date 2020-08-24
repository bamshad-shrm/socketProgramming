#ifndef SERVERCLASS_H
#define SERVERCLASS_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>

class serverClass : public QTcpServer
{
public:
    serverClass();

    void startServer();

protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // SERVERCLASS_H
