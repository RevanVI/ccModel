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

    void pause();
    void start();
    void stop();
public:
    TaskGenerator(double timeM = 500);

    void genTaskTime();
    void setIntensity(int inten);
    void setAvTime(int time);
signals:
    void taskGenerated(double time);

public slots:
    void genTask();
};

#endif // TASKGENERATOR_H
