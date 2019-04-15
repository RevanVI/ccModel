#include "tinterface.h"
#include "tapplication.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    TApplication a(argc, argv);

    return a.exec();
}
