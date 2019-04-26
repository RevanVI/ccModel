#include "pc.h"
#include <cmath>
#include <random>

PC::PC(int num, double timeM): QObject()
{
    pcNum = num;
    intensity = 3; //in hour
    working = false;
    taskTimer.setInterval(0);
    timeMult = timeM;

    QObject::connect(&breakTimer, SIGNAL(timeout()), this, SLOT(isBroken()));
    QObject::connect(&taskTimer, SIGNAL(timeout()), this, SLOT(sendDoneTask()));
    genBreakTime();
}

bool PC::setTask(int time)
{
    if (working)
        return false;
    taskTimer.setInterval(time);
    working = true;
    taskTimer.start();
    emit sendStatus(pcNum, 1);
    return true;
}

void PC::setNum(int num)
{
    pcNum = num;
}

void PC::setIntensity(int inten)
{
    intensity = inten;
}

void PC::setTimeMultiflier(double time)
{
    timeMult = time;
}

bool PC::status() const
{
    return working;
}

void PC::changeTaskTime(int interval)
{
    taskTimer.setInterval(interval);
}

void PC::changeCheckBreakTime(int interval)
{
    breakTimer.setInterval(interval);
}

void PC::genBreakTime()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    double number = distribution(generator);
    breakTimer.setInterval(-log(number)/intensity * timeMult * 60); //in miliseconds
}

void PC::isBroken()
{
    if (working)
    {
        taskTimer.stop();
        working = false;
        emit taskEnded(pcNum, -1);
    }
    emit broken(pcNum, breakTimer.interval() / timeMult); //time in minutes
    emit sendStatus(pcNum, -1);
    genBreakTime();
}

void PC::sendDoneTask()
{
    working = false;
    taskTimer.stop();
    emit taskEnded(pcNum, +1);
    emit sendStatus(pcNum, 0);
}

void PC::start()
{
    if (taskTimer.interval() != 0)
        taskTimer.start();
    breakTimer.start();
}

void PC::pause()
{
    taskTimer.stop();
    breakTimer.stop();
}

void PC::stop()
{
    taskTimer.stop();
    taskTimer.setInterval(0);
    breakTimer.stop();
    genBreakTime();
}
