#include "pc.h"
#include <cmath>
#include <random>

PC::PC(int num): QObject()
{
    pcNum = num;
    intensity = 3; //in hour
    working = false;
    lastBreakTime = 0;
    taskTimer.setInterval(500);

    QObject::connect(&breakTimer, SIGNAL(timeout()), this, SLOT(isBroken()));
    QObject::connect(&taskTimer, SIGNAL(timeout()), this, SLOT(sendDoneTask()));
    genBreakTime();
    breakTimer.start();
}

bool PC::setTask(int time)
{
    if (working)
        return false;
    taskTimer.setInterval(time);
    working = true;
    taskTimer.start();
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
    breakTimer.setInterval(-log(number)/intensity * 500 * 60); //in miliseconds
}

void PC::isBroken()
{
    lastBreakTime = 0;
    if (working)
    {
        taskTimer.stop();
        working = false;
        emit taskEnded(pcNum, -1);
    }
    emit broken(pcNum, breakTimer.interval() / 500.0); //time in minutes
    genBreakTime();
}

void PC::sendDoneTask()
{
    working = false;
    taskTimer.stop();
    emit taskEnded(pcNum, +1);
}
