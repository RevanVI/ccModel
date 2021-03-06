#include "tapplication.h"
#include <iostream>

using namespace std;

TApplication::TApplication(int argc, char **argv): QApplication (argc, argv)
{
    socket.bind(QHostAddress::LocalHost, 6374);
    QObject::connect(&socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    QObject::connect(&taskGen, SIGNAL(taskGenerated(double)), &calc, SLOT(getTask(double)));

    //print block
    QObject::connect(&calc, SIGNAL(pcBroken(int, double)), this, SLOT(printBreakInfo(int, double)));
    QObject::connect(&calc, SIGNAL(resendStat(QVector<double>)), this, SLOT(printLogStat(QVector<double>)));
    QObject::connect(&calc, SIGNAL(taskEnded(int, int)), this, SLOT(printEndTaskInfo(int, int)));
    QObject::connect(&calc, SIGNAL(taskConnected(int)), this, SLOT(printTaskConnection(int)));
    QObject::connect(&taskGen, SIGNAL(taskGenerated(double)), this, SLOT(printGenTaskInfo(double)));

    //send block
    QObject::connect(&calc, SIGNAL(resendStat(QVector<double>)), this, SLOT(sendStatData(QVector<double>)));
    QObject::connect(&calc, SIGNAL(resendStat(int, int)), this, SLOT(sendStatData(int, int)));
    QObject::connect(&calc, SIGNAL(resendStatus(int, int)), this, SLOT(sendStatus(int, int)));
}

TApplication::~TApplication()
{

}

void TApplication::printBreakInfo(int pcNum, double time)
{
    cout << QTime::currentTime().toString().toStdString() << " PC " << pcNum + 1 << " broken\tTime since last failure: " << time << "\n";
}

void TApplication::printLogStat(QVector<double> averData)
{
    cout << QTime::currentTime().toString().toStdString() << " allAvTime = " << averData[0] << "\tSDAvTime = " << averData[2] << "\tAvCount = " << averData[1] << "\n";
}

void TApplication::printEndTaskInfo(int pcNum, int status)
{
    cout << QTime::currentTime().toString().toStdString();
    if (pcNum == -1)
        cout << " Task didn't received\n";
    else if (status > 0)
        cout << " PC " << pcNum + 1 << " done task\n";
    else
        cout << " PC " << pcNum + 1 << " hadn't done task\n";
}

void TApplication::printGenTaskInfo(double time)
{
    cout << QTime::currentTime().toString().toStdString() << " Task generated with time = " << time << endl;
}

void TApplication::printTaskConnection(int pcNum)
{
    cout << QTime::currentTime().toString().toStdString() << " Task connected to PC " << pcNum + 1 << endl;
}

void TApplication::receiveData()
{
    int operation = -1;
    int recData[3];
    while (socket.hasPendingDatagrams())
    {
        QByteArray* data = new QByteArray();
        data->resize(socket.pendingDatagramSize());
        socket.readDatagram(data->data(), data->size());

        QDataStream str(data, QIODevice::ReadOnly);
        str.setVersion(QDataStream::Qt_5_9);
        str >> operation;
        if (operation == 0)
            for (int i = 0; i < 3; ++i)
                str >> recData[i];
        data->clear();
        delete data;
    }
    if (operation == 0)
    {
        taskGen.setIntensity(recData[0]);
        taskGen.setAvTime(recData[1]);
        calc.setPCbreakIntensity(recData[2]);
        cout << "\nGet new values\n\n";
    }
    else if (operation == 1)
    {
        processStart();
        cout << "Start process\n";
    }
    else if (operation == 2)
    {
        processPause();
        cout << "Pause process\n";
    }
    else
    {
        processStop();
        cout << "Stop process";
    }
}

void TApplication::sendStatData(QVector<double> averData) //send data about main statistics
{
    int operation = 0;
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str.setVersion(QDataStream::Qt_5_9);
    str << operation;
    for (int i = 0; i < averData.size(); ++i)
        str << averData[i];
    int bytes = socket.writeDatagram(data, QHostAddress::LocalHost, 22022);
}

void TApplication::sendStatData(int pcNum, int count) //send data about additional statistics
{
    int operation = 9;
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str.setVersion(QDataStream::Qt_5_9);
    str << operation;
    str << pcNum << count;
    int bytes = socket.writeDatagram(data, QHostAddress::LocalHost, 22022);
}

void TApplication::sendStatus(int pcNum, int status) //send data about pc's status
{
    int operation = 10;
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str.setVersion(QDataStream::Qt_5_9);
    str << operation << pcNum << status;
    int bytes = socket.writeDatagram(data, QHostAddress::LocalHost, 22022);
}

void TApplication::processPause()
{
    taskGen.pause();
    calc.pause();
}

void TApplication::processStart()
{
    taskGen.start();
    calc.start();
}

void TApplication::processStop()
{
    taskGen.stop();
    calc.stop();
}
