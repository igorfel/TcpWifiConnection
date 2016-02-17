#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QNetworkInterface>
#include <QStringList>
#include <QHostInfo>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    c = new Client();

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(connect2Server()));
    connect(ui->sendButton, SIGNAL(clicked(bool)), this, SLOT(sendData()));

    connect(this->c, SIGNAL(hasReadData()), this, SLOT(readData()));


    /*foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        if(interface.flags().testFlag(QNetworkInterface::IsUp))
        {
            foreach(QNetworkAddressEntry entry, interface.addressEntries())
            {
              //  if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                //{
                    ui->comboBox->addItem(entry.ip().toString());
                    //ui->textEdit->append(entry.ip().toString());
                //}
            }
        }
    }*/


/*
    QList<QHostAddress> list = QNetworkInterface::allAddresses();

     for(int nIter=0; nIter<list.count(); nIter++)

      {
         // if(!list[nIter].isLoopback())
           //   if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
                 ui->comboBox->addItem(list[nIter].toString());

      }
*//*
    QList<QNetworkInterface> allInterfaces = QNetworkInterface::allInterfaces();
    QNetworkInterface eth;

    foreach(eth, allInterfaces) {
        QList<QNetworkAddressEntry> allEntries = eth.addressEntries();
        QNetworkAddressEntry entry;
        foreach (entry, allEntries) {
            ui->comboBox->addItem(entry.broadcast());
        }
    }*/

    //ui->comboBox->addItem(ip[1].toString());
    //ui->comboBox->addItem(ip[2].toString());
    //ui->comboBox->addItem(ip[3].toString());

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connect2Server()
{
    this->c->start(ui->lineEdit->text(), ui->lineEdit_2->text().toInt());
    //this->c->start("169.254.157.41", 61888);

    //this->c->client.start
    //Client c2;
    //c2.start(ui->lineEdit->text(), 8888);//ui->lineEdit_2->text());
}

void MainWindow::sendData()
{
    c->write(ui->lineEdit_2->text());
    showAccelWindow();
}

void MainWindow::readData()
{
    ui->data->setText(c->Read());
}

void MainWindow::showAccelWindow()
{
    this->AccelWindow = new accelerometerWindow(this);
    this->AccelWindow->setModal(true);
    this->AccelWindow->showFullScreen();
}
