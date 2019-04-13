#include "tapplication.h"
#include <iostream>

using namespace std;

TApplication::TApplication(int argc, char **argv): QApplication (argc, argv)
{
    QObject::connect(&calc, SIGNAL(pcBroken(int, double)), this, SLOT(print(int, double)));
    QObject::connect(&calc, SIGNAL(resendStat(double, int, double, int)), this, SLOT(print(double, int, double, int)));
}

TApplication::~TApplication()
{

}

void TApplication::print(int pcNum, double number)
{
    cout << "PC " << pcNum << " broken\tInterval: " << number << "\n";
}

void TApplication::print(double allMO, int allCount, double MO, int count)
{
    cout << "MO = " << MO << "\tCount = " << count << "\n";
    cout << "allMO = " << allMO << "\tallCount = " << allCount << "\n";
}
