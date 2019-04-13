#ifndef TAPPLICATION_H
#define TAPPLICATION_H
#include <QtWidgets/QApplication>
#include "calccentre.h"
#include "taskgenerator.h"

using namespace std;

class TApplication: public QApplication
{
    Q_OBJECT
private:
    CalcCentre calc;
    TaskGenerator taskGen;
public:
    TApplication(int argc, char **argv);
    ~TApplication();

private slots:
    void print(int, double);
    void print(double, int, double, double, int);
    void printTaskInfo(int, int);
    void printTaskInfo(int);
    void printTaskConnection(int);
};

#endif // TAPPLICATION_H
