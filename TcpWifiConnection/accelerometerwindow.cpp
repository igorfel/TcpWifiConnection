#include "accelerometerwindow.h"
#include "ui_accelerometerwindow.h"

accelerometerWindow::accelerometerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accelerometerWindow)
{
    ui->setupUi(this);
    timeT = 0;
    //this->props.setWindow(this);
    props.setCentralWidget(ui->widget);
    this->plot = new PlotHandler::plot<double>(1,1,props);

    accelHandler = new accelerometerHandler(this);
    QTimer::singleShot(0, this, SLOT(startUpdate()));
}

accelerometerWindow::~accelerometerWindow()
{
    delete ui;
}

void accelerometerWindow::startUpdate()
{

    QTimer *timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer->start();
}

void accelerometerWindow::Update()
{
    timeT++;

    LinAlg::Matrix<double> newValue = this->accelHandler->getXFiltered();
    this->AccelX = this->AccelX | newValue;

    LinAlg::Matrix<double> newTimeValue = timeT;
    this->time = this->time | newTimeValue;

    ui->widget->hide();
    //this->plot = new PlotHandler::plot<double>(this->time, this->AccelX, props);
    this->plot->realTimeDataUpdate(timeT, this->accelHandler->getP() /*this->accelHandler->getXFiltered()*/);
    ui->widget->show();
}
