#include "SRAnalyzeCard.h"

#include <time.h>
#include <iostream>


#define DEBUG(info) std::cout << info << std::endl;

SRAnalyzeCard::SRAnalyzeCard()
{
}


SRAnalyzeCard::~SRAnalyzeCard()
{
}

void SRAnalyzeCard::reset(void)
{
	isTing = false;
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


	// ���Ʋ��뵽������
	mapCardData_[protagonists_].addCardData(_in_card);
	// ��õ�ǰ��������
	BYTE card_index[MAX_INDEX] = {};
	mapCardData_[protagonists_].getCardIndexData(card_index);

	

	// �������
	if (!isTing_ && 0 == SRCardMagic::isTing(card_index)) {
		isTing_ = true;

		// �������õ��ƣ�������
		_out_card;

		return WIK_LISTEN;
	}
	else if (isTing_ && 0 == SRCardMagic::isWin(card_index)) {
		return WIK_CHI_HU;
	}


	// �Ȳ��������ֲ��ܺ�����ô�Ϳ�ʼ��·���ơ�
	





	DEBUG("ȥ�����2����λ�Ĳ��������ƣ�����ͷ���м��Ų�")

	DEBUG("ȥ�����1����λ�Ĳ��������ƣ�����ͷ���м��Ų�")


	DEBUG("������������,�����Ҫ�������")
	
	// �����Ʒ���
	do {
		if (rand() % 2) {
			DEBUG("���־�������(1234, 1233)")	
			DEBUG("����Ƿ��о���������ƿɹ�����")							   
			if (rand() % 2) {

				DEBUG("δ���֣��Ծ����ƽ����������\n")
					DEBUG("-----------begin----------")
					DEBUG("�鿴���5�Ŵ�����齫��")	

				if (rand() % 2) {
					DEBUG("�������ƣ����ȸ�����")
				}
				DEBUG("��õ�ǰ�غ���")
														

				DEBUG("------------end-----------")
			}
			else {
				DEBUG("���־�������������齫��")
				DEBUG("�˳������Ʒ���")

				std::cout << std::endl << std::endl;
				break;
			}
		}
	} while (false);

	// �����Լ����ƣ��õ���Ҫ�������
	   // ���������� 1234 �������� ���������ʱ�򣬷����ڳ����еĶ��ӣ���֤������������ѡ��

	   // ���Ʒ���

	   // ������������
	   // �����ų�����
	   // ������ʱӦ���ж�
	   // 1. ����  2. 

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

