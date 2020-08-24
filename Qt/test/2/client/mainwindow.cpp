#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTcpSocket>

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

void MainWindow::on_connectBtn_clicked()
{
    QTcpSocket mySocket;
    mySocket.connectToHost("127.0.0.1",3000);
}

