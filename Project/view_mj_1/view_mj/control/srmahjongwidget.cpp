#include "srmahjongwidget.h"
#include <QDebug>
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>

#include <SRMahjong.h>

SRMahjongWidget::SRMahjongWidget(QWidget *parent)
    : QWidget(parent) {
    setStyleSheet("QWidget{background-color:orange;}" \
                  "QWidget:hover{border: 3px solid black;}");

    setMaximumSize(55,74);
    cardData_ = 0;
}

bool SRMahjongWidget::operator<(const SRMahjongWidget &other)
{
    return (this->cardData_ < other.cardData_);
}

bool SRMahjongWidget::operator>(const SRMahjongWidget &other)
{
    return (this->cardData_ > other.cardData_);
}

bool SRMahjongWidget::operator==(const SRMahjongWidget &other)
{
    return (this->cardData_ == other.cardData_);
}


void SRMahjongWidget::onModifyData(unsigned char data)
{
    cardData_ = data;
    info_ = convertToText(data);
}

void SRMahjongWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,
                           &opt, &p, this);

    p.drawText(0,0,width(),height(),Qt::AlignCenter,info_);


}

void SRMahjongWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit sigDoubleClick(this);
        qDebug() <<  info_ << QStringLiteral("��˫��");
    }
}

QString SRMahjongWidget::convertToText(unsigned char data)
{

    if (!isValidCard(data))
        return "??? ";


    unsigned char card_type = data & 0xF0;

    unsigned char card_num = data & 0x0F;

    QString name;

    switch (card_type) {
    case 0x00:
        name = QStringLiteral("��");
        break;
    case 0x10:
        name = QStringLiteral("��");
        break;
    case 0x20:
        name = QStringLiteral("ͬ");
        break;
    case 0x30: {
        name = QStringLiteral("��");
        if (card_num == 1)
            name = QStringLiteral("��") + name;
        else if (card_num == 2)
            name = QStringLiteral("��") + name;
        else if (card_num == 3)
            name = QStringLiteral("��") + name;
        else if (card_num == 4)
            name = QStringLiteral("��") + name;
        else if (card_num == 5)
            name = QStringLiteral("��");
        else if (card_num == 6)
            name = QStringLiteral("��");
        else if (card_num == 7)
            name = QStringLiteral("��");
        return name;
    }
    default:
        break;
    }

    name = QString::number(card_num) + name;

    return name;
}
