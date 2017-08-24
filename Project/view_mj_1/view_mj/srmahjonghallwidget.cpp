#include "srmahjonghallwidget.h"

#include <time.h>

#include <QStyleOption>
#include <QPainter>

#include <srmjglobal.h>
#include <SRMahjongPool.h>


SRMahjongHallWidget::SRMahjongHallWidget(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("QWidget{background-color:white;}" \
                  "QWidget:hover{border: 1px solid black;}");

    invisibleMahjongPool_ = new SRInvisibleMahjongPool();
    visibleMahjongPool_ = new SRVisibleMahjongPool();

}

void SRMahjongHallWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,
                           &opt, &p, this);

}




void SRMahjongHallWidget::onShuffle() {

    // ��������
    memset(cbCardDataArray_,0,sizeof(cbCardDataArray_));

    // ��ʼ������
    srand(time(0));

    // ����׼��
    BYTE cbMaxCount = MAX_REPERTORY;
    BYTE cbCardDataTemp[sizeof(g_cbCardDataArray)];
    memcpy(cbCardDataTemp, g_cbCardDataArray, sizeof(g_cbCardDataArray));

    // �����˿�
    BYTE cbRandCount=0,cbPosition=0;
    do {
        cbPosition = rand() % (cbMaxCount-cbRandCount);
        cbCardDataArray_[cbRandCount++] = cbCardDataTemp[cbPosition];
        cbCardDataTemp[cbPosition] = cbCardDataTemp[cbMaxCount-cbRandCount];
    } while (cbRandCount < cbMaxCount);

    // ���õ���ǽ֮��
    invisibleMahjongPool_->setMahjongPoolData(cbCardDataArray_, cbRandCount);
    return;
}

void SRMahjongHallWidget::onDealCard(enDirection direction, BYTE count)
{
    for (BYTE i = 0; i < count; ++i) {
        emit sigDealCard(direction, invisibleMahjongPool_->pop_front());
    }
}

void SRMahjongHallWidget::onOutCardToVisibleMahjongPool(unsigned char card)
{
    visibleMahjongPool_->push_back(card);
}
