#ifndef SERVERPROGRAMMING_H
#define SERVERPROGRAMMING_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMainWindow>

namespace Ui {
    class serverProgramming;
}


class serverProgramming : public QMainWindow
{
    Q_OBJECT
public:
    explicit serverProgramming(QObject *parent = nullptr);


    QString infoLableText;
    QString clientIp;
    QString clientPort;

private:
    QTcpServer *myServer;
    QTcpSocket *clientSocket;
    Ui::serverProgramming *ui;


signals:

public slots:
    void serverStart();
    void aConnectionArrived();
    void connectionState();
    void aConnectionLeft();
    void serverStop();
};

#endif // SERVERPROGRAMMING_H
