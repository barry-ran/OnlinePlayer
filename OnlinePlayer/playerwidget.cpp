#include <QMessageBox>
#include <QBoxLayout>
#include <QDesktopWidget>
#include <QDebug>

#include "playerwidget.h"
#include "ui_playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget)
{
    ui->setupUi(this);

    QVBoxLayout *rootVerticalLayout = new QVBoxLayout(this);
    rootVerticalLayout->setSpacing(0);
    rootVerticalLayout->setObjectName(QString::fromUtf8("rootVerticalLayout"));
    rootVerticalLayout->setContentsMargins(0, 0, 0, 0);

    m_player = new QtAV::AVPlayer(this);
    m_vo = new QtAV::VideoOutput(this);
    if (!m_vo->widget()) {
        QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
        return;
    }
    m_vo->widget()->setWindowFlag(Qt::WindowTransparentForInput);
    m_player->setRenderer(m_vo);
    rootVerticalLayout->addWidget(m_vo->widget());

    ui->controlWidget->raise();
    ui->controlWidget->show();
    updateControlPos();

    // 需要使用qt4的方式连接
    connect(m_vo,  SIGNAL(videoFrameSizeChanged()), this, SLOT(onVideoFrameSizeChanged()));
    connect(m_player, SIGNAL(bufferProgressChanged(qreal)), this, SLOT(onBufferProgressChanged(qreal)));
    connect(m_player, SIGNAL(mediaStatusChanged(QtAV::MediaStatus)), this, SLOT(onMediaStatusChanged(QtAV::MediaStatus)));
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}

void PlayerWidget::resizeEvent(QResizeEvent *event)
{
    updateControlPos();
}

void PlayerWidget::updateControlPos()
{
    const int hPanding = 100;
    const int bottomPanding = 50;
    ui->controlWidget->move(hPanding, height() - bottomPanding - ui->controlWidget->height());
    ui->controlWidget->resize(width() - hPanding * 2, ui->controlWidget->height());
}

void PlayerWidget::on_playBtn_clicked()
{
    m_player->play("C:/Users/admin/Desktop/test.mp4");
}

void PlayerWidget::on_pauseBtn_clicked()
{
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
    qDebug() << ">>>>>>>>>>" << status;
}
