#include "SRAnalyzeCard.h"
#include "SRCard.h"

#include <time.h>
#include <iostream>
#include <vector>


#define DEBUG(info) std::cout << info << std::endl;

SRAnalyzeCard::SRAnalyzeCard()
{
}


SRAnalyzeCard::~SRAnalyzeCard()
{
}

void SRAnalyzeCard::reset(void)
{
	isTing_ = false;
}

void SRAnalyzeCard::setGameCardForShow(stCardData _data)
{
	showCardData_ = _data;
}

void SRAnalyzeCard::setGameCardForHide(stCardData _data)
{
	showCardData_ = _data;
}

void SRAnalyzeCard::setGameCardForPlayer(enDirection _dec, stCardData _data)
{
	mapCardData_[_dec] = SRCardMagic(_data);
}

void SRAnalyzeCard::setGameProtagonists(enDirection _dec)
{
	protagonists_ = _dec;
}

int SRAnalyzeCard::getOutCard(unsigned char _in_card, unsigned char * _out_card) {

	if (_out_card == nullptr)
		return -1;


	// ��õ�ǰ��������
	BYTE card_index[MAX_INDEX] = {};
	mapCardData_[protagonists_].getCardIndexData(card_index);

	
	int arg1 = 0,arg2 = 0;
	// �������
	if (!isTing_ && (0 <= (arg1 = SRCardMagic::isTing(card_index)))) {
		arg2 = SRCardMagic::isTing(card_index, arg1);
		vecTingIndex_.push_back(arg1);
		if (arg2 >= 0)
			vecTingIndex_.push_back(arg2);
		isTing_ = true;
	}

	// ���Ʋ��뵽������
	mapCardData_[protagonists_].addCardData(_in_card);
	mapCardData_[protagonists_].getCardIndexData(card_index);
	SRCard card(card_index);

	// ������
	if (isTing_ && 0 == card.isWin()) {
		return WIK_CHI_HU;
	}



	// ���ܺ�����ô�Ϳ�ʼ��·���ơ�
	do {

		// �������� ����������������ͷ���
		if (isTing_) {
			
			
			// ȷ��Ҫ���������ƶ�����ǶԼҵĿ��ֻ�˳�ӣ�
			// ����ǣ��򾡿��ܵĻ��������ͣ��޷��������Բ�����Ϊ��
		}

		// �и��ȸ�
		for (int i = 0; i < MAX_INDEX; ++i) {
			if (card[i] == 4) {
				// �������Ƶ�����£�������� �Ƿ�������

				*_out_card = SRCardMagic::switchToCardData(i);
				return WIK_GANG;
			}
		}
		
		// ��õ��ŵķ���
		int index = card.getFanPaiOne();
		if (index > 0) {
			*_out_card = SRCardMagic::switchToCardData(index);
			break;
		}
		

		// ������й���2����λ�Ĳ���������
		index = card.getIntervalTwo();
		if (index > 0) {
			*_out_card = SRCardMagic::switchToCardData(index);
			break;
		}
	

		// ������пɹ�����Ĳ���������
		std::vector<int> vec_index;
		for (index = 0; (index = card.getIntervalOne(index)) != 0;) {
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
			*_out_card = SRCardMagic::switchToCardData(index);
			break;
		}


		// ���е�����˵�����־���������
		// �������Ƴ��� �������Ͼ���
		*_out_card = card.getOutCard();
		

	} while (false);


	mapCardData_[protagonists_].delCardData(*_out_card);
	return 0;
}

int SRAnalyzeCard::getAction(unsigned char _in_card)
{
	BYTE card_index[MAX_INDEX] = {};
	mapCardData_[protagonists_].getCardIndexData(card_index);

	// �жϺ���
	if (isTing_) {
		card_index[SRCardMagic::switchToCardIndex(_in_card)]++;
		if (0 == SRCardMagic::isWin(card_index))
			return WIK_CHI_HU;
		return WIK_NULL;
	}


	// ѯ�ʳ�����
	



	return WIK_NULL;
}

void SRAnalyzeCard::analyzeGamePlayer(enDirection _in_dec, stCardData * _out_dynamic, stCardData * _out_static)
{
}

int SRAnalyzeCard::analyzeProtagonists(void)
{
	//unsigned char* card = mapCardData_.at(protagonists_);
	//unsigned char card_count = mapCardData_.at(protagonists_).size;
	
	// �ж��Ƶ�����
	//if ((card_count < 2) || (card_count > MAX_COUNT) || ((card_count - 2) % 3 != 0))
	//	return -1;

	// ����ת��������ģʽ

	return 0;
}

void SRAnalyzeCard::analyzeGamePlayerForChain(void)
{
}

