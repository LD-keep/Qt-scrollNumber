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
    m_pScrollNumFirtst->setRange(2000, 2100);
    m_pScrollNumFirtst->setRegionText("year");

    m_pScrollNumSecond = new ScrollNumberWidget(this);
    m_pScrollNumSecond->setRange(1, 12);
    m_pScrollNumSecond->setRegionText("mon");

    m_pScrollNumThird = new ScrollNumberWidget(this);
    m_pScrollNumThird->setRange(1, 31);
    m_pScrollNumThird->setRegionText("day");

    m_pHMainLayout = new QHBoxLayout(this);
    m_pHMainLayout->addWidget(m_pScrollNumFirtst);
    m_pHMainLayout->addWidget(m_pScrollNumSecond);
    m_pHMainLayout->addWidget(m_pScrollNumThird);

    setLayout(m_pHMainLayout);
}
