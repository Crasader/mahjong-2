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
#include <SRMahjong.h>
#include <SRMahjongPool.h>


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

        // ������ҳ�������Ϊ�ź�
        connect(seatWidget_[i],SIGNAL(sigAction(enDirection, int, BYTE)),
                this,SLOT(onPlayerAction(enDirection, int, BYTE)));
    }

    // ��ʼ����λ�������Ĳ���
    initSeatLayout();


    connect(hallWidget_,SIGNAL(sigDealCard(enDirection,BYTE)),
            this,SLOT(onDealCard(enDirection,BYTE)));

//    connect(this,SIGNAL(sigDealCard(enDirection,BYTE)),
//            )

}

void SRMahjongTableWidget::onOpen() {
    // ϴ��
    hallWidget_->onShuffle();

    // ����
    SRInvisibleMahjongPool* invisible_pool = hallWidget_->getInvisibleMahjongPool();
    SRVisibleMahjongPool* visible_pool = hallWidget_->getVisibleMahjongPool();
    for(int drc = (int)enDirection::South; drc <= enDirection::East; ++drc) {
        robot_[drc]->setInvisibleMahjongPool(invisible_pool);
        robot_[drc]->setVisibleMahjongPool(visible_pool);

        // ��ʼ���齫����
        unsigned char temp_card_data[MAX_COUNT] = {};
        for (int i = 0; i < 13; ++i)
            temp_card_data[i] = invisible_pool->pop_front();

        SRMahjong* temp_mj = new SRMahjong(temp_card_data, 13);

        // ���齫���õ�������
        robot_[drc]->setMahjong((enDirection)drc, temp_mj);
        seatWidget_[drc]->setMahjong(temp_mj);
    }

    // �û�����
    hallWidget_->onDealCard(enDirection::South,1);

    // �����û�����
    emit sigAskPlayerOutCard(enDirection::South);

}

void SRMahjongTableWidget::onPlayerAction(enDirection direction, int action, BYTE data)
{

}


void SRMahjongTableWidget::onDealCard(enDirection direction, BYTE data)
{
    seatWidget_[direction]->touchCard(data);
}

void SRMahjongTableWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,
                           &opt, &p, this);

    // �����ӽ���
    for (auto seat : seatWidget_)
        seat->update();
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


