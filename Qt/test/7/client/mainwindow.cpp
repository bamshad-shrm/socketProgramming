#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
