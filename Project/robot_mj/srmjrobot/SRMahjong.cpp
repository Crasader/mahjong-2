#include "SRMahjong.h"
#include "SRAnalysis.h"

#include <iostream>

#include <algorithm>



SRMahjong::SRMahjong(unsigned char cardData[], unsigned char cardCount) {
	memset(cardIndex_, 0, sizeof(cardIndex_));
	memset(cardData_, 0, sizeof(cardData_));
	cardCount_ = cardCount;
	
	lastTouchCard_ = 0;

#ifdef _DEBUG
	int card_size = cardCount * sizeof(unsigned char);
	if (card_size > sizeof(cardData_)) {
		std::cout << __FUNCTION__ << "The data of crossing the line." << std::endl;
	}
#endif

	memcpy(cardData_, cardData, cardCount_ * sizeof(unsigned char));

	// ����ת��Ϊ����ģʽ(����������󣬿��ܻ��������Խ��)
	for (int i = 0; i < cardCount_; ++i)
		cardIndex_[SRAnalysis::switchToCardIndex(cardData[i])]++;
}

SRMahjong::~SRMahjong() {
}


unsigned char SRMahjong::have(unsigned char card) {
	return cardIndex_[SRAnalysis::switchToCardIndex(card)];
}

void SRMahjong::sort(void) {
	std::sort(cardData_, cardData_ + MAX_COUNT - 1);
}

void SRMahjong::upCardIndex(void) {
	memset(cardIndex_, 0, sizeof(cardIndex_));
	for (int i = 0; i < sizeof(cardData_) / sizeof(cardData_[0]); ++i) {
		int idx = SRAnalysis::switchToCardIndex(cardData_[i]);
		if (cardData_[i] == 0)
			continue;

		// ��ֹidx�±�Ϊ-1
		if (idx >= 0 && idx < MAX_INDEX)
			cardIndex_[idx]++;
		else
			std::cout << "warning:" << __FUNCTION__ << std::endl;
	}
}

unsigned char SRMahjong::length(void) 
{		
	//��Ŀͳ��
	BYTE cbCardCount = 0;
	for (BYTE i = 0; i<MAX_INDEX; i++)
		cbCardCount += cardIndex_[i];

	return cbCardCount;
}

void SRMahjong::addCard(unsigned char card)
{
	cardData_[MAX_COUNT - 1] = card;
	lastTouchCard_ = card;
	cardCount_ += 1;

	this->sort();
	this->upCardIndex();
}

void SRMahjong::delCard(unsigned char card)
{
	// ���ﻹ��Ҫ��������һ��
	auto c = std::find(cardData_, cardData_ + MAX_COUNT, card);

	if (c != nullptr)
		*c = 0;
	else {
		std::cout << "error: Try to delete a data that doesn't exist." << std::endl;
		return;
	}

	cardCount_ -= 1;

	this->sort();
	this->upCardIndex();
}



int SRMahjong::getFanPaiOne(int _indexBegin) const {
	if (_indexBegin == 0)
		_indexBegin = MAX_INDEX - MAX_FAN;
	else if (_indexBegin < MAX_INDEX - MAX_FAN || _indexBegin >= MAX_INDEX)
		return 0;

	for (int i = _indexBegin; i < MAX_INDEX; ++i) {
		if (cardIndex_[i] == 1) {
			return i;
		}
	}

	return -1;
}



int SRMahjong::getIntervalOne(int _indexBegin) const {
	for (int i = _indexBegin / 9; i < 3; ++i) {
		const int& INDEX_BEGIN = i * 9;
		const int& INDEX_END = i * 9 + 9;
		for (int index_begin = _indexBegin; index_begin < INDEX_END; ++index_begin) {
			// û���� ���� ����ָ���ķ�Χ֮ǰ ��ѡ������
			if (cardIndex_[index_begin] == 0)
				continue;

			const int& arg1 = index_begin - 1;
			const int& arg3 = index_begin + 1;

			// �ж�����
			if ((arg1 >= INDEX_BEGIN && cardIndex_[arg1] > 0)
				|| (arg3 < INDEX_END && cardIndex_[arg3] > 0)) {
				continue;
			}

			// ����������
			return index_begin;
		}
	}


	return -1;
}

int SRMahjong::getIntervalTwo(int _indexBegin) const {

	for (int i = _indexBegin / 9; i < 3; ++i) {
		const int& INDEX_BEGIN = i * 9;
		const int& INDEX_END = i * 9 + 9;
		for (int index_begin = _indexBegin; index_begin < INDEX_END; ++index_begin) {
			// û���� ���� ����ָ���ķ�Χ֮ǰ ��ѡ������
			if (cardIndex_[index_begin] == 0)
				continue;

			const int& arg1 = index_begin - 1, &arg2 = index_begin - 2;
			const int& arg3 = index_begin + 1, &arg4 = index_begin + 2;

			// �ж�����
			if ((arg1 >= INDEX_BEGIN && cardIndex_[arg1] > 0)
				|| (arg2 >= INDEX_BEGIN && cardIndex_[arg2] > 0)
				|| (arg3 < INDEX_END && cardIndex_[arg3] > 0)
				|| (arg4 < INDEX_END && cardIndex_[arg4] > 0)) {
				continue;
			}

			// ����������
			return index_begin;
		}
	}
	return -1;
}

int SRMahjong::getShunDopant(int _indexBegin) const {
	// ���������������		
	BYTE kind_item_count = 0;
	stTeamKind team_kind[MAX_COUNT];
	memset(team_kind, 0, sizeof(team_kind));

	for (BYTE i = _indexBegin; i < MAX_INDEX; i++) {
		if ((i > (MAX_INDEX - 4)) || (cardIndex_[i] == 0) || ((i % 9) < 7))
			continue;

		if ((cardIndex_[i + 1] >= 1) && (cardIndex_[i + 2] >= 1))
		{
			team_kind[kind_item_count].card[0] = i;
			team_kind[kind_item_count].card[1] = i + 1;
			team_kind[kind_item_count].card[2] = i + 2;
			team_kind[kind_item_count].kind = WIK_LEFT;
			team_kind[kind_item_count++].eye = i;
		}
		
	}


	for (int i = 0; i < kind_item_count; ++i) {
		const int& ridx1 = team_kind[i].card[0];
		const int& ridx2 = team_kind[i].card[1];
		const int& ridx3 = team_kind[i].card[2];

		// ˳���Ƶ�������
		int temp_team_count = cardIndex_[ridx1] + cardIndex_[ridx2] + cardIndex_[ridx3];

		// ˵������ ���� ���� [1123   1223  1122333 1112223333]
		if (temp_team_count % 3 == 1) {
			// Ѱ����С������  
			const int& rnum = (cardIndex_[ridx1] <= cardIndex_[ridx2])
								? cardIndex_[ridx1] : cardIndex_[ridx2];
				

			if (cardIndex_[ridx1] != rnum) {
				return ridx1;
			}
			else if (cardIndex_[ridx2] != rnum) {
				return ridx2;
			}
			else if (cardIndex_[ridx3] != rnum) {
				// ������Ҫ����ϸ��һ��  
				const int& temp_next_kind_head = team_kind[i + 1].eye;
				if (temp_next_kind_head <= ridx3 + 1) {
					// ��һ������������뵱ǰ����ص��齫 �������� [123345 12335789]
					// ��������������һ��
					continue;
				}
				return ridx3;
			}
		}
	}

	return -1;
}

bool isValidCard(unsigned char cbCardData)
{
	return SRAnalysis::isValidCard(cbCardData);
}
