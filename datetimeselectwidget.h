#ifndef DATETIMESELECTWIDGET_H
#define DATETIMESELECTWIDGET_H

#include <QWidget>

class ScrollNumberWidget;
class QHBoxLayout;

class DateTimeSelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DateTimeSelectWidget(QWidget *parent = 0);

signals:

public slots:

private:
    void initUI();

private:
    ScrollNumberWidget *m_pScrollNumFirtst;
    ScrollNumberWidget *m_pScrollNumSecond;
    ScrollNumberWidget *m_pScrollNumThird;

    QHBoxLayout *m_pHMainLayout;
};

#endif // DATETIMESELECTWIDGET_H
