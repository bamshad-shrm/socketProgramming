#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QThread>

namespace Ui {
class server;
}

class server : public QMainWindow
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = nullptr);
    ~server();

public:
    Ui::server *ui;
};

class thread: public QThread {
    void run();
};

#endif // SERVER_H
