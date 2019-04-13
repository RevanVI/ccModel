#include "tapplication.h"
#include <iostream>

using namespace std;

TApplication::TApplication(int argc, char **argv): QApplication (argc, argv)
{
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
    cout << "PC " << pcNum + 1 << " broken\tTime since last failure: " << number << "\n";
}

void TApplication::print(double allAvTime, int allCount, double allAvCount, double avTime, int count)
{
    cout << "MO = " << avTime << "\tCount = " << count << "\n";
    cout << "allMO = " << allAvTime << "\tallCount = " << allCount << "\tAvCount = " << allAvCount << "\n";
}

void TApplication::printTaskInfo(int pcNum, int count)
{
    if (pcNum == -1)
        cout << "Task didn't received\n";
    else if (count > 0)
        cout << "PC " << pcNum + 1 << " done task\n";
    else
        cout << "PC " << pcNum + 1 << " hadn't done task\n";
}

void TApplication::printTaskInfo(int time)
{
    cout << "Task generated with time = " << time / 500.0 << endl;
}

void TApplication::printTaskConnection(int pcNum)
{
    cout << "Task connected to PC " << pcNum + 1 << endl;
}
