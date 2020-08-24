#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    class MyThread : public QThread {
    public:
        void run();
    };

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
