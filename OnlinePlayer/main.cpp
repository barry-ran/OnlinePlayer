#include <QApplication>
#include <QtAVWidgets>

#include "playerwidget.h"
#include "framelesswindowhelper/framelesswindowhelper.h"


int main(int argc, char *argv[])
{
    QtAV::Widgets::registerRenderers();
    QApplication a(argc, argv);

    FramelessWindowHelper<PlayerWidget> player;
    player.setResizeable(false);
    player.setTitleHeight(player.height());
    player.show();
    return a.exec();
}
