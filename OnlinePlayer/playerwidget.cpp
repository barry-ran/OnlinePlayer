#include <QMessageBox>

#include "playerwidget.h"
#include "ui_playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget)
{
    ui->setupUi(this);

    m_player = new QtAV::AVPlayer(this);
    m_vo = new QtAV::VideoOutput(this);
    if (!m_vo->widget()) {
        QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
        return;
    }
    m_vo->widget()->setWindowFlag(Qt::WindowTransparentForInput);
    m_player->setRenderer(m_vo);
    ui->rootVerticalLayout->addWidget(m_vo->widget());
    //m_player->play("C:/Users/admin/Desktop/test.mp4");
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}
