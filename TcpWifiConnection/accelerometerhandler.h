#ifndef ACCELEROMETERHANDLER_H
#define ACCELEROMETERHANDLER_H

#include <filter.h>
#include <QAccelerometer>
#include <SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h>
//#include <QGeoPositionInfo>
//#include <QGeoPositionInfoSource>
//#include <QGeoSatelliteInfoSource>

//QTM_USE_NAMESPACE

class accelerometerHandler : public QObject, QAccelerometerFilter
{
    Q_OBJECT
public:
    qreal getX(){return x;}
    qreal getY(){return y;}
    qreal getZ(){return z;}
    double getXFiltered(){return xFiltered;}
    double getYFiltered(){return yFiltered;}
    double getZFiltered(){return zFiltered;}

    double getVx(){return Vx;}
    double getVy(){return Vy;}
    double getVz(){return Vz;}

    double getPx(){return Px;}
    double getPy(){return Py;}
    double getPz(){return Pz;}

    accelerometerHandler(QObject* parent = 0);

//signals:
private slots:
    //void stopSampleData();

    // Override of QAcclerometerFilter::filter(QAccelerometerReading*)
    bool filter(QAccelerometerReading* reading);

private:
QAccelerometer* m_sensor;
qreal x,y,z;
double timeT, xFiltered, yFiltered, zFiltered;
double Vx,Vy,Vz, Px,Py,Pz;
bool getDataFlag;
Filter<double> *_filter;
//void filter2();
//void accel2Vel();
//void vel2Pos();


LinAlg::Matrix<double> dataFilterEst(LinAlg::Matrix<double> Y);
public:
double dataFilter(LinAlg::Matrix<double> &filterVet, double accelData, LinAlg::Matrix<double> coef);
LinAlg::Matrix<double> AccelX, AccelY, AccelZ, filterXCoef, filterYCoef, filterZCoef, filterXVet, filterYVet, filterZVet;


};

#endif // ACCELEROMETERHANDLER_H
