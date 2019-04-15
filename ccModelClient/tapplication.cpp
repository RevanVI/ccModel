#include "tapplication.h"
#include <iostream>

using namespace std;

TApplication::TApplication(int argc, char **argv): QApplication (argc, argv)
{
    interface.show();
    socket.bind(6374);
    QObject::connect(&interface, SIGNAL(setBtnClicked()), this, SLOT(sendData()));
    QObject::connect(&interface, SIGNAL(startBtnClicked()), this, SLOT(sendData()));
    QObject::connect(&interface, SIGNAL(pauseBtnClicked()), this, SLOT(sendData()));
    QObject::connect(&interface, SIGNAL(stopBtnClicked()), this, SLOT(sendData()));
}

TApplication::~TApplication()
{

}

void TApplication::sendData()
{
    QBitArray arr(4, false);
    arr[0] = true;
    int* intData = interface.getData();
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str.setVersion(QDataStream::Qt_5_9);
    str << arr;
    for (int i = 0; i < 3; ++i)
        str << intData[i];
    int bytes = socket.writeDatagram(data, QHostAddress::LocalHost, 6374);
}

void TApplication::receiveData()
{
    QBitArray arr(4, false);
    int recData[3];
    double avTime;
    while (socket.hasPendingDatagrams())
    {
        QByteArray* data = new QByteArray();
        data->resize(socket.pendingDatagramSize());
        socket.readDatagram(data->data(), data->size());

        QDataStream str(data, QIODevice::ReadOnly);
        str.setVersion(QDataStream::Qt_5_9);
        str >> arr;
        for (int i = 0; i < 3; ++i)
            str >> recData[i];
        str >> avTime;
        data->clear();
        delete data;
    }
    if (arr[0] == true)
    {
        interface.setStatData(recData, avTime);
    }
}
