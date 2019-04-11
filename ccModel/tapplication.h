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
    void print(double, double);
};

#endif // TAPPLICATION_H
