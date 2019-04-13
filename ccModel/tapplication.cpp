#include "tapplication.h"
#include <iostream>

using namespace std;

TApplication::TApplication(int argc, char **argv): QApplication (argc, argv)
{
    QObject::connect(&calc, SIGNAL(pcBroken(int, double)), this, SLOT(print(int, double)));
    QObject::connect(&calc, SIGNAL(resendStat(double, int, double, double, int)), this, SLOT(print(double, int, double, double, int)));
}

TApplication::~TApplication()
{

}

void TApplication::print(int pcNum, double number)
{
    cout << "PC " << pcNum << " broken\tTime since last failure: " << number << "\n";
}

void TApplication::print(double allAvTime, int allCount, double allAvCount, double avTime, int count)
{
    cout << "MO = " << avTime << "\tCount = " << count << "\n";
    cout << "allMO = " << allAvTime << "\tallCount = " << allCount << "\tAvCount = " << allAvCount << "\n";
}
