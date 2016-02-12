// client.h
#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>

class Client: public QObject
{
Q_OBJECT
public:
  Client(QObject* parent = 0);
  ~Client();
  void start(QString address, quint16 port);

  void write(QString str);
  QString Read()const{return readByte;}

public slots:
  void read();
  void wake();
signals:
  void hasReadData();

private:
  QString readByte, writeByte;
  QTcpSocket client;
  QNetworkSession *networkSession;
};
