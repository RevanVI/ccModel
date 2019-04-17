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
    int count;
    double avTime;

    double allTime;
    int allCount;
    int cycleCount;

    QVector<double> averData; //0 - allAvTime, 1 - allAvCount
    QVector<int> taskDonePC;
    QVector<int> taskCanceledPC;
    int taskCanceled;
public:
    Statistics(const int pcCount = 0);

    void addData(double t, int c);
    void prepareToSendMain();
public slots:
    void calc();
    void receiveTaskInfo(int, int);
signals:
    void sendDataMain(QVector<int>, double);
    void sendData(QVector<double>, QVector<int>, QVector<int>, int);
};

#endif // STATISTICS_H
