// client.cc
#include "client.h"
#include <QHostAddress>
#include <iostream>

Client::Client(QObject* parent): QObject(parent)
{
  connect(&client, SIGNAL(connected()),
    this, SLOT(wake()));
    //hasRead = 0;
    connect(&client, SIGNAL(readyRead()), this, SLOT(read()));

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        //getFortuneButton->setEnabled(false);
        //statusLabel->setText(tr("Opening network session."));
        networkSession->open();
    }
}

Client::~Client()
{
    client.disconnectFromHost();
    client.close();
}

void Client::start(QString address, quint16 port)
{
    QHostAddress addr(address);
    client.connectToHost(addr, port);
}

void Client::write(QString str)
{
    client.waitForConnected();
    client.write(str.toStdString().c_str());
    client.flush();
}

void Client::read()
{
    char buffer[1024] = {0};
    client.read(buffer, client.bytesAvailable());
    this->readByte = buffer;
    emit this->hasReadData();

}

void Client::wake(){}

