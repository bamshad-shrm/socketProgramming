#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientprogramming.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    clientProgramming clientProgrammingObject;

private slots:
    void on_connectButton_clicked();

    void on_disconnectButton_clicked();

    void eventPrint();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
