#ifndef TAPPLICATION_H
#define TAPPLICATION_H
#include <QtWidgets/QApplication>
#include <QtNetwork/QUdpSocket>
#include <QDataStream>
#include <QBitArray>
#include "tinterface.h"

using namespace std;

class TApplication: public QApplication
{
    Q_OBJECT
private:
    TInterface interface;
public:
    TApplication(int argc, char **argv);
    ~TApplication();
    QUdpSocket socket;
private slots:
    void sendData(int btnNum);
    void receiveData();
};

#endif // TAPPLICATION_H
