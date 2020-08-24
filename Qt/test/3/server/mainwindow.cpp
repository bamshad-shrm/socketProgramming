#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::connectionState(int socketStateInt) {
    QString returnMsg;
    if (socketStateInt == 0) {
        returnMsg = "\n Connection state: The socket is not connected.";
    }
    if (socketStateInt == 1) {
        returnMsg = "\n Connection state: The socket is performing a host name lookup.";
    }
    if (socketStateInt == 2) {
        returnMsg = "\n Connection state: The socket has started establishing a connection.";
    }
    if (socketStateInt == 3) {
        returnMsg = "\n Connection state: A connection is established.";
    }
    if (socketStateInt == 4) {
        returnMsg = "\n Connection state: The socket is bound to an address and port.";
    }
    if (socketStateInt == 6) {
        returnMsg = "\n Connection state: The socket is about to close (data may still be waiting to be written).";
    }
    return returnMsg;
}

void MainWindow::newConnectionArrived() {
    clientSocket = myServer->nextPendingConnection();
    text.append("\n I got a new connectoin from IP: ");
    clientIp = clientSocket->peerAddress().toString();
    text.append(clientIp);
    text.append(" port: ");
    clientPort = QString::number(clientSocket->peerPort());
    text.append(clientPort);
    ui->label->setText(text);
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(theConnectionIsDisconnected()));
    /*socketState = clientSocket->state();
    socketStateMessage = connectionState(socketState);
    text.append(socketStateMessage);
    ui->label->setText(text);*/
}

void MainWindow::theConnectionIsDisconnected() {
    text.append("\n I lost a connection from: ");
    ui->label->setText(text);
    text.append(clientIp);
    text.append(" port: ");
    text.append(clientPort);
    ui->label->setText(text);
    /*socketState = clientSocket->state();
    socketStateMessage = connectionState(socketState);
    text.append(socketStateMessage);
    ui->label->setText(text);*/
}

void MainWindow::on_pushButton_clicked()
{
    myServer = new QTcpServer(this);
    myServer->listen(QHostAddress::Any,3000);
    if (myServer->isListening()){
        text.append("\n The server is listening for a new connection ...");
        ui->label->setText(text);
    }
    else {
        text.append("\n Listen() error");
        ui->label->setText(text);
    }
    connect(myServer, SIGNAL(newConnection()), this, SLOT(newConnectionArrived()));
}

void MainWindow::on_pushButton_2_clicked()
{
    myServer->close();
    text.append("\n The server is stopped.");
    ui->label->setText(text);
}


