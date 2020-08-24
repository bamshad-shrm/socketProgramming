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
        returnMsg = "\n The socket is not connected.";
    }
    if (socketStateInt == 1) {
        returnMsg = "\n The socket is performing a host name lookup.";
    }
    if (socketStateInt == 2) {
        returnMsg = "\n The socket has started establishing a connection.";
    }
    if (socketStateInt == 3) {
        returnMsg = "\n A connection is established.";
    }
    if (socketStateInt == 4) {
        returnMsg = "\n The socket is bound to an address and port.";
    }
    if (socketStateInt == 6) {
        returnMsg = "\n The socket is about to close (data may still be waiting to be written).";
    }
    return returnMsg;
}

void MainWindow::on_pushButton_clicked()
{
    mySocket.connectToHost("127.0.0.1",3000);
    socketState = mySocket.state();
    socketStateMessage = connectionState(socketState);
    text.append(socketStateMessage);
    ui->label->setText(text);
    mySocket.waitForConnected(3000);
    socketState = mySocket.state();
    socketStateMessage = connectionState(socketState);
    text.append(socketStateMessage);
    ui->label->setText(text);
}

void MainWindow::on_pushButton_2_clicked()
{
    mySocket.disconnectFromHost();
    socketState = mySocket.state();
    socketStateMessage = connectionState(socketState);
    text.append(socketStateMessage);
    ui->label->setText(text);
}
