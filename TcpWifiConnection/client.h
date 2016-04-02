#ifndef CLIENT_H
#define CLIENT_H

// client.h
#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <SistemasdeControle/headers/primitiveLibs/LinAlg/matrix.h>

class Client: public QObject
{
Q_OBJECT
public:
  Client(QObject* parent = 0);
  ~Client();
  void write(QString str);
  void start(QString address, quint16 port);
  QString Read()const{return readByte;}
  //QTcpSocket getClient()const{ return client; }
  QTcpSocket client;
  LinAlg::Matrix<int> getSensorData();

public slots:
  void read();
  void wake();
signals:
  void hasReadData();

private:
  int byteData;
  LinAlg::Matrix<int> sensorData;
  //QTcpSocket client;
  QString readByte, writeByte, tempStr;
  QNetworkSession *networkSession;
  void realTimeSensor(const char *buffer);

};
#endif //CLIENT_H
