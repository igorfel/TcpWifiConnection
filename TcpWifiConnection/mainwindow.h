#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <client.h>
#include <accelerometerwindow.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Client *c;
    accelerometerWindow *AccelWindow;

private slots:
    void connect2Server();
    void sendData();
    void readData();
    void showAccelWindow();
};

#endif // MAINWINDOW_H
