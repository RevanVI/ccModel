#include "calccentre.h"

CalcCentre::CalcCentre(): QObject()
{
    for (int i = 0; i < pcCount; ++i)
        pcArr[i].setNum(i + 1);
    for (int i = 0; i < pcCount; ++i)
        QObject::connect(&pcArr[i], SIGNAL(broken(int, double)), this, SLOT(getBreak(int, double)));
    QTimer* timer = new QTimer(this);
    timer->setInterval(30000);
    QObject::connect(timer, SIGNAL(timeout()), &stat, SLOT(calc()));
    QObject::connect(&stat, SIGNAL(calculated(double, int, double, double, int)), this, SLOT(getStat(double, int, double, double, int)));
    sTime.start();
    timer->start();
}

void CalcCentre::getBreak(int val1, double val2)
{
    stat.addData(sTime.elapsed() / 500, 1); //time in minutes
    emit pcBroken(val1, val2);
    sTime.restart();
}

void CalcCentre::getStat(double allAvTime, int allCount, double allAvCount, double avTime, int count)
{
    emit resendStat(allAvTime, allCount, allAvCount, avTime, count);
}
