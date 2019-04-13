#include "calccentre.h"

CalcCentre::CalcCentre(): QObject()
{
    stat = new Statistics(pcCount);
    for (int i = 0; i < pcCount; ++i)
        pcArr[i].setNum(i);
    for (int i = 0; i < pcCount; ++i)
    {
        QObject::connect(&pcArr[i], SIGNAL(broken(int, double)), this, SLOT(getBreak(int, double)));
        QObject::connect(&pcArr[i], SIGNAL(taskEnded(int, int)), this, SLOT(getEndedTask(int, int)));
    }
    QTimer* timer = new QTimer(this);
    timer->setInterval(30000);
    QObject::connect(timer, SIGNAL(timeout()), stat, SLOT(calc()));
    QObject::connect(stat, SIGNAL(calculated(double, int, double, double, int)), this, SLOT(getStat(double, int, double, double, int)));
    QObject::connect(this, SIGNAL(taskEnded(int, int)), stat, SLOT(receiveTaskInfo(int, int)));
    sTime.start();
    timer->start();
}

void CalcCentre::setPCbreakIntensity(int inten)
{
    for (int i = 0; i < pcCount; ++i)
        pcArr[i].setIntensity(inten);
}

void CalcCentre::getBreak(int pcNum, double breakTime)
{
    stat->addData(sTime.elapsed() / 500.0, 1); //time in minutes
    emit pcBroken(pcNum, breakTime);
    sTime.restart();
}

void CalcCentre::getStat(double allAvTime, int allCount, double allAvCount, double avTime, int count)
{
    emit resendStat(allAvTime, allCount, allAvCount, avTime, count);
}

void CalcCentre::getTask(int time)
{
    for (int i = 0; i < pcCount; ++i)
    {
        if (pcArr[i].status() == false)
        {
            emit taskConnected(i);
            pcArr[i].setTask(time);
            return;
        }
    }
    emit taskEnded(-1, -1);
}

void CalcCentre::getEndedTask(int pcNum, int count)
{
    emit taskEnded(pcNum, count);
}
