#ifndef CALCCENTRE_H
#define CALCCENTRE_H
#include <QTimer>
#include <QTime>
#include "pc.h"
#include "statistics.h"

class CalcCentre: public QObject
{
    Q_OBJECT
private:
    static const int pcCount = 5;
    PC pcArr[pcCount];
    Statistics* stat;
    QTime sTime;
    double timeMult = 500;
    QTimer cycleTimer;
    int addTime;
public:
    CalcCentre();
    ~CalcCentre();
    void setPCbreakIntensity(int inten);

    void start();
    void pause();
    void stop();
public slots:
    void getBreak(int pcNum, double time);
    void getStat(QVector<double>);
    void getStat(int pcNum, int count);
    void getTask(double time);//
    void getEndedTask(int pcNum, int taskStatus);
    void getStatus(int pcNum, int status);
signals:
    void pcBroken(int pcNum, double time);
    void resendStat(QVector<double>);
    void resendStat(int, int);
    void taskEnded(int pcNum, int taskStatus);
    void taskConnected(int pcNum);
    void resendStatus(int pcNum, int status);
};

#endif // CALCCENTRE_H
