#ifndef CALCCENTRE_H
#define CALCCENTRE_H
#include <QTimer>
#include <QTime>
#include "pc.h"
#include "statistics.h"

class CalcCentre: public QObject
{
    Q_OBJECT
private:
    static const int pcCount = 3;
    PC pcArr[pcCount];
    Statistics stat;
    QTime sTime;
public:
    CalcCentre();
public slots:
    void getBreak(int, double);
    void getStat(double allMO, int allCount, double MO, int count);
signals:
    void pcBroken(int, double);
    void resendStat(double, int, double, int);
};

#endif // CALCCENTRE_H
