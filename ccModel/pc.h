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
    double timeMult;
public:
    PC(int num = 0, double timeM = 500);

    bool setTask(int time);
    void setNum(int num);
    void setIntensity(int inten);
    void setTimeMultiflier(double time);
    bool status() const;
    void changeTaskTime(int interval);
    void changeCheckBreakTime(int interval);
    void genBreakTime();
signals:
    void broken(int pcNum, double time);
    void taskEnded(int pcNum, int taskStatus);
    void sendStatus(int pcNum, int status);
private slots:
    void isBroken();
    void sendDoneTask();
};

#endif // PC_H
