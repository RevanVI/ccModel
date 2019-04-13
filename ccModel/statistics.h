#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>

class Statistics: public QObject
{
    Q_OBJECT
private:
    double time;
    int count;
    double MO;
    double allMO;
    double allTime;
    int allCount;
public:
    Statistics();

    void addData(double t, int c);
public slots:
    void calc();
signals:
    void calculated(double, int, double, int);
};

#endif // STATISTICS_H
