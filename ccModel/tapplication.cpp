#include "tapplication.h"
#include <iostream>

using namespace std;

TApplication::TApplication(int argc, char **argv): QApplication (argc, argv)
{
    socket.bind(6374);
    QObject::connect(&socket, SIGNAL(readyRead()), this, SLOT(receiveData()));

    QObject::connect(&calc, SIGNAL(pcBroken(int, double)), this, SLOT(print(int, double)));
    QObject::connect(&calc, SIGNAL(resendStat(double, int, double, double, int)), this, SLOT(print(double, int, double, double, int)));
    QObject::connect(&taskGen, SIGNAL(taskGenerated(int)), &calc, SLOT(getTask(int)));
    QObject::connect(&taskGen, SIGNAL(taskGenerated(int)), this, SLOT(printTaskInfo(int)));
    QObject::connect(&calc, SIGNAL(taskEnded(int, int)), this, SLOT(printTaskInfo(int, int)));
    QObject::connect(&calc, SIGNAL(taskConnected(int)), this, SLOT(printTaskConnection(int)));
}

TApplication::~TApplication()
{

}

void TApplication::print(int pcNum, double number)
{
    cout << QTime::currentTime().toString().toStdString() << " PC " << pcNum + 1 << " broken\tTime since last failure: " << number << "\n";
}

void TApplication::print(double allAvTime, int allCount, double allAvCount, double avTime, int count)
{
    cout << QTime::currentTime().toString().toStdString() << " MO = " << avTime << "\tCount = " << count << "\n";
    cout << "allMO = " << allAvTime << "\tallCount = " << allCount << "\tAvCount = " << allAvCount << "\n";
}

void TApplication::printTaskInfo(int pcNum, int count)
{
    cout << QTime::currentTime().toString().toStdString();
    if (pcNum == -1)
        cout << " Task didn't received\n";
    else if (count > 0)
        cout << " PC " << pcNum + 1 << " done task\n";
    else
        cout << " PC " << pcNum + 1 << " hadn't done task\n";
}

void TApplication::printTaskInfo(int time)
{
    cout << QTime::currentTime().toString().toStdString() << " Task generated with time = " << time / 500.0 << endl;
}

void TApplication::printTaskConnection(int pcNum)
{
    cout << QTime::currentTime().toString().toStdString() << " Task connected to PC " << pcNum + 1 << endl;
}

void TApplication::receiveData()
{
    QBitArray arr(4, false);
    int recData[3];
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
        data->clear();
        delete data;
    }
    if (arr[0] == true)
    {
        taskGen.setIntensity(recData[0]);
        taskGen.setAvTime(recData[1]);
        calc.setPCbreakIntensity(recData[2]);
        cout << "\nGet new values\n\n";
    }
}
