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

    bool setTask(int time);
    void setNum(int num);
    void setIntensity(int inten);
    bool status() const;
    void changeTaskTime(int interval);
    void changeCheckBreakTime(int interval);
    void genBreakTime();
signals:
    void broken(int, double);
    void taskEnded(int, int); //int1 - PC num, int2 = +1 if done, -1 if canceled
private slots:
    void isBroken();
    void sendDoneTask();
};

#endif // PC_H
