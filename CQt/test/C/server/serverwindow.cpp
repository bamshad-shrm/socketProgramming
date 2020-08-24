#include "serverwindow.h"
#include "ui_serverwindow.h"

serverWindow::serverWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::serverWindow)
{
    ui->setupUi(this);
}

serverWindow::~serverWindow()
{
    delete ui;
}
