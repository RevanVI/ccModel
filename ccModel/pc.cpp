#include "pc.h"
#include <cmath>
#include <random>

PC::PC(): QObject()
{
    intensity = 1; //in hour
    working = false;
    lastBreakTime = 0;
    taskTimer.setInterval(500);
    breakTimer.setInterval(100);

    QObject::connect(&breakTimer, SIGNAL(timeout()), this, SLOT(isBroken()));
    breakTimer.start();
}

bool PC::setTask()
{
    if (working)
        return false;
    working = true;
    return true;
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

void PC::isBroken()
{
    lastBreakTime += breakTimer.interval();
    double prop = 1.0 / pow(2.7, intensity * lastBreakTime / 500.0 / 60); //propability of normal work

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    double number = distribution(generator);

    if (number > prop)
    {
        lastBreakTime = 0;
        working = false;
        emit broken(prop, number);
    }
}
