#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <accelerometerwindow.h>
#include <commands.h>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QStringList>
#include <QHostInfo>
#include <QTimer>
#include <client.h>

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
    Commands *cmdWindow;
    void generatePlot();

private slots:
    void connect2Server();
    void onConnected();
    void readData();
    void showAccelWindow();
    void showCmdWindow();

};

#endif // MAINWINDOW_H
