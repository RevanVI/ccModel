#include "calccentre.h"

CalcCentre::CalcCentre(): QObject()
{
    count = 0;
    time = 0;
    for (int i = 0; i < 1; ++i)
        QObject::connect(&pcArr[i], SIGNAL(broken(double, double)), this, SLOT(getBreak(double, double)));
    QTimer* timer = new QTimer(this);
    timer->setInterval(30000);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(calcMO()));

    sTime.start();
    timer->start();
}

void CalcCentre::getBreak(double val1, double val2)
{
    ++count;
    time += sTime.elapsed();
    emit pcBroken(val1, val2);
    sTime.restart();
}

void CalcCentre::calcMO()
{
    double buf = (time / 500 / 60) / count;
    emit calculated(count);
    time = 0;
    count = 0;
    sTime.restart();
}
