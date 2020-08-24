#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QtCore>

namespace Ui {
class serverWindow;
}

class serverWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit serverWindow(QWidget *parent = nullptr);
    ~serverWindow();

private:
    Ui::serverWindow *ui;
};

#endif // SERVERWINDOW_H
