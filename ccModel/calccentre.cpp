#include "calccentre.h"

CalcCentre::CalcCentre(): QObject()
{
    QObject::connect(&pcArr, SIGNAL(broken(double, double)), this, SLOT(getBreak(double, double)));
}

void CalcCentre::getBreak(double val1, double val2)
{
    emit error(val1, val2);
}
