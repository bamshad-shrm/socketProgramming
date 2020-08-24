#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
        newEvent() signal is called by either newConnection() or disconnected() signals from serverprogramming.cpp.
        Because we can NOT include mainwindow.h in serverprogramming.h we must make the newEvent signal and connect it to disconnect() and newConnection()
        and then connect the newEvent() SIGNAL to eventPrint()  SLOT.
        If we could include mainwindow.h in serverprogramming.h we would directly connect disconnect() and newConnection() to eventPrint().
    */

    connect(&serverProgrammingObject,SIGNAL(newEvent()),this,SLOT(eventPrint()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    serverProgrammingObject.serverPort = ui->portlineEdit->text().toUShort();
    serverProgrammingObject.serverStart();
    ui->infoLable->setText(serverProgrammingObject.infoLableText);
}

void MainWindow::on_stopButton_clicked()
{
    serverProgrammingObject.serverStop();
    ui->infoLable->setText(serverProgrammingObject.infoLableText);
}

void MainWindow::eventPrint() {
    ui->infoLable->setText(serverProgrammingObject.infoLableText);
}
