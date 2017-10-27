
#include <QApplication>
#include <QCalendarWidget>

#include "datetimeselectwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DateTimeSelectWidget widget;
    widget.setObjectName("DateTimeSelectWidget");
    widget.setAttribute(Qt::WA_StyledBackground);
    widget.setFixedSize(300, 200);
    widget.setStyleSheet("QWidget#DateTimeSelectWidget{border-image: url(D:/workspace/project/testqml/resource/image/50a2fdff45d7a.png)}");
    widget.show();

    app.exec();
    return 0;
}
