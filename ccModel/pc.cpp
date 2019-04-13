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
    genBreakTime();
    breakTimer.start();
}

bool PC::setTask()
{
    if (working)
        return false;
    working = true;
    return true;
}

void PC::setNum(int num)
{
    pcNum = num;
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
    working = false;
    emit broken(pcNum, breakTimer.interval());
    genBreakTime();
}
