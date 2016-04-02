#include "accelerometerhandler.h"
#include <qtimer>
#include <time.h>

//void accelerometerHandler::positionUpdateTimeout()
//{
//    qDebug("positionUpdateTimeout() received");
//}

//void accelerometerHandler::positionUpdated(const QGeoPositionInfo& pos)
//{
//    m_latitude = pos.coordinate().latitude();
//    m_longitude = pos.coordinate().longitude();
//    m_altitude = pos.coordinate().altitude();
//    m_direction = QString::number(pos.attribute(QGeoPositionInfo::Direction));
//    m_groundSpeed = QString::number(pos.attribute(QGeoPositionInfo::GroundSpeed));
//    m_verticalSpeed = QString::number(pos.attribute(QGeoPositionInfo::VerticalSpeed));
//    m_horizontalAccuracy = QString::number(pos.attribute(QGeoPositionInfo::HorizontalAccuracy));
//    m_verticalAccuracy = QString::number(pos.attribute(QGeoPositionInfo::VerticalAccuracy));


//    qDebug("updated position long=%d, alt=%d, lat=%d", this->m_longitude, this->m_altitude, this->m_latitude);
//}

accelerometerHandler::accelerometerHandler(QObject* parent) : QObject(parent)
{
    this->_filter = new Filter<double>();

    m_sensor = new QAccelerometer(this);
    m_sensor->addFilter(this);
    m_sensor->connectToBackend();
    m_sensor->setAccelerationMode(QAccelerometer::AccelerationMode::Combined);
    m_sensor->setDataRate(1);
    m_sensor->start();

    getDataFlag = true;
    this->xFiltered = 0;

    this->filterXVet = LinAlg::Zeros<double> (1,3);
    this->filterYVet = LinAlg::Zeros<double> (1,3);
    this->filterZVet = LinAlg::Zeros<double> (1,3);

    //QTimer::singleShot(5000, this, SLOT(stopSampleData()));
}

//void accelerometerHandler::stopSampleData()
//{
//    getDataFlag = false;

//    this->filterXCoef = dataFilterEst(this->AccelX);
//}

bool accelerometerHandler::filter(QAccelerometerReading* reading)
{
    //srand(time(NULL));
    this->x = reading->x();
    this->y = reading->y();
    this->z = reading->z();

    this->xFiltered = this->_filter->firstOrder(this->x);
    this->yFiltered = this->_filter->firstOrder(this->y);
    this->zFiltered = this->_filter->firstOrder(this->z);

    this->Vx = this->_filter->accel2Vel(this->xFiltered, 0.1);
    this->Vy = this->_filter->accel2Vel(this->yFiltered, 0.1);
    this->Vz = this->_filter->accel2Vel(this->zFiltered, 0.1);

    this->Px = this->_filter->vel2Pos(this->Vx, 0.1);
    this->Px = this->_filter->vel2Pos(this->Vy, 0.1);
    this->Px = this->_filter->vel2Pos(this->Vz, 0.1);


    /*if(getDataFlag){
        this->AccelX = this->AccelX | this->x;
        this->AccelY = this->AccelY | this->y;
        this->AccelZ = this->AccelZ | this->z;
    }else{
        this->x = dataFilter(this->filterXVet, this->x, this->filterXCoef);
    }*/

            //qDebug("Current device acceleration: x=%f y=%f z=%f", x, y, z);
    return 1;
}

LinAlg::Matrix<double> accelerometerHandler::dataFilterEst(LinAlg::Matrix<double> y)
{
    LinAlg::Matrix<double> A, Y;

    for(unsigned i = 3; i < y.getNumberOfColumns(); ++i)  {
        Y = Y | 0;
        LinAlg::Matrix<double> vet(1,3);
        vet(1,1) = y(1,i);
        vet(1,2) = y(1,i-1);
        vet(1,3) = y(1,i-2);

        A = A||vet;
    }

    return (((~A)*A)^(-1))*(~A)*Y;
}

double accelerometerHandler::dataFilter(LinAlg::Matrix<double> &filterVet, double accelData, LinAlg::Matrix<double> coef){

    filterVet(1,3) = filterVet(1,2);
    filterVet(1,2) = filterVet(1,1);
    filterVet(1,1) = accelData;

//    this->filterYVet(1,3) = this->filterYVet(1,2);
//    this->filterYVet(1,2) = this->filterYVet(1,1);
//    this->filterYVet(1,1) = accelYData;

//    this->filterZVet(1,3) = this->filterZVet(1,2);
//    this->filterZVet(1,2) = this->filterZVet(1,1);
//    this->filterZVet(1,1) = accelZData;


    return (coef * filterVet)(1,1);
}

//void accelerometerHandler::filter2(){
//    this->xFiltered += (0.001/0.1)*(this->x - this->xFiltered);
//    this->yFiltered += (0.001/0.1)*(this->y - this->yFiltered);
//    this->zFiltered += (0.001/0.1)*(this->z - this->zFiltered);
//}

//void accelerometerHandler::accel2Vel(){
//    this->Vx += this->xFiltered/0.1;
//    this->Vy = this->yFiltered/0.1;
//    this->Vz = this->zFiltered/0.1;
//}

//void accelerometerHandler::vel2Pos (){
//    this->Px += this->Vx/0.1;
//    this->Py += this->Vy/0.1;
//    this->Pz += this->Vz/0.1;
//}
