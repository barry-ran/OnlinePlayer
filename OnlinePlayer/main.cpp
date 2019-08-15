#include <QApplication>
#include <QtAVWidgets>

#include "mainwidget.h"
#include "playerwindow.h"
#include "framelesswindowhelper/framelesswindowhelper.h"


int main(int argc, char *argv[])
{
    QtAV::Widgets::registerRenderers();
    QApplication a(argc, argv);

    FramelessWindowHelper<PlayerWindow> player;
    player.setResizeable(false);
    player.resize(800, 600);
    player.show();
    return a.exec();
}
