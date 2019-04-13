#include "statistics.h"

Statistics::Statistics(): QObject()
{
    time = 0;
    allTime = 0;
    count = 0;
    allCount = 0;
    MO = 0;
    allMO = 0;
}

void Statistics::addData(double t, int c)
{
    time += t;
    count += c;
}

void Statistics::calc()
{
    MO = (time / 500 / 60) / count;
    allCount += count;
    allTime += time;
    allMO =(allTime / 500 / 60) / allCount;
    emit calculated(allMO, allCount, MO, count);
    time = 0;
    count = 0;
}
