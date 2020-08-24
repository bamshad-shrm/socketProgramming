#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <serverprogramming.h>

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

private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void eventPrint();
    void on_actionChat_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
