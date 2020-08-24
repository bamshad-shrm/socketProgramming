#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myprocess.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

myProcess theProcess;

private slots:
    void on_startButton_clicked();
    void onNumberChanged(int);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
