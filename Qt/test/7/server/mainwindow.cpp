#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
