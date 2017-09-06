// SRMahjongRobot.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "SRMahjong.h"
#include "SRMahjongRobot.h"
#include "SRMahjongAnalysis.h"

#include <iostream>

#include <time.h>


// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� SRMahjongRobot.h
SRMahjongRobot::SRMahjongRobot(void) {
	direction_ = enDirection::None;
	memset(enemyDirection_, 0, sizeof(enemyDirection_));
	roundNumber_ = 0;

	analysisLogic_ = new SRMahjongAnalysis();

	// �Ƴ��е��齫
	visibleMahjongPool_ = nullptr;
	// ��ǽ�ϵ��齫
	invisibleMahjongPool_ = nullptr;

	

	// ���з�λ���齫		
	memset(mahjong_, 0, sizeof(mahjong_));
}

int SRMahjongRobot::touchCard(unsigned char card) {
	SRMahjong* pmj = mahjong_[direction_];

	if (pmj == nullptr)
		return -1;

	// �ִε���
	roundNumber_++;

	// ����
	return pmj->addCardData(card);
}

int SRMahjongRobot::getOutCard(unsigned char * out_card, unsigned char * out_card_count) {
	if (out_card == nullptr || out_card_count == nullptr)
		return -87;

	// ����ɫ����
	SRMahjong* pmj = nullptr;
	if (direction_ != enDirection::None)
		pmj = mahjong_[direction_];
	if (pmj == nullptr)
		return -1;
	if (analysisLogic_->getMahjong() != pmj)
		analysisLogic_->setMahjong(pmj);

	srand((unsigned int)time(0));

	


	return 0;
}

int SRMahjongRobot::getAction(enDirection drc, unsigned char card) {
	return 0;
}

void SRMahjongRobot::setDirection(enDirection drc) {
	direction_ = drc;
	// �������齫�������ø�������
	if (mahjong_[direction_] != nullptr)
		analysisLogic_->setMahjong(mahjong_[direction_]);
}

SRMahjong * SRMahjongRobot::getMahjong(void) {
	if (direction_ == enDirection::None)
		return nullptr;

	return mahjong_[direction_];
}

const SRMahjong * SRMahjongRobot::getMahjong(enDirection drc) const {
	if (drc == enDirection::None)
		return nullptr;

	return mahjong_[drc];
}

void SRMahjongRobot::setMahjong(enDirection drc, SRMahjong * mahjong) {
	if (drc == enDirection::None)
		return;

	// �����齫
	mahjong_[drc] = mahjong;

	// �������齫�������ø�������
	if (drc == direction_)
		analysisLogic_->setMahjong(mahjong_[drc]);
}

void SRMahjongRobot::setEnemy(enDirection drc, int isEnemy) {
	if (drc == enDirection::None)
		return;

	enemyDirection_[drc] = isEnemy;
}
