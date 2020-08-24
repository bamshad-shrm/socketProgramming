#include <QCoreApplication>

#include <QTcpSocket>
#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const char *sendData = "A message from the Qt client.";

    QTcpSocket mySocket;

    mySocket.connectToHost("127.0.0.1",3000);

    mySocket.write(sendData);


    mySocket.waitForBytesWritten(1000);
    mySocket.waitForReadyRead(3000);
    qDebug() << "Reading: " << mySocket.bytesAvailable();

    qDebug() << mySocket.readAll();

    mySocket.close();

    return a.exec();
}
