#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QtAV>

namespace Ui {
class PlayerWidget;
}

class PlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    ~PlayerWidget();

private:
    Ui::PlayerWidget *ui;

    QtAV::VideoOutput *m_vo = Q_NULLPTR;
    QtAV::AVPlayer *m_player = Q_NULLPTR;
};

#endif // PLAYERWIDGET_H
