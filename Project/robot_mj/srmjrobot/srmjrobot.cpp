// srmjrobot.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "srmjrobot.h"
#include "SRMahjong.h"	  
#include "SRMahjongPool.h"
#include "SRAnalysis.h"


SRRobot::SRRobot(void) {
	// ���ݳ�ʼ��
	isTing_ = -1;
	memset(arrTing_, 0, sizeof(arrTing_));
	numTing_ = 0;

	invisibleMahjongPool_ = nullptr;
	visibleMahjongPool_ = nullptr;

	direction_ = enDirection::None;
	for (int i = 0; i < sizeof(mahjong_) / sizeof(mahjong_[0]); ++i)
		mahjong_[i] = nullptr;
}

SRRobot::~SRRobot(void) {
}

int SRRobot::touchCard(int direction) {
	SRMahjong* pmj = mahjong_[direction_];

	if (invisibleMahjongPool_ == nullptr || pmj == nullptr)
		return -1;

	// ����
	pmj->addCard(invisibleMahjongPool_->pop_front());
	return 0;
}

int SRRobot::getOutCard(unsigned char * out_card, unsigned char * out_card_count) {
	// ����У��
	if (out_card == nullptr || out_card_count == nullptr)
		return -87;
	SRMahjong* pmj = nullptr;
	if (direction_ != enDirection::None)
		pmj = mahjong_[direction_];
	if (pmj == nullptr)
		return -1;

	// �ж�����
	if (SRAnalysis::isWin(pmj->data(), pmj->size())) {
		return WIK_CHI_HU;
	}


	// ���Ʒ���
	unsigned char temp_discard[MAX_COUNT];
	memset(temp_discard, 0, sizeof(temp_discard));
	// �����㷨
	if (isTing_ > 0 || (isTing_ = SRAnalysis::isTing(pmj->data(), 
		pmj->size(), temp_discard, arrTing_, &numTing_)) > 0) {
		// ����������ͳ������

		// ��������ǽ��������������ѳ�˳�����ͣ����ǻ����ơ�


		*out_card = temp_discard[0];
		*out_card_count = 1;
		pmj->delCard(*out_card);

		return WIK_LISTEN;
	}


	// ��·����
	do {
		// �и��ȸ�
		for (unsigned char i = 0, s = 0; i < MAX_INDEX; ++i) {
			s = pmj->getIndex(i);
			if (s == 4) {
				// ����������Ƶ�����£�������� �Ƿ�������, �����ǲ������ͻ��ĸ���
				int i = 0;

				*out_card = SRAnalysis::switchToCardData(s);
				*out_card_count = 4;

				for(int i = 0; i < *out_card_count; ++i)
					pmj->delCard(*out_card);

				return WIK_GANG;
			}
		}

		// ������й���2����λ�Ĳ���������
		int index = pmj->getIntervalTwo();
		if (index > 0) {
			*out_card = SRAnalysis::switchToCardData(index);
			*out_card_count = 1;
			break;
		}


		// ������пɹ�����Ĳ���������
		std::vector<int> vec_index;
		for (index = 0; (index = pmj->getIntervalOne(index)) != 0;) {
			vec_index.push_back(index);
		}
		// ����Ƿ��е��ƿɳ�
		if (!vec_index.empty()) {
			// ��������۾�����
			for (auto x : vec_index) {
				x %= 9;
				if (x <= 2 || x >= 7) {
					index = x;
					break;
				}
			}
			*out_card = SRAnalysis::switchToCardData(index);
			*out_card_count = 1;
			break;
		}


		// ���������е����˵�����ͱȽϸ����ˣ���Ҫ����Ȩ�ظ��������ȷ���

		*out_card = pmj->getLastTouchCard();
		*out_card_count = 1;
	} while (false);

	// ɾ���������
	for (int i = 0; i < *out_card_count; ++i)
		pmj->delCard(*out_card);

	return WIK_NULL;
}

int SRRobot::getAction(enDirection drc, unsigned char card) {

	SRMahjong* pmj = nullptr;
	if (direction_ != enDirection::None)
		pmj = mahjong_[direction_];

	if (pmj == nullptr)
		return -1;

	if (0 == SRAnalysis::isWin(pmj->data(), pmj->size())) {
		return WIK_CHI_HU;
	}

	// �Ĵ��齫�ж�������

	return 0;
}

void SRRobot::setDirection(enDirection drc) {
	direction_ = drc;
}

SRRobot::enDirection SRRobot::getDirection(void) const {
	return direction_;
}

void SRRobot::setVisibleMahjongPool(SRMahjongPool * pool) {
	visibleMahjongPool_ = pool;
}

void SRRobot::setInvisibleMahjongPool(SRMahjongPool * pool) {
	invisibleMahjongPool_ = pool;
}

const SRMahjong * SRRobot::getMahjong(void) const {
	return mahjong_[direction_];
}

const SRMahjong * SRRobot::getMahjong(enDirection drc) const {
	return mahjong_[drc];
}

void SRRobot::setMahjong(enDirection drc, SRMahjong * mahjong) {
	mahjong_[drc] = mahjong;
}
