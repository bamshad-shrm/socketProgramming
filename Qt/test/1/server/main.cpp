#include <QCoreApplication>

#include <QTcpSocket>
#include <QDebug>
#include <QTcpServer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpServer myServer;

    myServer.listen(QHostAddress::Any,3000);

    myServer.waitForNewConnection(10000);

    QTcpSocket *clientSocket = myServer.nextPendingConnection();

    clientSocket->write("A message from the Qt server");

    clientSocket->waitForBytesWritten(1000);
    clientSocket->waitForReadyRead(3000);
    qDebug() << "Reading: " << clientSocket->bytesAvailable();

    qDebug() << clientSocket->readAll();

    clientSocket->close();

    return a.exec();
}
