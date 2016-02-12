#ifndef ACCELEROMETERHANDLER_H
#define ACCELEROMETERHANDLER_H

#include <QAccelerometer>

//QTM_USE_NAMESPACE

class accelerometerHandler : public QObject, QAccelerometerFilter
{
    Q_OBJECT
public:
    qreal x,y,z;

    accelerometerHandler(QObject* parent = 0) : QObject(parent)
    {
        m_sensor = new QAccelerometer(this);
        m_sensor->addFilter(this);
        m_sensor->start();

        //AccelWindow->ui.
    }

//signals:
    qreal getX(){return x;}
    qreal getY(){return y;}
    qreal getZ(){return z;}


   private slots:

   // Override of QAcclerometerFilter::filter(QAccelerometerReading*)
    bool filter(QAccelerometerReading* reading)
    {
        x = reading->x();
        y = reading->y();
        z = reading->z();

        return 1;
    }

private:
QAccelerometer* m_sensor;

};

#endif // ACCELEROMETERHANDLER_H
