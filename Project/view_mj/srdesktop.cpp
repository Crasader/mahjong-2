#include "srdesktop.h"
#include <time.h>
SRDesktop::SRDesktop(QWidget *parent) : QWidget(parent) {
    memset(cbCardDataArray_,0,sizeof(cbCardDataArray_));
}

void SRDesktop::onShuffle() {
    // ��������
    memset(cbCardDataArray_,0,sizeof(cbCardDataArray_));
    index_ = 0;

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

    return;
}

void SRDesktop::onDealCard(enDirection direction, BYTE count) {
    if ((index_ + count) >= MAX_REPERTORY)
        emit emDealCard(direction,&cbCardDataArray_[index_],MAX_REPERTORY-index_);
    else
        emit emDealCard(direction,&cbCardDataArray_[index_],count);

    index_ += count;
}
