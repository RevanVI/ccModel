#include "calccentre.h"

CalcCentre::CalcCentre(): QObject()
{
    for (int i = 0; i < pcCount; ++i)
        pcArr[i].setNum(i);
    for (int i = 0; i < pcCount; ++i)
        QObject::connect(&pcArr[i], SIGNAL(broken(int, double)), this, SLOT(getBreak(int, double)));
    QTimer* timer = new QTimer(this);
    timer->setInterval(30000);
    QObject::connect(timer, SIGNAL(timeout()), &stat, SLOT(calc()));
    QObject::connect(&stat, SIGNAL(calculated(double, int, double, int)), this, SLOT(getStat(double, int, double, int)));
    sTime.start();
    timer->start();
}

void CalcCentre::getBreak(int val1, double val2)
{
    stat.addData(sTime.elapsed(), 1);
    emit pcBroken(val1, val2);
    sTime.restart();
}

void CalcCentre::getStat(double allMO, int allCount, double MO, int count)
{
    emit resendStat(allMO, allCount, MO, count);
}
