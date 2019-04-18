#include "tinterface.h"
#include "ui_tinterface.h"

#include <QDebug>

QT_CHARTS_USE_NAMESPACE

TInterface::TInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TInterface)
{
    ui->setupUi(this);
    this->setLayout(ui->mainLayt);
    ui->groupBox_2->setLayout(ui->horizontalLayout_3);

    ui->groupBox_3->setLayout(ui->gridLayout);
    statusLbl.push_back(ui->status0);
    statusLbl.push_back(ui->status1);
    statusLbl.push_back(ui->status2);
    statusLbl.push_back(ui->status3);
    statusLbl.push_back(ui->status4);

    maxVal = -1;
    for (int i = 0; i < 5; ++i)
    {
        QBarSet* buf = new QBarSet("PC" + QString::number(i + 1));
        setPC.push_back(buf);
        for (int j = 0; j < 2; ++j)
            *setPC[i] << 0;
    }
    QHorizontalBarSeries *series = new QHorizontalBarSeries();
    for (int i = 0; i < setPC.size(); ++i)
        series->append(setPC[i]);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Детальная статистика");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Выполнено" << "Отменено";
    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(categories);
    chart->setAxisY(axisY, series);
    QValueAxis *axisX = new QValueAxis();
    axisX->setTickCount(6);
    chart->setAxisX(axisX, series);
    axisX->applyNiceNumbers();

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QBoxLayout* layt = new QBoxLayout(QBoxLayout::TopToBottom);
    layt->addWidget(chartView);
    ui->statWgt->setLayout(layt);
}

TInterface::~TInterface()
{
    delete ui;
    for (int i = 0; i < setPC.size(); ++i)
        delete setPC[i];
    delete chartView;
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
    for (int i = 0; i < 5; ++i)
        setStatus(i, 0);
}

void TInterface::on_pauseBtn_clicked()
{
    emit btnClicked(2);
}

void TInterface::on_stopBtn_clicked()
{
    emit btnClicked(3);
    for (int i = 0; i < 5; ++i)
        setStatus(i, -2);
}

void TInterface::setStatData(QVector<double> averData)
{
    ui->avTimeSBox->setValue(averData[0]);
}

void TInterface::setStatData(int pcNum, int count)
{
    qDebug() << "setData " << pcNum << " " << count << "\n";
    if (pcNum != -1)
    {
        if (count > 0)
        {
            ui->taskDoneSBox->setValue(ui->taskDoneSBox->value() + 1);
            setPC[pcNum]->replace(0, setPC[pcNum]->at(0) + 1);
        }
        else
        {
            ui->canceledTaskSBox->setValue(ui->canceledTaskSBox->value() + 1);
            setPC[pcNum]->replace(1, setPC[pcNum]->at(1) + 1);
        }

        if (setPC[pcNum]->at(0) > maxVal)
            maxVal = setPC[pcNum]->at(0);
        else if (setPC[pcNum]->at(1) > maxVal)
            maxVal = setPC[pcNum]->at(1);

        int buf = maxVal / 5;
        if (buf == 0 && maxVal >= 5)
            buf = maxVal + 5;
        else
            buf = buf * 5 + 5;
        chartView->chart()->axisX()->setRange(0, buf);
    }
    else
        ui->notRecTaskSBox->setValue(ui->notRecTaskSBox->value() + 1);
}

void TInterface::setStatus(int pcNum, int status)
{
    if (status == 0)
    {
        statusLbl[pcNum]->setStyleSheet("color: rgb(0, 0, 0)");
        statusLbl[pcNum]->setText("Waiting");
    }
    else if (status == 1)
    {
        statusLbl[pcNum]->setStyleSheet("color: rgb(0, 0, 100)");
        statusLbl[pcNum]->setText("Working");
    }
    else if (status == -1)
    {
        statusLbl[pcNum]->setStyleSheet("color: rgb(100, 0, 0)");
        statusLbl[pcNum]->setText("Broken");
        QTimer::singleShot(400, this,[=](){ this->setStatus(pcNum, status + 1); });
    }
    else if (status == -2)
    {
        statusLbl[pcNum]->setStyleSheet("color: rgb(0, 0, 0)");
        statusLbl[pcNum]->setText("off");
    }
}
