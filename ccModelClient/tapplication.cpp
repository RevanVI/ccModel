#include "tapplication.h"
#include <iostream>

using namespace std;

TApplication::TApplication(int argc, char **argv): QApplication (argc, argv)
{
    interface.show();
    socket.bind(22022);
    QObject::connect(&socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    QObject::connect(&interface, SIGNAL(btnClicked(int)), this, SLOT(sendData(int)));
}

TApplication::~TApplication()
{

}

void TApplication::sendData(int btnNum)
{

    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str.setVersion(QDataStream::Qt_5_9);
    str << btnNum;
    if (btnNum == 0)
    {
        int* intData = interface.getData();
        for (int i = 0; i < 3; ++i)
            str << intData[i];
        delete[] intData;
    }
    int bytes = socket.writeDatagram(data, QHostAddress::LocalHost, 6374);
}

void TApplication::receiveData()
{
    int operation;
    QVector<double> averData;
    int pcNum = -2;
    int count = 0;
    while (socket.hasPendingDatagrams())
    {
        averData.clear();
        pcNum = -2;
        count = 0;
        QByteArray* data = new QByteArray();
        data->resize(socket.pendingDatagramSize());
        socket.readDatagram(data->data(), data->size());

        QDataStream str(data, QIODevice::ReadOnly);
        str.setVersion(QDataStream::Qt_5_9);
        str >> operation;

        if (operation == 0)
        {
            double buf;
            for (int i = 0; i < 2; ++i)
            {
                str >> buf;
                averData.push_back(buf);
            }
        }
        else if (operation == 9)
        {
            str >> pcNum >> count;
            qDebug() << "receive " << pcNum << " " << count << endl;
        }
        else if (operation == 10) //status
           for (int i = 0; i < 2; ++i)
           {
               int buf;
               str >> buf;
           }
        data->clear();
        delete data;
    }
    if (operation == 0)
        interface.setStatData(averData);
    else if (operation == 9)
        interface.setStatData(pcNum, count);
    //if (operation == 10)
            //interface.setStatus(taskDonePC);
}
