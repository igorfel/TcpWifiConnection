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
    PlotHandler::plot<double> *plot;
    accelerometerHandler *accelHandler;
    PlotHandler::plotProperties props;

private slots:
    void Update();
};

#endif // ACCELEROMETERWINDOW_H
