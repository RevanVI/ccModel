#ifndef CALCCENTRE_H
#define CALCCENTRE_H
#include "pc.h"

class CalcCentre: public QObject
{
    Q_OBJECT
private:
    PC pcArr;
public:
    CalcCentre();
public slots:
    void getBreak(double, double);

signals:
    void error(double, double);
};

#endif // CALCCENTRE_H
