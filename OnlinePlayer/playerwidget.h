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
    void timerEvent(QTimerEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void updateControlPos();
    void startControlTimer();
    void stopControlTimer();

private slots:
    void on_playBtn_clicked();
    void on_pauseBtn_clicked();
    void onVideoFrameSizeChanged();
    void onBufferProgressChanged(qreal progress);
    void onMediaStatusChanged(QtAV::MediaStatus status);
    void onStateChanged(QtAV::AVPlayer::State state);

    void on_preBtn_clicked();

private:
    Ui::PlayerWidget *ui;

    QtAV::VideoOutput *m_vo = Q_NULLPTR;
    QtAV::AVPlayer *m_player = Q_NULLPTR;

    QSize m_defaultSize;
    int m_controlTimer = 0;

    QPoint m_lastPressed;
};

#endif // PLAYERWIDGET_H
