#include "statistics.h"

Statistics::Statistics(int pcCount): QObject()
{
    this->pcCount = pcCount;
    time = 0; 

    count = 0;
    avTime = 0;

    cycleCount = 0;
    allCount = 0;
    allTime = 0;

    averData.push_back(0); //allAvTime = 0;
    averData.push_back(0); //allAvCount = 0;

    taskCanceled = 0;
    for (int i = 0; i < pcCount; ++i)
    {
        taskDonePC.push_back(0);
        taskCanceledPC.push_back(0);
    }

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
    averData[0] =(allTime / 60) / allCount;
    averData[1] = double(allCount) / cycleCount;

    emit sendData(averData, taskDonePC, taskCanceledPC, taskCanceled);
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
    emit sendData(averData, taskDonePC, taskCanceledPC, taskCanceled);
}
