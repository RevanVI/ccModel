#include "taskgenerator.h"
#include <random>

TaskGenerator::TaskGenerator(double timeM): QObject()
{
    intensity = 5;
    avTime = 5;
    timeMult = timeM;
    genTime();
    QObject::connect(&taskTimer, SIGNAL(timeout()), this, SLOT(genTask()));
}

void TaskGenerator::genTime()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    double number = distribution(generator);
    taskTimer.setInterval(-log(number)/intensity * timeMult * 60); //in real miliseconds
}

void TaskGenerator::genTask()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    double number = distribution(generator);
    emit taskGenerated(-log(number) * avTime); //in minutes
    genTime();
}

void TaskGenerator::setIntensity(int inten)
{
    intensity = inten;
}

void TaskGenerator::setAvTime(int time)
{
    avTime = time;
}

void TaskGenerator::pause()
{
    taskTimer.stop();
}

void TaskGenerator::start()
{
    taskTimer.start();
}

void TaskGenerator::stop()
{
    taskTimer.stop();
    genTime();
}
