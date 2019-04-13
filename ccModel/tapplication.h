#ifndef TAPPLICATION_H
#define TAPPLICATION_H
#include <QtWidgets/QApplication>
#include "calccentre.h"

using namespace std;

class TApplication: public QApplication
{
    Q_OBJECT
private:
    CalcCentre calc;
public:
    TApplication(int argc, char **argv);
    ~TApplication();

private slots:
    void print(int, double);
    void print(double, int, double, double, int);
};

#endif // TAPPLICATION_H
