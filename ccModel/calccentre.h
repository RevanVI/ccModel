#ifndef CALCCENTRE_H
#define CALCCENTRE_H
#include <QTimer>
#include <QTime>
#include "pc.h"

class CalcCentre: public QObject
{
    Q_OBJECT
private:
    PC pcArr[1];
    double time;
    int count;
    QTime sTime;
public:
    CalcCentre();
public slots:
    void getBreak(double, double);
    void calcMO();
signals:
    void pcBroken(double, double);
    void calculated(double);
};

#endif // CALCCENTRE_H
