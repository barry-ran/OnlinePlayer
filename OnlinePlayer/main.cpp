#include <QApplication>
#include <QtAVWidgets>

#include "playerwidget.h"
#include "framelesswindowhelper/framelesswindowhelper.h"


int main(int argc, char *argv[])
{
    QtAV::Widgets::registerRenderers();
    QApplication a(argc, argv);

    FramelessWindowHelper<PlayerWidget> player;
    player.setTitleHeight(0);
    player.show();
    return a.exec();
}
