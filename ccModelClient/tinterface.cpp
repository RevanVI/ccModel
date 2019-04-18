#include "tinterface.h"
#include "ui_tinterface.h"

QT_CHARTS_USE_NAMESPACE

TInterface::TInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TInterface)
{
    ui->setupUi(this);
    this->setLayout(ui->mainLayt);
    ui->groupBox_2->setLayout(ui->horizontalLayout_3);

    QVector<QBarSet> set;
    for (int i = 0; i < 5; ++i)
    {
        QBarSet buf("PC" + QString::number(i + 1));
        set.push_back(buf);
        for (int j = 0; j < 2; ++j)
            set[i] << 0;
    }
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
    emit btnClicked(0);
}

void TInterface::on_startBtn_clicked()
{
    emit btnClicked(1);
}

void TInterface::on_pauseBtn_clicked()
{
    emit btnClicked(2);
}

void TInterface::on_stopBtn_clicked()
{
    emit btnClicked(3);
}

void TInterface::setStatData(QVector<double> averData, QVector<int> taskDonePC, QVector<int> taskCanceledPC, int taskCanceled)
{
    int taskDone = 0;
    int taskCanceledSum = 0;
    for (int i = 0; i < taskDonePC.size(); ++i)
        taskDone += taskDonePC[i];
    for (int i = 0; i < taskCanceledPC.size(); ++i)
        taskCanceledSum += taskCanceledPC[i];
    ui->taskDoneSBox->setValue(taskDone);
    ui->notRecTaskSBox->setValue(taskCanceled);
    ui->canceledTaskSBox->setValue(taskCanceledSum);
    ui->avTimeSBox->setValue(averData[0]);
}
