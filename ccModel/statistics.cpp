#include "statistics.h"

Statistics::Statistics(): QObject()
{
    time = 0; 
    count = 0;
    avTime = 0;

    cycleCount = 0;
    allCount = 0;
    allTime = 0;

    allAvTime = 0;
    allAvCount = 0;
}

void Statistics::addData(double t, int c)
{
    time += t;
    count += c;
}

void Statistics::calc()
{
    ++cycleCount;
    avTime = (time / 60) / count;

    allCount += count;
    allTime += time;
    allAvTime =(allTime / 60) / allCount;
    allAvCount = double(allCount) / cycleCount;
    emit calculated(allAvTime, allCount, allAvCount, avTime, count);
    time = 0;
    count = 0;
}
