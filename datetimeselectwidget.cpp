#include "datetimeselectwidget.h"
#include "scrollnumberwidget.h"

#include <QHBoxLayout>

DateTimeSelectWidget::DateTimeSelectWidget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

void DateTimeSelectWidget::initUI()
{
    m_pScrollNumFirtst = new ScrollNumberWidget(this);
    m_pScrollNumFirtst->setRange(1, 23, 9);
    m_pScrollNumFirtst->setRegionText("hour");

    m_pScrollNumSecond = new ScrollNumberWidget(this);
    m_pScrollNumSecond->setRange(0, 59);
    m_pScrollNumSecond->setRegionText("min");

    m_pScrollNumThird = new ScrollNumberWidget(this);
    m_pScrollNumThird->setRange(0, 59);
    m_pScrollNumThird->setRegionText("sec");

    m_pHMainLayout = new QHBoxLayout(this);
    m_pHMainLayout->addWidget(m_pScrollNumFirtst);
    m_pHMainLayout->addWidget(m_pScrollNumSecond);
    m_pHMainLayout->addWidget(m_pScrollNumThird);

    setLayout(m_pHMainLayout);
}
