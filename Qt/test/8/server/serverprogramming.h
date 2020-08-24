#ifndef SERVERPROGRAMMING_H
#define SERVERPROGRAMMING_H

#include <QMainWindow>
#include <QObject>

class serverProgramming : public QMainWindow
{
    Q_OBJECT
public:
    explicit serverProgramming(QWidget *parent = nullptr);

signals:

public slots:
    void serverStart();
};

#endif // SERVERPROGRAMMING_H
