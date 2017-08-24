#include "srmahjongtablewidget.h"
#include "srmahjonghallwidget.h"
#include "srmahjongseatwidget.h"

#include <time.h>

#include <QStyleOption>
#include <QPainter>
#include <QGridLayout>
#include <QDebug>

#include <srmjglobal.h>
#include <srmjrobot.h>


SRMahjongTableWidget::SRMahjongTableWidget(QWidget *parent) : QWidget(parent)
{
    hallWidget_ = new SRMahjongHallWidget;
    for (int i =0; i < sizeof(seatWidget_)/ sizeof(seatWidget_[0]); ++i)
        seatWidget_[i] = new SRMahjongSeatWidget;

    // ���û����˵�λ��
    for(int i = (int)enDirection::South; i <= (int)enDirection::East; ++i) {
        robot_[i] = new SRRobot();
        seatWidget_[i]->setDirection((enDirection)i);
        seatWidget_[i]->setRobot(robot_[i]);
    }

    // ��ʼ����λ�������Ĳ���
    initSeatLayout();


    connect(hallWidget_,SIGNAL(sigDealCard(enDirection,BYTE)),
            this,SLOT(onDealCard(enDirection,BYTE)));


}

void SRMahjongTableWidget::onOpen() {
    // ϴ��
    hallWidget_->onShuffle();

    // ����
    SRInvisibleMahjongPool* temp = hallWidget_->getInvisibleMahjongPool();
    SRVisibleMahjongPool* temp2 = hallWidget_->getVisibleMahjongPool();
    for(int i = 0; i < 4; ++i) {
        robot_[i]->setInvisibleMahjongPool(temp);
        robot_[i]->setVisibleMahjongPool(temp2);
    }
    hallWidget_->onDealCard(enDirection::South,13);
    hallWidget_->onDealCard(enDirection::West,13);
    hallWidget_->onDealCard(enDirection::North,13);
    hallWidget_->onDealCard(enDirection::East,13);

    // �û�����
    hallWidget_->onDealCard(enDirection::South,1);

    // �����û�����

}

void SRMahjongTableWidget::onPlayerAction(enDirection direction, int action) {

}

void SRMahjongTableWidget::onDealCard(enDirection direction, BYTE data)
{
    seatWidget_[direction]->onTouchCard(&data, 1);
}

void SRMahjongTableWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,
                           &opt, &p, this);
}


void SRMahjongTableWidget::initSeatLayout(void) {

    QGridLayout* layout = new QGridLayout();

    // Ϊÿ��λ�����÷�λ����
    for(int i = (int)enDirection::South; i <= (int)enDirection::East; ++i) {
        enDirection drc = seatWidget_[i]->getDirection();
        switch (drc) {
        case enDirection::North:
            layout->addWidget(seatWidget_[i],0,1,1,8);  // ��
            break;
        case enDirection::West:
            layout->addWidget(seatWidget_[i],1,0,8,1);  // ��
            break;
        case enDirection::East:
            layout->addWidget(seatWidget_[i],1,9,8,1);  // ��
            break;
        case enDirection::South:
            layout->addWidget(seatWidget_[i],9,1,1,8);  // ��
            break;
        default:
            break;
        }
    }

    layout->addWidget(hallWidget_,1,1,8,8);     // ��

    setLayout(layout);
}


