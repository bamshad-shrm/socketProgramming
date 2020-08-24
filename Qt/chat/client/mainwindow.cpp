#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
        newEvent() signal is called by disconnected() and readyRead() signals from clientprogramming.cpp.
        Because we can NOT include mainwindow.h in clientprogramming.h we must make the newEvent signal and connect it to disconnect() and readyRead()
        and then connect the newEvent() SIGNAL to eventPrint()  SLOT.
        If we could include mainwindow.h in clientprogramming.h we would directly connect disconnect() and readyRead() to eventPrint().
    */
    connect(&clientProgrammingObject,SIGNAL(newEvent()),this,SLOT(eventPrint()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    clientProgrammingObject.serverIp = QHostAddress(ui->IPlineEdit->text());
    clientProgrammingObject.serverPort = ui->PortlineEdit->text().toUShort();
    clientProgrammingObject.userName = ui->userNamelineEdit->text();
    clientProgrammingObject.myConnect();
    ui->connectionLable->setText(clientProgrammingObject.connectionLableText);
}

void MainWindow::on_disconnectButton_clicked()
{
    clientProgrammingObject.myDisconnect();
    ui->connectionLable->setText(clientProgrammingObject.connectionLableText);
}

void MainWindow::on_sendButton_clicked()
{
    clientProgrammingObject.userMsg = ui->msgLineEdit->text();
    clientProgrammingObject.sendMsg();
    ui->chatLable->setText(clientProgrammingObject.chatLableText);
    ui->msgLineEdit->clear();
}

void MainWindow::eventPrint() {
    ui->chatLable->setText(clientProgrammingObject.chatLableText);
    ui->connectionLable->setText(clientProgrammingObject.connectionLableText);
}


void MainWindow::on_actionConnection_messages_triggered()
{
    if (ui->connectionScrollArea->isHidden()) {
        ui->connectionScrollArea->setVisible(true);
    }
    else {
        ui->connectionScrollArea->setVisible(false);
    }
}
