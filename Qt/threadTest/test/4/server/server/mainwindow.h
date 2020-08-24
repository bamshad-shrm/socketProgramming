#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serverclass.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    serverClass serverClassObject;

private slots:
    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
