#ifndef TASKGENERATOR_H
#define TASKGENERATOR_H

#include <QObject>
#include <QTimer>

class TaskGenerator: public QObject
{
    Q_OBJECT
private:
    int intensity;
    QTimer taskTimer;
public:
    TaskGenerator();

    void genTaskTime();
    void setIntensity();

signals:
    void taskGenerated();

public slots:
    void genTask();
};

#endif // TASKGENERATOR_H
