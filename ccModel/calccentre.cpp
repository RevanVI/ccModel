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
        QObject::connect(&pcArr[i], SIGNAL(sendStatus(int, int)), this, SLOT(getStatus(int, int)));
    }
    cycleTimer.setInterval(30000);
    addTime = 0;
    QObject::connect(&cycleTimer, SIGNAL(timeout()), stat, SLOT(calc()));
    QObject::connect(stat, SIGNAL(sendData(QVector<double>)), this, SLOT(getStat(QVector<double>)));
    QObject::connect(stat, SIGNAL(sendData(int, int)), this, SLOT(getStat(int, int)));
    QObject::connect(this, SIGNAL(taskEnded(int, int)), stat, SLOT(receiveTaskInfo(int, int)));
}

CalcCentre::~CalcCentre()
{
    delete stat;
}

void CalcCentre::setPCbreakIntensity(int inten)
{
    for (int i = 0; i < pcCount; ++i)
        pcArr[i].setIntensity(inten);
}

void CalcCentre::getBreak(int pcNum, double breakTime)
{
    stat->addData((sTime.elapsed() + addTime) / timeMult, 1); //time in minutes
    addTime = 0;
    emit pcBroken(pcNum, breakTime);
    sTime.restart();
}

void CalcCentre::getStat(QVector<double> averData)
{
    emit resendStat(averData);
}

void CalcCentre::getStat(int pcNum, int count)
{
    emit resendStat(pcNum, count);
}

void CalcCentre::getTask(double time)
{
    for (int i = 0; i < pcCount; ++i)
    {
        if (pcArr[i].status() == false)
        {
            emit taskConnected(i);
            pcArr[i].setTask(time * timeMult);
            return;
        }
    }
    emit taskEnded(-1, -1);
}

void CalcCentre::getEndedTask(int pcNum, int count)
{
    emit taskEnded(pcNum, count);
}

void CalcCentre::getStatus(int pcNum, int status)
{
    emit resendStatus(pcNum, status);
}

void CalcCentre::start()
{
    sTime.start();
    cycleTimer.start();
    for (int i = 0; i < pcCount; ++i)
        pcArr[i].start();
}

void CalcCentre::pause()
{
    addTime = sTime.elapsed();
    cycleTimer.stop();
    for (int i = 0; i < pcCount; ++i)
        pcArr[i].pause();
}

void CalcCentre::stop()
{
    cycleTimer.stop();
    cycleTimer.setInterval(30000);
    for (int i = 0; i < pcCount; ++i)
        pcArr[i].stop();
    stat->reset();
}
