#include "accelerometerwindow.h"
#include "ui_accelerometerwindow.h"

accelerometerWindow::accelerometerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accelerometerWindow)
{
    ui->setupUi(this);
    timeT = 0;
    this->_filter = new Filter<double>();

    this->averageX = 0;
    this->averageY = 0;
    this->averageZ = 0;

//    this->AccelX = LinAlg::Ones<double>(1000, 1);
//    this->AccelY = LinAlg::Ones<double>(1000, 1);
//    this->AccelZ = LinAlg::Ones<double>(1000, 1);

    //this->props.setWindow(this);
    props.setCentralWidget(ui->widget);
    this->plotX = new PlotHandler::plot<double>(1,1,props);

    props.setCentralWidget(ui->widget_2);
    this->plotY = new PlotHandler::plot<double>(1,1,props);

    props.setCentralWidget(ui->widget_3);
    this->plotZ = new PlotHandler::plot<double>(1,1,props);

    accelHandler = new accelerometerHandler(this);
    QTimer::singleShot(0, this, SLOT(startUpdate()));
}

accelerometerWindow::~accelerometerWindow()
{
    delete ui;
}

void accelerometerWindow::setClient(Client *c)
{
    this->c = c;
    connect(this->c, SIGNAL(hasReadData()), this, SLOT(Update()));
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
    //readFromExtDevice();
    readFromDevice();
}

void accelerometerWindow::readFromDevice () {
    timeT++;

    int dim = 100;
    if(this->AccelX.getNumberOfRows() > dim-2) {
        for(int i=1; i <= dim; ++i){
            this->AccelX(i, 1) = this->AccelX(i+1, 1);
            averageX+=this->AccelX(i,1);
            if(i == dim-1)
                averageX /= dim-1;

            this->AccelY(i, 1) = this->AccelY(i+1, 1);
            averageY+=this->AccelY(i,1);
            if(i == dim-1)
                averageY /= dim-1;

            this->AccelZ(i, 1) = this->AccelZ(i+1, 1);
            averageZ+=this->AccelZ(i,1);
            if(i == dim-1)
                averageZ /= dim-1;

            this->timeM(i, 1) = this->timeM(i+1, 1);
        }

        this->AccelX(dim,1) -= this->averageX;
        this->AccelY(dim,1) -= this->averageY;
        this->AccelZ(dim,1) -= this->averageZ;


        this->timeM(dim,1) = timeT;

        this->AccelX(dim,1) = this->accelHandler->getX();
        this->AccelY(dim,1) = this->accelHandler->getY();
        this->AccelZ(dim,1) = this->accelHandler->getZ();
    } else {

        LinAlg::Matrix<double> newTimeValue = timeT;
        this->timeM = this->timeM | newTimeValue;

        //Acumulando valores
        LinAlg::Matrix<double> newValueX = this->accelHandler->getX();
        this->AccelX = this->AccelX | newValueX;

        LinAlg::Matrix<double> newValueY = this->accelHandler->getY();
        this->AccelY = this->AccelY | newValueY;

        LinAlg::Matrix<double> newValueZ = this->accelHandler->getZ();
        this->AccelZ = this->AccelZ | newValueZ;
}

    //Aplicar media somente no ultimo dado recebido
    ui->widget->hide();
    this->plotX->generalPlot(timeM, this->AccelX);
    ui->widget->show();

    ui->widget_2->hide();
    this->plotY->generalPlot(timeM, this->AccelY);
    ui->widget_2->show();

    ui->widget_3->hide();
    this->plotZ->generalPlot(timeM, this->AccelZ);
    ui->widget_3->show();
}

void accelerometerWindow::readFromExtDevice () {
    timeT++;
    LinAlg::Matrix<double> newTimeValue = timeT;
    this->timeM = this->timeM | newTimeValue;

//Acumulando valores
    LinAlg::Matrix<double> newValueX = this->_filter->firstOrder(c->getSensorData()(1,1));
    this->AccelX = this->AccelX | newValueX;

    LinAlg::Matrix<double> newValueY = this->_filter->firstOrder(c->getSensorData()(2,1));
    this->AccelY = this->AccelY | newValueY;

    LinAlg::Matrix<double> newValueZ = this->_filter->firstOrder(c->getSensorData()(3,1));
    this->AccelZ = this->AccelZ | newValueZ;


    for(int i=1; i < 1000; ++i){
        this->AccelX(i, 1) = this->AccelX(i+1, 1);
        averageX+=this->AccelX(i,1);
        if(i == 999)
            averageX /= 999;

        this->AccelY(i, 1) = this->AccelY(i+1, 1);
        averageY+=this->AccelY(i,1);
        if(i == 999)
            averageY /= 999;

        this->AccelZ(i, 1) = this->AccelZ(i+1, 1);
        averageZ+=this->AccelZ(i,1);
        if(i == 999)
            averageZ /= 999;
    }

//Lendo em tempo real
//    double posx = this->_filter->firstOrder(c->getSensorData()(1,1));
//    posx = this->_filter->accel2Vel(posx, 0.1);
//    posx = this->_filter->vel2Pos(posx, 0.1);

//    double posy = this->_filter->firstOrder(c->getSensorData()(2,1));
//    posy = this->_filter->accel2Vel(posy, 0.1);
//    posy = this->_filter->vel2Pos(posy, 0.1);

//    double posz = this->_filter->firstOrder(c->getSensorData()(3,1));
//    posz = this->_filter->accel2Vel(posz, 0.1);
//    posz = this->_filter->vel2Pos(posz, 0.1);

    ui->widget->hide();
    this->plotX->generalPlot(timeM, this->AccelX - this->averageX);
    ui->widget->show();

    ui->widget_2->hide();
    this->plotY->generalPlot(timeM, this->AccelY - this->averageY);
    ui->widget_2->show();

    ui->widget_3->hide();
    this->plotZ->generalPlot(timeM, this->AccelZ - this->averageZ);
    ui->widget_3->show();
}
