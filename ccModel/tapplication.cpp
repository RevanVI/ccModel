#include "tapplication.h"
#include <iostream>

using namespace std;

TApplication::TApplication(int argc, char **argv): QApplication (argc, argv)
{
    QObject::connect(&calc, SIGNAL(error(double, double)), this, SLOT(print(double, double)));
}

TApplication::~TApplication()
{

}

void TApplication::print(double prop, double number)
{
    cout << "PC broken\tProp: " << prop << "\tNumber: " << number << "\n";
}
