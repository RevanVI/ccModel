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
public:
    TaskGenerator();

    void genTaskTime();
    void setIntensity(int inten);
signals:
    void taskGenerated(int);

public slots:
    void genTask();
};

#endif // TASKGENERATOR_H
