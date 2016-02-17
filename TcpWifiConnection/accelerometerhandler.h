#ifndef ACCELEROMETERHANDLER_H
#define ACCELEROMETERHANDLER_H

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
    double getV(){return V;}
    double getP(){return P;}

    accelerometerHandler(QObject* parent = 0);

//signals:
private slots:
    void stopSampleData();

    // Override of QAcclerometerFilter::filter(QAccelerometerReading*)
    bool filter(QAccelerometerReading* reading);

private:
QAccelerometer* m_sensor;
qreal x,y,z;
double timeT, xFiltered;
double V, P, xAnt;
bool getDataFlag;
void filter2();
void accel2Vel();
void vel2Pos();

LinAlg::Matrix<double> dataFilterEst(LinAlg::Matrix<double> Y);
public:
double dataFilter(LinAlg::Matrix<double> &filterVet, double accelData, LinAlg::Matrix<double> coef);
LinAlg::Matrix<double> AccelX, AccelY, AccelZ, filterXCoef, filterYCoef, filterZCoef, filterXVet, filterYVet, filterZVet;

};

#endif // ACCELEROMETERHANDLER_H
