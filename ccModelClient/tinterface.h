#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QTimer>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>

namespace Ui {
class TInterface;
}

class TInterface : public QWidget
{
    Q_OBJECT
private:
    Ui::TInterface *ui;
    QVector<QtCharts::QBarSet*> setPC;
    QtCharts::QChartView* chartView;
    QVector<QLabel*> statusLbl;
    int maxVal;
    bool isStopped;
private slots:
    void on_setBtn_clicked();
    void on_startBtn_clicked();
    void on_stopBtn_clicked();
    void on_pauseBtn_clicked();
public:
    explicit TInterface(QWidget *parent = nullptr);
    ~TInterface();

    int* getData();
public slots:
    void setStatData(QVector<double> averData);
    void setStatData(int pcNum, int count);
    void setStatus(int pcNum, int status);
signals:
    void btnClicked(int btnNum);
};

#endif // WIDGET_H
