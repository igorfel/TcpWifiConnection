#ifndef COMMANDS_H
#define COMMANDS_H

#include <QDialog>
#include <client.h>
#include <QThread>
#include <QSlider>

namespace Ui {
class Commands;
}

class Commands : public QDialog
{
    Q_OBJECT

public:
    void setClient(Client *c);
    explicit Commands(QWidget *parent = 0);
    ~Commands();

    static void msleep(unsigned long msecs){QThread::msleep(msecs);}

private:
    Ui::Commands *ui;
    QTimer *t;
    Client *c;
    float sendDelay=10;
    int pwm1,pwm2,pwm3,pwm4, lastPWM1,lastPWM2,lastPWM3,lastPWM4,
        lastSliderVal1 = 0,lastSliderVal2 = 0,lastSliderVal3 = 0,lastSliderVal4 = 0;
    bool midPWM, isFixed = false;
    void checkSlidersLim();
    void attLastValues();

private slots:
    void sendData(QString s);
    void on_addPwm1_clicked();
    void on_subPwm1_clicked();
    void on_subPwm2_clicked();
    void on_subPwm3_clicked();
    void on_addPwm2_clicked();
    void on_addPwm3_clicked();
    void on_subPwm4_clicked();
    void on_addPwm4_clicked();
    void displayReceivedData();
    void on_sendData_clicked();
    void on_fixValues_clicked();
    void on_pwm1Value_sliderReleased();
    void on_pwm2Value_sliderReleased();
    void on_pwm3Value_sliderReleased();
    void on_pwm4Value_sliderReleased();
    void on_pwm1Value_sliderMoved(int position);
    void on_pwm2Value_sliderMoved(int position);
    void on_pwm3Value_sliderMoved(int position);
    void on_pwm4Value_sliderMoved(int position);

};

#endif // COMMANDS_H
