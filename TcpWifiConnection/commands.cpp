#include "commands.h"
#include "ui_commands.h"

Commands::Commands(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Commands)
{
    ui->setupUi(this);
    //Client c = new Client();
    this->pwm1 = 0;
    this->pwm2 = 0;
    this->pwm3 = 0;
    this->pwm4 = 0;
    this->lastPWM1 = 0;
    this->lastPWM2 = 0;
    this->lastPWM3 = 0;
    this->lastPWM4 = 0;

    //on_fixValues_clicked();

    this->t = new QTimer(this);
    //connect(this->c, SIGNAL(hasReadData()), this, SLOT(displayReceivedData()));
}

Commands::~Commands()
{
    delete ui;
}

void Commands::setClient(Client *c)
{
    this->c = c;
    connect(this->c, SIGNAL(hasReadData()), this, SLOT(displayReceivedData()));
}

void Commands::sendData(QString s)
{
    this->c->write(s);
}

//void Commands::send1()
//{
////    if(this->midPWM && this->pwm >= 125)
////        this->t->stop();
////    if(this->pwm >= 250)
////        this->t->stop();

//    sendData("_1_");
//    this->pwm+=1;
//    ui->pwmData->setText(QString::number(pwm));
//}
//void Commands::send0()
//{
////    if(this->midPWM && this->pwm <= 135)
////        this->t->stop();
////    if(this->pwm <= 5)
////        this->t->stop();

//    sendData("_0_");
//    this->pwm-=1;
//    ui->pwmData->setText(QString::number(pwm));
//}

//void Commands::sendMaxPWM()
//{
//    this->midPWM = false;

//    connect(t, SIGNAL(timeout()), this, SLOT(send1()));
//    this->t->setInterval(this->sendDelay);
//    this->t->start();
//}
//void Commands::sendMidPWM()
//{
//    this->midPWM = true;

//    if(this->pwm > 130){
//        connect(t, SIGNAL(timeout()), this, SLOT(send0()));
//        this->t->setInterval(this->sendDelay);
//        this->t->start();
//    }else if(this->pwm < 130){
//        connect(t, SIGNAL(timeout()), this, SLOT(send1()));
//        this->t->setInterval(this->sendDelay);
//        this->t->start();
//    }
//}
//void Commands::sendMinPWM()
//{
//    this->midPWM = false;

//    connect(t, SIGNAL(timeout()), this, SLOT(send0()));
//    this->t->setInterval(this->sendDelay);
//    this->t->start();
//}

void Commands::on_pwm1Value_sliderReleased()
{
    int value = ui->pwm1Value->value();

    for(unsigned int i = this->lastPWM1; i>value; --i){
        //sendData("_0_");
        this->pwm1-=1;
        Commands::msleep(this->sendDelay);
    }

    for(unsigned int i = this->lastPWM1; i<value; ++i){
        //sendData("_1_");
        this->pwm1+=1;
        Commands::msleep(this->sendDelay);
    }

lastPWM1 = value;
ui->pwm1ValueLabel->setText(QString::number(this->pwm1));
}

void Commands::on_pwm2Value_sliderReleased()
{
    int value = ui->pwm2Value->value();

    for(unsigned int i = this->lastPWM2; i>value; --i){
        //sendData("_2_");
        this->pwm2-=1;
        Commands::msleep(this->sendDelay);
    }

    for(unsigned int i = this->lastPWM2; i<value; ++i){
        //sendData("_3_");
        this->pwm2+=1;
        Commands::msleep(this->sendDelay);
    }


lastPWM2 = value;
ui->pwm2ValueLabel->setText(QString::number(this->pwm2));
}

void Commands::on_pwm3Value_sliderReleased()
{
    int value = ui->pwm3Value->value();

    for(unsigned int i = this->lastPWM3; i>value; --i){
        //sendData("_4_");
        this->pwm3-=1;
        Commands::msleep(this->sendDelay);
    }

    for(unsigned int i = this->lastPWM3; i<value; ++i){
        //sendData("_5_");
        this->pwm3+=1;
        Commands::msleep(this->sendDelay);
    }

lastPWM3 = value;
ui->pwm3ValueLabel->setText(QString::number(this->pwm3));
}

void Commands::on_pwm4Value_sliderReleased()
{
    int value = ui->pwm4Value->value();

    for(unsigned int i = this->lastPWM4; i>value; --i){
        //sendData("_6_");
        this->pwm4-=1;
        Commands::msleep(this->sendDelay);
    }

    for(unsigned int i = this->lastPWM4; i<value; ++i){
        //sendData("_7_");
        this->pwm4+=1;
        Commands::msleep(this->sendDelay);
    }

lastPWM4 = value;
ui->pwm4ValueLabel->setText(QString::number(this->pwm4));
}

void Commands::on_pwm1Value_sliderMoved(int position)
{
    if(this->isFixed) {
        checkSlidersLim();

        int value = ui->pwm1Value->value()-this->lastSliderVal1;
        this->pwm4 += value;
        ui->pwm4Value->setValue(ui->pwm4Value->value()+value);
        this->pwm2 += value;
        ui->pwm2Value->setValue(ui->pwm2Value->value()+value);
        this->pwm3 += value;
        ui->pwm3Value->setValue(ui->pwm3Value->value()+value);

        attLastValues();
    }
}

void Commands::on_pwm2Value_sliderMoved(int position)
{
    if(this->isFixed) {
        checkSlidersLim();

        int value = ui->pwm2Value->value()-this->lastSliderVal2;
        this->pwm1 += value;
        ui->pwm1Value->setValue(ui->pwm1Value->value()+value);
        this->pwm4 += value;
        ui->pwm4Value->setValue(ui->pwm4Value->value()+value);
        this->pwm3 += value;
        ui->pwm3Value->setValue(ui->pwm3Value->value()+value);

        attLastValues();
    }
}

void Commands::on_pwm3Value_sliderMoved(int position)
{
    if(this->isFixed) {
        checkSlidersLim();

        int value = ui->pwm3Value->value()-this->lastSliderVal3;
        this->pwm1 += value;
        ui->pwm1Value->setValue(ui->pwm1Value->value()+value);
        this->pwm2 += value;
        ui->pwm2Value->setValue(ui->pwm2Value->value()+value);
        this->pwm4 += value;
        ui->pwm4Value->setValue(ui->pwm4Value->value()+value);

        attLastValues();
    }
}

void Commands::on_pwm4Value_sliderMoved(int position)
{
    if(this->isFixed) {
        checkSlidersLim();

        int value = ui->pwm4Value->value()-this->lastSliderVal4;
        this->pwm1 += value;
        ui->pwm1Value->setValue(ui->pwm1Value->value()+value);
        this->pwm2 += value;
        ui->pwm2Value->setValue(ui->pwm2Value->value()+value);
        this->pwm3 += value;
        ui->pwm3Value->setValue(ui->pwm3Value->value()+value);
        attLastValues();


    }
}

void Commands::checkSlidersLim() {
    int value1 = ui->pwm1Value->value(),value2 = ui->pwm2Value->value(),value3 = ui->pwm3Value->value(),value4 = ui->pwm4Value->value();

    if(ui->pwm1Value->value() > 257 || ui->pwm2Value->value() > 257 || ui->pwm3Value->value() > 257 || ui->pwm4Value->value() > 257) {
        int value = value1-1;
        ui->pwm1Value->setValue(value);
        value = value2-1;
        ui->pwm2Value->setValue(value);
        value = value3-1;
        ui->pwm3Value->setValue(value);
        value = value4-1;
        ui->pwm4Value->setValue(value);

    } else if(ui->pwm1Value->value() < 0 || ui->pwm2Value->value() < 0 || ui->pwm3Value->value() < 0 || ui->pwm4Value->value() < 0) {
        int value = value1+1;
        ui->pwm1Value->setValue(value);
        value = value2+1;
        ui->pwm2Value->setValue(value);
        value = value3+1;
        ui->pwm3Value->setValue(value);
        value = value4+1;
        ui->pwm4Value->setValue(value);
    }
}

void Commands::on_subPwm1_clicked()
{
    //sendData("_0_");
    this->pwm1-=1;
    ui->pwm1Value->setValue(this->pwm1);
    ui->pwm1ValueLabel->setText(QString::number(this->pwm1));
}

void Commands::on_addPwm1_clicked()
{
    //sendData("_1_");
    this->pwm1+=1;
    ui->pwm1Value->setValue(this->pwm1);
    ui->pwm1ValueLabel->setText(QString::number(this->pwm1));
}

void Commands::on_subPwm2_clicked()
{
    //sendData("_2_");
    this->pwm2-=1;
    ui->pwm2Value->setValue(this->pwm2);
    ui->pwm2ValueLabel->setText(QString::number(this->pwm2));
}

void Commands::on_addPwm2_clicked()
{
    //sendData("_3_");
    this->pwm2+=1;
    ui->pwm2Value->setValue(this->pwm2);
    ui->pwm2ValueLabel->setText(QString::number(this->pwm2));
}

void Commands::on_subPwm3_clicked()
{
    //sendData("_4_");
    this->pwm3-=1;
    ui->pwm3Value->setValue(this->pwm3);
    ui->pwm3ValueLabel->setText(QString::number(this->pwm3));
}

void Commands::on_addPwm3_clicked()
{
    //sendData("_5_");
    this->pwm3+=1;
    ui->pwm3Value->setValue(this->pwm3);
    ui->pwm3ValueLabel->setText(QString::number(this->pwm3));
}

void Commands::on_subPwm4_clicked()
{
    //sendData("_6_");
    this->pwm4-=1;
    ui->pwm4Value->setValue(this->pwm4);
    ui->pwm4ValueLabel->setText(QString::number(this->pwm4));
}

void Commands::on_addPwm4_clicked()
{
    //sendData("_7_");
    this->pwm4+=1;
    ui->pwm4Value->setValue(this->pwm4);
    ui->pwm4ValueLabel->setText(QString::number(this->pwm4));
}

void Commands::attLastValues() {
    this->lastSliderVal1 = ui->pwm1Value->value();
    this->lastSliderVal2 = ui->pwm2Value->value();
    this->lastSliderVal3 = ui->pwm3Value->value();
    this->lastSliderVal4 = ui->pwm4Value->value();

    this->pwm1 = ui->pwm1Value->value();
    this->pwm2 = ui->pwm2Value->value();
    this->pwm3 = ui->pwm3Value->value();
    this->pwm4 = ui->pwm4Value->value();

    ui->pwm1ValueLabel->setText(QString::number(this->pwm1));
    ui->pwm2ValueLabel->setText(QString::number(this->pwm2));
    ui->pwm3ValueLabel->setText(QString::number(this->pwm3));
    ui->pwm4ValueLabel->setText(QString::number(this->pwm4));
}

void Commands::on_fixValues_clicked()
{
    if(this->isFixed)
        this->isFixed = false;
    else{
        this->isFixed = true;
        attLastValues();
    }

    ui->addPwm1->setEnabled(!this->isFixed);
    ui->addPwm2->setEnabled(!this->isFixed);
    ui->addPwm3->setEnabled(!this->isFixed);
    ui->addPwm4->setEnabled(!this->isFixed);

    ui->subPwm1->setEnabled(!this->isFixed);
    ui->subPwm2->setEnabled(!this->isFixed);
    ui->subPwm3->setEnabled(!this->isFixed);
    ui->subPwm4->setEnabled(!this->isFixed);

    ui->fixValues->setText("Fixed: " + QString::number(this->isFixed));
}

void Commands::on_sendData_clicked()
{
    sendData(ui->data2Send->text());
}

void Commands::displayReceivedData()
{
    ui->sensorX->setText(QString::number(c->getSensorData()(1,1)));
    ui->sensorY->setText(QString::number(c->getSensorData()(2,1)));
    ui->sensorZ->setText(QString::number(c->getSensorData()(3,1)));
}
