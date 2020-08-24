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

void MainWindow::on_startButton_clicked()
{
   serverProgrammingObject.serverStart();
   ui->infoLable->setText(serverProgrammingObject.infoLableText);
}

void MainWindow::on_stopButton_clicked()
{
    serverProgrammingObject.serverStop();
    ui->infoLable->setText(serverProgrammingObject.infoLableText);
}
