#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QString>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString text;
    int socketState;
    QString socketStateMessage;
    QString connectionState(int);
    QString clientIp;
    QString clientPort;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void newConnectionArrived();

    void theConnectionIsDisconnected();

private:
    Ui::MainWindow *ui;
    QTcpServer *myServer;
    QTcpSocket *clientSocket;

};

#endif // MAINWINDOW_H
