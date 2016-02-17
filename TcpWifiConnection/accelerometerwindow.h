#ifndef ACCELEROMETERWINDOW_H
#define ACCELEROMETERWINDOW_H

#include <QDialog>
#include <accelerometerhandler.h>
#include <SistemasdeControle/headers/graphicLibs/plot.h>

namespace Ui {
class accelerometerWindow;
}

class accelerometerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit accelerometerWindow(QWidget *parent = 0);
    ~accelerometerWindow();

private:
    Ui::accelerometerWindow *ui;
    accelerometerHandler *accelHandler;
    PlotHandler::plot<double> *plot;
    PlotHandler::plotProperties props;
    double timeT;

    LinAlg::Matrix<double> AccelX, AccelY, AccelZ, time;

private slots:
    void Update();
    void startUpdate();
};

#endif // ACCELEROMETERWINDOW_H
