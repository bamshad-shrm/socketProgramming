#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serverprogramming.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    serverProgramming serverProgrammingObject;

    Ui::MainWindow *ui;

private slots:
    void on_startButton_clicked();

private:

};

#endif // MAINWINDOW_H
