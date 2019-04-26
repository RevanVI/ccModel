#ifndef STATISTICS_H
#define STATISTICS_H
#include <QVector>
#include <QObject>

class Statistics: public QObject
{
    Q_OBJECT
private:
    int pcCount;

    double time;
    double sqTime;
    int count;

    double allTime;
    double allSqTime;
    int allCount;
    int cycleCount;

    QVector<double> averData; //0 - allAvTime, 1 - allAvCount, 2 - SDavTime
    QVector<int> taskDonePC;
    QVector<int> taskCanceledPC;
    int taskCanceled;
public:
    Statistics(const int pcCount = 0);

    void addData(double t, int c);
    void prepareToSendMain();
    void reset();
public slots:
    void calc();
    void receiveTaskInfo(int, int);
signals:
    void sendData(int pcNum, int value); //detailed Stat data
    void sendData(QVector<double>); // main Stat Data
};

#endif // STATISTICS_H
