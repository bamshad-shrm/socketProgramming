#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>

#include <unistd.h> // For close().

namespace Ui {
class server;
}

class server : public QMainWindow
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = nullptr);
    ~server();

private:
    Ui::server *ui;
};

#endif // SERVER_H
