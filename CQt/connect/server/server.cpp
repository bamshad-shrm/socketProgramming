#include "server.h"
#include "ui_server.h"
#include "bamsocket.h"
#include <QThread>

extern int serverFd, clientFd, portNumber=3001, backlogValue=5;
extern QString lableText, serverFdString, portNumberString;


server::server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);
    ui->displayLbl->setText(lableText);
}

class MyThread : public QThread
{
public:
    void run();
};

void MyThread::run()
{
    serverFd = bamSock();

    if (serverFd <= 0) {
        lableText.append("socket() Error.\n");
        //ui->displayLbl->setText(lableText);
    }
    else {
        lableText.append("\nThe Server with following info is created.\n");
        serverFdString = QString::number(serverFd);
        lableText.append("File descriptor: ");
        lableText.append(serverFdString);
        lableText.append("\n");
        //ui->displayLbl->setText(lableText);
    }

    int bindRtv = bamBind(serverFd,portNumber);

    if (bindRtv != 1) {
        lableText.append("bind() Error.\n");
        //ui->displayLbl->setText(lableText);
    }
    else {
        portNumberString = QString::number(portNumber);
        lableText.append("Port number: ");
        lableText.append(portNumberString);
        lableText.append("\n");
        lableText.append("IP address: ");
        lableText.append("127.0.0.1");
        lableText.append("\n");
        //ui->displayLbl->setText(lableText);
    }

    int listenRtv = bamListen(serverFd,backlogValue);

    if (listenRtv != 1) {
        lableText.append("listen() Error.\n");
        //ui->displayLbl->setText(lableText);
    }
    else {
        lableText.append("\nWe are waiting for connections ...\n");
    }

    /*int clientFd = bamAccept(serverFd);

    if (clientFd == -1) {
        lableText.append("accept() Error.\n");
        ui->displayLbl->setText(lableText);
    }
    else {
        lableText.append("\nA new connection arrived\n");
    }*/

    bamClose(serverFd);
    lableText.append("\nThe server with following info is closed.\n");
    lableText.append("File descriptor: ");
    lableText.append(serverFdString);
    lableText.append("\n");
    lableText.append("Port number: ");
    lableText.append(portNumberString);
    lableText.append("\n");
    lableText.append("IP address: ");
    lableText.append("127.0.0.1");
    lableText.append("\n");

    //ui->displayLbl->setText(lableText);
}


server::~server()
{
    delete ui;
}


void server::on_startBtn_clicked()
{




}

void server::on_stopBtn_clicked()
{


}
