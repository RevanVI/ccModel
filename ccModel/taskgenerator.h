#ifndef TASKGENERATOR_H
#define TASKGENERATOR_H

#include <QObject>
#include <QTimer>

class TaskGenerator: public QObject
{
    Q_OBJECT
private:
    int intensity;
    int avTime;
    QTimer taskTimer;
    double timeMult;


public:
    TaskGenerator(double timeM = 500);

    void genTime();
    void setIntensity(int inten);
    void setAvTime(int time);
    void pause();
    void start();
    void stop();
signals:
    void taskGenerated(double time);

public slots:
    void genTask();
};

#endif // TASKGENERATOR_H
