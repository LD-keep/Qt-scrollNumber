#include "scrollnumberwidget.h"

#include <QLabel>
#include <QPoint>
#include <QMouseEvent>

#include <QDebug>

ScrollNumberWidget::ScrollNumberWidget(QWidget *parent)
    : QWidget(parent)
{   
    setObjectName("ScrollNumberWidget");
    m_iMaxValue = 0;
    m_iMinValue = 0;
    m_iIndex = 0;
    m_listLabel.clear();

    m_strNormal = "QLabel{font: 22px; color: green;}";
    m_strSelect = "QLabel{font: 30px; color: darkYellow;}";

    initUI();
}

ScrollNumberWidget::~ScrollNumberWidget()
{
    destroyList();
}

void ScrollNumberWidget::setRange(int min, int max)
{
    setRange(min, max, min);
}

void ScrollNumberWidget::setRange(int min, int max, int initValue)
{
    m_iMaxValue = max;
    m_iMinValue = min;
    m_iIndex = initValue;

    showLabel(m_iIndex, QPoint(0, 0));
}

QString ScrollNumberWidget::value()
{
    if (m_listLabel.isEmpty())
    {
        return QString();
    }

    return m_listLabel.at(m_iIndex)->text();
}

void ScrollNumberWidget::setRegionText(QString text)
{
    m_pLbSelectRegion->setText(text);
}

void ScrollNumberWidget::setScrollNumberStyle(QString strNormal, QString strSelect)
{
    m_strNormal = strNormal;
    m_strSelect = strSelect;
}

void ScrollNumberWidget::setSelectRectStyle(QString strStyle)
{
    m_pLbSelectRegion->setStyleSheet(strStyle);
}

void ScrollNumberWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    m_posPrev = event->pos();
}

void ScrollNumberWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    reviseCalculatePos();
    m_posPrev = event->pos();
}

void ScrollNumberWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    moveLabel(event->pos());
    m_posPrev = event->pos();
}

void ScrollNumberWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    if (m_pLbSelectRegion->isHidden())
    {
        m_pLbSelectRegion->setFixedSize(width(), ItemHeight);
        m_pLbSelectRegion->move(0, (height() - ItemHeight)/2);
        m_pLbSelectRegion->show();
        refreshScrollNumberStyle();
        reviseCalculatePos();
    }
}

void ScrollNumberWidget::initUI()
{
    QLabel *pLbItem = NULL;
    for (int i = 0; i < VisibleLabelNum; ++i)
    {
        pLbItem = new QLabel(this);
        pLbItem->setAlignment(Qt::AlignCenter);
        pLbItem->setFixedSize(ItemWidth, ItemHeight);
        pLbItem->setStyleSheet(m_strNormal);
        m_listLabel.append(pLbItem);
    }

    m_pLbSelectRegion = new QLabel(this);
    m_pLbSelectRegion->setStyleSheet("QLabel{border: 1px solid gray; font: 10px; color: black;}");
    m_pLbSelectRegion->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    m_pLbSelectRegion->setText("hour");
    m_pLbSelectRegion->hide();
}

void ScrollNumberWidget::destroyList()
{
    if (!m_listLabel.isEmpty())
    {
        qDeleteAll(m_listLabel.begin(), m_listLabel.end());
        m_listLabel.clear();
    }
}

void ScrollNumberWidget::moveLabel(QPoint pos)
{
    QPoint directionPos = pos - m_posPrev;
    if (directionPos.y() > - MoveMinOffset
        && directionPos.y() < MoveMaxOffset)
    {
        return;
    }

    bool directionFlag = false;
    if (directionPos.y() > 0)
    {
        directionFlag = true;
    }

    int size = m_listLabel.size();
    int i = 0;
    int y = 0;
    QLabel *pLbItem = NULL;
    for (directionFlag ? i = size - 1 : i = 0; directionFlag ? i >= 0 : i < size; directionFlag ? --i : ++i)
    {
        pLbItem = m_listLabel.at(i);
        y = pLbItem->pos().y() + directionPos.y();
        pLbItem->move(0, y);
//        qDebug() << "-------- item pos --- >" << pLbItem->pos();
    }

//    qDebug() << "--- start end pos ---"
//             << m_listLabel.at(m_iIndex)->pos() <<  m_iIndex << m_listLabel.at(m_iIndex)->text().toInt();;

    if (directionFlag)
    {
        pLbItem = m_listLabel.at(0);
        if (pLbItem->pos().y() > 0)
        {
            showLabel(pLbItem->text().toInt(), pLbItem->pos());
        }
    }
    else
    {
        pLbItem = m_listLabel.at(VisibleLabelNum-1);
        if (pLbItem->pos().y() + pLbItem->height() - height() < 0)
        {
            showLabel(pLbItem->text().toInt(), pLbItem->pos());
        }
    }

    refreshScrollNumberStyle();
}

void ScrollNumberWidget::showLabel(int value, QPoint pos)
{

    //show prev page
    updateLabelAttributes(0, 4, value, -6, -4, pos);
//    pLbItem = m_listLabel.at(0);
//    pLbItem->move(QPoint(0, pos.y() + -4*ItemHeight));
//    pLbItem->setText(QString::number(calculateValue(value, -6)));

//    pLbItem = m_listLabel.at(1);
//    pLbItem->move(QPoint(0, pos.y() + -3*ItemHeight));
//    pLbItem->setText(QString::number(calculateValue(value, -5)));

//    pLbItem = m_listLabel.at(2);
//    pLbItem->move(QPoint(0, pos.y() + -2*ItemHeight));
//    pLbItem->setText(QString::number(calculateValue(value, -4)));

//    pLbItem = m_listLabel.at(3);
//    pLbItem->move(QPoint(0, pos.y() + -1*ItemHeight));
//    pLbItem->setText(QString::number(calculateValue(value, -3)));

    //show curr page
    updateLabelAttributes(4, 5, value, -2, 0, pos);
//    pLbItem = m_listLabel.at(4);
//    pLbItem->move(pos);
//    pLbItem->setText(QString::number(calculateValue(value, -2)));

//    pLbItem = m_listLabel.at(5);
//    pLbItem->move(QPoint(0, pos.y() + ItemHeight));
//    pLbItem->setText(QString::number(calculateValue(value, -1)));

//    pLbItem = m_listLabel.at(6);
//    pLbItem->move(QPoint(0, pos.y() + 2*ItemHeight));
//    pLbItem->setText(QString::number(calculateValue(value, 0)));

//    pLbItem = m_listLabel.at(7);
//    pLbItem->move(QPoint(0, pos.y() + 3*ItemHeight));
//    pLbItem->setText(QString::number(calculateValue(value, 1)));

//    pLbItem = m_listLabel.at(8);
//    pLbItem->move(QPoint(0, pos.y() + 4*ItemHeight));
//    pLbItem->setText(QString::number(calculateValue(value, 2)));

    //show next page
    updateLabelAttributes(9, 3, value, 3, 5, pos);
//    pLbItem = m_listLabel.at(9);
//    pLbItem->move(QPoint(0, pos.y() + 5*ItemHeight));
//    pLbItem->setText(QString::number(calculateValue(value, 3)));

//    pLbItem = m_listLabel.at(10);
//    pLbItem->move(QPoint(0, pos.y() + 6*ItemHeight));
//    pLbItem->setText(QString::number(calculateValue(value, 4)));

//    pLbItem = m_listLabel.at(11);
//    pLbItem->move(QPoint(0, pos.y() + 7*ItemHeight));
//    pLbItem->setText(QString::number(calculateValue(value, 5)));
}

void ScrollNumberWidget::updateLabelAttributes(int start, int num, int value,
                                               int valOffset, int offset, QPoint pos)
{
    int size = start + num;
    QLabel *pLbItem = NULL;
    QString text;
    for (int i = start; i < size; ++i)
    {
        pLbItem = m_listLabel.at(i);
        if (NULL == pLbItem)
        {
            continue;
        }

        pLbItem->move(QPoint(0, pos.y() + offset*ItemHeight));
        text = QString::number(calculateValue(value, valOffset));
        if (1 == text.size())
        {
            text.insert(0, "0");
        }
        pLbItem->setText(text);
        pLbItem->raise();
        ++offset;
        ++valOffset;
    }
}

int ScrollNumberWidget::calculateValue(int indexVal, int offset)
{
    int value = indexVal + offset;
    if (0 == value)
    {
        value = m_iMaxValue;
        if (0 == m_iMinValue)
        {
            value = m_iMinValue;
        }
    }
    else if (value < 0)
    {
        value = value + m_iMaxValue + 1;
    }
    else if (value > m_iMaxValue)
    {
        value = value - m_iMaxValue + m_iMinValue - 1;
    }
    else if (value < m_iMinValue)
    {
        value = m_iMaxValue + (offset + (indexVal - m_iMinValue)) + 1;
    }

    return value;
}

void ScrollNumberWidget::refreshScrollNumberStyle()
{
    int size = m_listLabel.size();
    QLabel *pLbItem = NULL;
    QSize rectSize(ItemWidth, ItemHeight);
    QRect regionRect(m_pLbSelectRegion->pos(), rectSize);
    QFontMetrics fontMet(m_listLabel.at(0)->font());
    for (int i = 0; i < size; ++i)
    {
        pLbItem = m_listLabel.at(i);
        QRect itemRect(pLbItem->pos(), rectSize);
        QRect interRect = regionRect.intersected(itemRect);
        if (interRect.y() > 0)
        {
            qDebug() << "---- rect ---" << i << interRect << pLbItem->text();
            if (regionRect.contains(0, pLbItem->pos().y() + ItemFontSpacing)
                    || regionRect.contains(0, pLbItem->pos().y() + fontMet.height() + ItemFontSpacing))
            {
                m_mapInterRect.insert(i, interRect.height());
                m_iIndex = i;
                pLbItem->setStyleSheet(m_strSelect);
            }
            else
            {
                pLbItem->setStyleSheet(m_strNormal);
            }
        }
        else
        {
            pLbItem->setStyleSheet(m_strNormal);
            if (m_mapInterRect.find(i) != m_mapInterRect.end())
            {
                m_mapInterRect.remove(i);
            }
        }
    }
}

void ScrollNumberWidget::reviseCalculatePos()
{
    if (m_mapInterRect.isEmpty())
    {
        return;
    }

    int offsetY = 0;
    int size = m_mapInterRect.size();
    QLabel *pLbItem = NULL;
    if (1 == size)
    {
        m_iIndex = m_mapInterRect.begin().key();
    }
    else
    {
        QMap<int, int>::iterator iter = m_mapInterRect.begin();
        ++iter;
        m_iIndex = iter.key();
        if (m_mapInterRect.begin().value() > iter.value())
        {
            m_iIndex = m_mapInterRect.begin().key();
        }
    }

    offsetY = m_pLbSelectRegion->pos().y() - m_listLabel.at(m_iIndex)->pos().y();
    for (int i = 0; i < m_listLabel.size(); ++i)
    {
        pLbItem = m_listLabel.at(i);
        pLbItem->move(0, pLbItem->pos().y() + offsetY);
        if (m_iIndex == i)
        {
            pLbItem->setStyleSheet(m_strSelect);
        }
        else
        {
            pLbItem->setStyleSheet(m_strNormal);
        }
    }

    m_mapInterRect.clear();
    emit valueChange(m_listLabel.at(m_iIndex)->text().toInt());
}
