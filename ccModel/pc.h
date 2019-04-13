#ifndef PC_H
#define PC_H

#include <QTimer>

class PC: public QObject
{
    Q_OBJECT
private:
    int pcNum;
    int intensity;
    bool working;
    int lastBreakTime; //time from last break in miliseconds;
    QTimer taskTimer;
    QTimer breakTimer;
public:
    PC(int num = 0);

    bool setTask();
    void setNum(int num);
    bool status() const;
    void changeTaskTime(int interval);
    void changeCheckBreakTime(int interval);
    void genBreakTime();
signals:
    void broken(int, double);
private slots:
    void isBroken();
};

#endif // PC_H
