#include <QMessageBox>
#include <QBoxLayout>
#include <QDesktopWidget>
#include <QTimer>
#include <QTimerEvent>
#include <QMouseEvent>
#include <QDebug>

#include "playerwidget.h"
#include "ui_playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget)
{
    ui->setupUi(this);

    // init player
    m_player = new QtAV::AVPlayer(this);
    m_vo = new QtAV::VideoOutput(this);
    if (!m_vo->widget()) {
        QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
        return;
    }
    m_player->setRenderer(m_vo);

    // init signal
    // 需要使用qt4的方式连接
    connect(m_vo,  SIGNAL(videoFrameSizeChanged()), this, SLOT(onVideoFrameSizeChanged()));
    connect(m_player, SIGNAL(bufferProgressChanged(qreal)), this, SLOT(onBufferProgressChanged(qreal)));
    connect(m_player, SIGNAL(mediaStatusChanged(QtAV::MediaStatus)), this, SLOT(onMediaStatusChanged(QtAV::MediaStatus)));
    connect(m_player, SIGNAL(stateChanged(QtAV::AVPlayer::State)), this, SLOT(onStateChanged(QtAV::AVPlayer::State)));

    // init ui
    QVBoxLayout *rootVerticalLayout = new QVBoxLayout(this);
    rootVerticalLayout->setSpacing(0);
    rootVerticalLayout->setObjectName(QString::fromUtf8("rootVerticalLayout"));
    rootVerticalLayout->setContentsMargins(0, 0, 0, 0);
    rootVerticalLayout->addWidget(m_vo->widget());

    ui->playBtn->show();
    ui->pauseBtn->hide();
    ui->playSlider->hide();

    m_defaultSize = size();
    updateControlPos();

    m_vo->widget()->setMouseTracking(true);
    ui->controlWidget->setMouseTracking(true);
    setMouseTracking(true);
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}

void PlayerWidget::resizeEvent(QResizeEvent *event)
{
    updateControlPos();
}

void PlayerWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_controlTimer) {
        stopControlTimer();
        ui->controlWidget->hide();
    }
}

void PlayerWidget::mousePressEvent(QMouseEvent *event)
{
    if (!isFullScreen()) {
        m_lastPressed = event->pos();
    }
}

void PlayerWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_lastPressed = QPoint(0, 0);
}

void PlayerWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_lastPressed.isNull()) {
        QPoint distance = event->pos() - m_lastPressed;
        QPoint dstPos = pos() + distance;
        move(dstPos);
        return;
    }
    ui->controlWidget->raise();
    ui->controlWidget->show();
    if (childAt(event->pos()) == ui->controlWidget) {
        stopControlTimer();
    } else {
        startControlTimer();
    }
}

void PlayerWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}

void PlayerWidget::updateControlPos()
{
    const int hPanding = 50;
    const int bottomPanding = 25;
    ui->controlWidget->move(hPanding, height() - bottomPanding - ui->controlWidget->height());
    ui->controlWidget->resize(width() - hPanding * 2, ui->controlWidget->height());
}

void PlayerWidget::startControlTimer()
{
    stopControlTimer();
    m_controlTimer = startTimer(1000);
}

void PlayerWidget::stopControlTimer()
{
    if (0 != m_controlTimer) {
        killTimer(m_controlTimer);
        m_controlTimer = 0;
    }
}

void PlayerWidget::on_playBtn_clicked()
{
    if (m_player->isPaused()) {
        m_player->pause(false);
        return;
    }    
    m_player->play("C:/Users/admin/Desktop/test.mp4");
}

void PlayerWidget::on_pauseBtn_clicked()
{
    m_player->pause();
    qDebug() << m_vo->videoFrameSize();
}

void PlayerWidget::onVideoFrameSizeChanged()
{
    if (!m_vo->videoFrameSize().isEmpty()) {
        int width = m_vo->videoFrameSize().width();
        int height = m_vo->videoFrameSize().height();

        QDesktopWidget* desktop = QApplication::desktop();
        if (desktop) {
            QRect screenRect = desktop->availableGeometry();
            width = qMin(screenRect.width(), width);
            height = qMin(screenRect.height(), height);
            move(screenRect.center() - QRect(0, 0, width, height).center());
        }

        resize(width, height);
    }
}

void PlayerWidget::onBufferProgressChanged(qreal progress)
{
    //qDebug() << ">>>>>>>>>>" << progress;
}

void PlayerWidget::onMediaStatusChanged(QtAV::MediaStatus status)
{
    //qDebug() << ">>>>>>>>>>" << status;
    if (QtAV::EndOfMedia == status) {
        resize(m_defaultSize);
    }
    //updateUI();
}

void PlayerWidget::onStateChanged(QtAV::AVPlayer::State state)
{
    if (m_player->isPlaying() && !m_player->isPaused()) {        
        ui->pauseBtn->show();
        ui->playBtn->hide();
    } else {        
        ui->playBtn->show();
        ui->pauseBtn->hide();
    }
}

void PlayerWidget::on_preBtn_clicked()
{

}
