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

protected:
    void resizeEvent(QResizeEvent *event) override;

    void updateControlPos();


private slots:
    void on_playBtn_clicked();

    void on_pauseBtn_clicked();

    void onVideoFrameSizeChanged();
    void onBufferProgressChanged(qreal progress);
    void onMediaStatusChanged(QtAV::MediaStatus status);

private:
    Ui::PlayerWidget *ui;

    QtAV::VideoOutput *m_vo = Q_NULLPTR;
    QtAV::AVPlayer *m_player = Q_NULLPTR;
};

#endif // PLAYERWIDGET_H
