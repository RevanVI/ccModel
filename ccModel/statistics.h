#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>

class Statistics: public QObject
{
    Q_OBJECT
private:
    double time;
    int count;
    double avTime;

    double allTime;
    int allCount;
    int cycleCount;

    double allAvTime;
    double allAvCount;

    int* taskDonePC;
    int* taskCanceledPC;
    int taskCanceled;
public:
    Statistics(const int pcCount = 0);

    void addData(double t, int c);
public slots:
    void calc();
    void receiveTaskInfo(int, int);
signals:
    void calculated(double, int, double, double, int);
};

#endif // STATISTICS_H
