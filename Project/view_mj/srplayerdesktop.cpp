#include "srplayerdesktop.h"
#include "srplayermodel.h"
#include "srcardmodel.h"
#include "srcommon.h"

#include <iomanip>
#include <iostream>
#include <algorithm>

#include <QDebug>
#include <QPushButton>


SRPlayerDesktop::SRPlayerDesktop(QWidget *parent) : QWidget(parent)
{
    model_ = new SRPlayerModel;
    layout_ = new QBoxLayout(QBoxLayout::LeftToRight);
    cardModel_ = new SRCardModel;

    for(int i = 0; i < MAX_COUNT; ++i) {
        listButton_.push_back(new QPushButton());
        layout_->addWidget(listButton_.at(i));
        listButton_.at(i)->setFixedSize(50,75);
    }

    setLayout(layout_);
}

void SRPlayerDesktop::setDirection(enDirection _direction) {
     model_->setDirection(_direction);

     if(_direction == enDirection::South || _direction == enDirection::North) {
        layout_->setDirection(QBoxLayout::LeftToRight);
     }
     else if (_direction == enDirection::West ||_direction == enDirection::East) {
        layout_->setDirection(QBoxLayout::TopToBottom);
     }

}

enDirection SRPlayerDesktop::getDirection()
{
    return model_->getDirection();
}

void SRPlayerDesktop::onDealCard(enDirection direction, BYTE *data, BYTE count)
{
    if (direction != model_->getDirection())
        return;

    // ��һ�ηַ�
    if (count == MAX_COUNT)
        cardModel_->setCardData(data,count);
    else if (count == 1)
        onPlayState(*data);
    else
        qDebug() << "????";


}

void SRPlayerDesktop::onPlayState(BYTE data)
{
    BYTE out_card = data;
    // ��������

    // �滻��Ҫ�������

    // ���ͳ���֪ͨ
    emit outCard(getDirection(),out_card);
}

void SRPlayerDesktop::onOtherPlayState(enDirection direction, BYTE data)
{
    if (direction == getDirection())
        return;

    // ���������˵ĳ��ƽ׶�
    qDebug() << QString(QStringLiteral("%1�ڷ���%2���� %3")).arg(sr::getDirectionNameQ(getDirection()))
                .arg(sr::getDirectionNameQ(direction)).arg(sr::convertCard(data));

    // �����������ź�
}


const char* const SRPlayerDesktop::getDirectionName()
{
    switch (model_->getDirection()) {
    case ::enDirection::South:
        return "λ��";
    case ::enDirection::West:
        return "λ��";
    case ::enDirection::North:
        return "λ��";
    case ::enDirection::East:
        return "λ��";
    default:
        return "????";
    }
}


void SRPlayerDesktop::paintEvent(QPaintEvent *event)
{
    for(int i = 0; i < MAX_COUNT; ++i)
        listButton_.at(i)->setText(sr::convertCard(cardModel_->getCardData(i)));

    QWidget::paintEvent(event);
}

