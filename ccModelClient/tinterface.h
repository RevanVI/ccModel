#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class TInterface;
}

class TInterface : public QWidget
{
    Q_OBJECT
private:
    Ui::TInterface *ui;
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
    void setStatData(int* taskCount, double avTime);
signals:
    void setBtnClicked();
    void startBtnClicked();
    void pauseBtnClicked();
    void stopBtnClicked();
};

#endif // WIDGET_H
