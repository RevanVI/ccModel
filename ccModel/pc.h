#ifndef PC_H
#define PC_H

#include <QTimer>

class PC: public QObject
{
    Q_OBJECT
private:
    int intensity;
    bool working;
    int lastBreakTime; //time from last break in miliseconds;
    QTimer taskTimer;
    QTimer breakTimer;
public:
    PC();

    bool setTask();
    bool status() const;
    void changeTaskTime(int interval);
    void changeCheckBreakTime(int interval);
    void genBreakTime();
signals:
    void broken(double, double);

private slots:
    void isBroken();


};

#endif // PC_H
