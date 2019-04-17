#ifndef TAPPLICATION_H
#define TAPPLICATION_H
#include <QtWidgets/QApplication>
#include <QtNetwork/QUdpSocket>
#include <QDataStream>
#include <QBitArray>
#include "calccentre.h"
#include "taskgenerator.h"

using namespace std;

class TApplication: public QApplication
{
    Q_OBJECT
private:
    CalcCentre calc;
    TaskGenerator taskGen;
    QUdpSocket socket;
public:
    TApplication(int argc, char **argv);
    ~TApplication();
    void processPause();
    void processStart();
    void processStop();
private slots:
    void printBreakInfo(int pcNum, double time);
    void printLogStat(QVector<double> averData);
    void printEndTaskInfo(int pcNum, int status); // pcNum - num of PC or -1 if all PCs working, status (+1/-1)
    void printGenTaskInfo(double time);
    void printTaskConnection(int pcNum);
    void receiveData();
    void sendStatData(QVector<double> averData, QVector<int> taskDonePC, QVector<int> taskCanceledPC, int taskCanceled);
    void sendStatus(int pcNum, int status);
};

#endif // TAPPLICATION_H
