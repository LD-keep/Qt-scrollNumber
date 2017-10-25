
#include <QApplication>
#include <QCalendarWidget>

#include "scrollnumberwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ScrollNumberWidget widget;
    widget.setFixedSize(80, 170);
    widget.setRange(1, 31);
    widget.show();

    app.exec();
    return 0;
}
