#include "serverclass.h"

serverClass::serverClass()
{

}

void serverClass::startServer() {
    quint16 port = 3000;

    if(!this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening to port " << port << "...";
    }
}


// This function is called by QTcpServer when a new connection is available.
void serverClass::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    qDebug() << socketDescriptor << " Connecting...";

    // Every new connection will be run in a newly created thread
    //MyThread *thread = new MyThread(socketDescriptor, this);

    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    //connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    //thread->start();
}
