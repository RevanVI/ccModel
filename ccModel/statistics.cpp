#include "statistics.h"

Statistics::Statistics(int pcCount): QObject()
{
    this->pcCount = pcCount;
    time = 0; 
    count = 0;

    cycleCount = 0;
    allCount = 0;
    allTime = 0;
    allSqTime = 0;

    averData.push_back(0); //allAvTime = 0;
    averData.push_back(0); //allAvCount = 0;
    averData.push_back(0); //SDavTime = 0;

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

    allCount += count;
    allTime += time;
    allSqTime += time * time;
    averData[0] = allTime / allCount ; //
    averData[1] = double(allCount) / cycleCount;
    averData[2] = sqrt((allSqTime / cycleCount) - averData[0]* averData[0]);
    emit sendData(averData);
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
    emit sendData(pcNum, count);
}
