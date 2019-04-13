#include "statistics.h"

Statistics::Statistics(int pcCount): QObject()
{
    time = 0; 
    count = 0;
    avTime = 0;

    cycleCount = 0;
    allCount = 0;
    allTime = 0;

    allAvTime = 0;
    allAvCount = 0;

    taskCanceled = 0;
    taskCanceledPC = new int[pcCount];
    taskDonePC = new int[pcCount];
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

void Statistics::receiveTaskInfo(int pcNum, int count)
{
    if (pcNum == -1)
        taskCanceled += abs(count);
    else if (count > 0)
        taskDonePC[pcNum] += count;
    else
        taskCanceledPC[pcNum] += -count;
}
