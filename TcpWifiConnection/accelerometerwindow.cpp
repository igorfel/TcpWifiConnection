#include "accelerometerwindow.h"
#include "ui_accelerometerwindow.h"

accelerometerWindow::accelerometerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accelerometerWindow)
{
    ui->setupUi(this);

    this->props.setCentralWidget(ui->widget);
    //this->props.setWindow(this);
    this->plot = new PlotHandler::plot<double>(1,1,props);


    //Contador para função update (identifica a orientação do dispositivo)
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer->start(100);
}

accelerometerWindow::~accelerometerWindow()
{
    delete ui;
}

void accelerometerWindow::Update()
{
    ui->widget->hide();
    this->plot->realTimeDataUpdate((double)accelHandler->getX(), (double)accelHandler->getY());
    ui->widget->show();
}
