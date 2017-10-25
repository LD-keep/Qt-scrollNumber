#ifndef SCROLLNUMBERWIDGET_H
#define SCROLLNUMBERWIDGET_H

#include <QWidget>
#include <QMap>

class QLabel;
class QPoint;

const int ItemWidth = 80;
const int ItemHeight = 38;
const int VisibleLabelNum = 12;
const int ItemFontSpacing = 5;
const int MoveMinOffset = -3;
const int MoveMaxOffset = 3;

class ScrollNumberWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScrollNumberWidget(QWidget *parent = 0);
    ~ScrollNumberWidget();

    QString value();

    void setRange(int min, int max);

    void setRegionText(QString text);
    void setScrollNumberStyle(QString strNormal, QString strSelect);
    void setSelectRectStyle(QString strStyle);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void showEvent(QShowEvent *event);

private:
    void initUI();
    void destroyList();
    void moveLabel(QPoint pos);
    void showLabel(int value, QPoint pos);
    void updateLabelAttributes(int start, int num, int value, int valOffset, int offset, QPoint pos);
    int calculateValue(int indexVal, int offset);
    void refreshScrollNumberStyle();
    void reviseCalculatePos();

private:
    QLabel *m_pLbSelectRegion;
    QPoint m_posPrev;
    QString m_strNormal;
    QString m_strSelect;
    QString m_strRegionStyle;

    int m_iIndex;
    int m_iMaxValue;
    int m_iMinValue;
    QList<QLabel*> m_listLabel;
    QMap<int, int> m_mapInterRect;

};

#endif // SCROLLNUMBERWIDGET_H
