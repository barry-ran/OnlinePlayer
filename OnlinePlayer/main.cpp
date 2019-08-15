#include <QApplication>
#include <QtAVWidgets>

#include "mainwidget.h"
#include "playerwindow.h"


int main(int argc, char *argv[])
{
    QtAV::Widgets::registerRenderers();
    QApplication a(argc, argv);
    PlayerWindow player;
    player.show();
    player.resize(800, 600);
    return a.exec();
}
