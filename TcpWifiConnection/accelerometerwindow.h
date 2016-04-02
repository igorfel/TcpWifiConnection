#ifndef ACCELEROMETERWINDOW_H
#define ACCELEROMETERWINDOW_H

#include <QDialog>
#include <accelerometerhandler.h>
#include <SistemasdeControle/headers/graphicLibs/plot.h>
#include <client.h>
#include <filter.h>

namespace Ui {
class accelerometerWindow;
}

class accelerometerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit accelerometerWindow(QWidget *parent = 0);
    ~accelerometerWindow();
    void setClient(Client *c);

private:
    Client *c;
    Ui::accelerometerWindow *ui;
    accelerometerHandler *accelHandler;
    PlotHandler::plot<double> *plotX, *plotY, *plotZ;
    PlotHandler::plotProperties props;
    double timeT, averageX, averageY, averageZ;
    Filter<double> *_filter;
    LinAlg::Matrix<double> AccelX, AccelY, AccelZ, timeM;

    //void displayReceivedData();
    void readFromDevice();
    void readFromExtDevice();

private slots:
    void Update();
    void startUpdate();
};

#endif // ACCELEROMETERWINDOW_H
