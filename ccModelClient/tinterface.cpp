#include "tinterface.h"
#include "ui_tinterface.h"

TInterface::TInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TInterface)
{
    ui->setupUi(this);
    this->setLayout(ui->mainLayt);
}

TInterface::~TInterface()
{
    delete ui;
}

int* TInterface::getData()
{
    int * data = new int[3];
    data[0] = ui->taskIntSBox->value();
    data[1] = ui->taskTimeSBox->value();
    data[2] = ui->breakIntSBox->value();
    return data;
}

void TInterface::on_setBtn_clicked()
{
    emit setBtnClicked();
}

void TInterface::on_startBtn_clicked()
{
    emit startBtnClicked();
}

void TInterface::on_stopBtn_clicked()
{
    emit stopBtnClicked();
}

void TInterface::on_pauseBtn_clicked()
{
    emit pauseBtnClicked();
}

void TInterface::setStatData(int* taskCount, double avTime)
{
    ui->taskDoneSBox->setValue(taskCount[0]);
    ui->notRecTaskSBox->setValue(taskCount[1]);
    ui->canceledTaskSBox->setValue(taskCount[2]);
    ui->avTimeSBox->setValue(avTime);
}
