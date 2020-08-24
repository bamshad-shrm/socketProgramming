#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mThread = new myThread(this);
    QObject::connect(mThread,SIGNAL(screenDisplay(QString)),this,SLOT(onNewServerMessage(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewServerMessage(QString newMsg) {
    ui->label->setText(newMsg);
}

void MainWindow::on_pushButton_clicked()
{
    //Started
    mThread->Stop = false;
    mThread->start();
}

void MainWindow::on_pushButton_2_clicked()
{
    //Stopped
    mThread->Stop = true;
}
