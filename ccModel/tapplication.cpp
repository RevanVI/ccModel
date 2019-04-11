#include "tapplication.h"
#include <iostream>

using namespace std;

TApplication::TApplication(int argc, char **argv): QApplication (argc, argv)
{
    QObject::connect(&calc, SIGNAL(pcBroken(double, double)), this, SLOT(print(double, double)));
    QObject::connect(&calc, SIGNAL(calculated(double)), this, SLOT(print(double)));
}

TApplication::~TApplication()
{

}

void TApplication::print(double prop, double number)
{
    cout << "PC broken\tProp: " << prop << "\tNumber: " << number << "\n";
}

void TApplication::print(double MO)
{
    cout << "MO = " << MO << "\n";
}
