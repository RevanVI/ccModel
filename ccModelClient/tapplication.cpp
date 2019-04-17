#include "tapplication.h"
#include <iostream>

using namespace std;

TApplication::TApplication(int argc, char **argv): QApplication (argc, argv)
{
    interface.show();
    socket.bind(22022);
    QObject::connect(&socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
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
    int operation = 0;
    int* intData = interface.getData();
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str.setVersion(QDataStream::Qt_5_9);
    str << operation;
    for (int i = 0; i < 3; ++i)
        str << intData[i];
    int bytes = socket.writeDatagram(data, QHostAddress::LocalHost, 6374);
    delete[] intData;
}

void TApplication::receiveData()
{
    int operation;
    QVector<double> averData;
    QVector<int> taskDonePC;
    QVector<int> taskCanceledPC;
    int taskCanceled;
    while (socket.hasPendingDatagrams())
    {
        averData.clear();
        taskDonePC.clear();
        taskCanceledPC.clear();
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
            int buf1;
            for (int i = 0; i < 3; ++i)
            {
                str >> buf1;
                taskDonePC.push_back(buf1);
            }
            for (int i = 0; i < 3; ++i)
            {
                str >> buf1;
                taskCanceledPC.push_back(buf1);
            }
            str >> taskCanceled;
        }
        data->clear();
        delete data;
    }
    if (operation == 0)
        interface.setStatData(averData, taskDonePC, taskCanceledPC, taskCanceled);
}
