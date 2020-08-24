#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
        newEvent() signal is called by disconnected() signal from clientprogramming.cpp.
        Because we can NOT include mainwindow.h in clientprogramming.h we must make the newEvent signal and connect it to disconnect()
        and then connect the newEvent() SIGNAL to eventPrint()  SLOT.
        If we could include mainwindow.h in clientprogramming.h we would directly connect disconnect() to eventPrint().
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
    clientProgrammingObject.myConnect();
    ui->infoLable->setText(clientProgrammingObject.infoLableText);
}

void MainWindow::on_disconnectButton_clicked()
{
    clientProgrammingObject.myDisconnect();
    ui->infoLable->setText(clientProgrammingObject.infoLableText);
}

void MainWindow::eventPrint() {
    ui->infoLable->setText(clientProgrammingObject.infoLableText);
}
