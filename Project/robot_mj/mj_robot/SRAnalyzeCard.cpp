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

int SRAnalyzeCard::getOutCard(unsigned char * _out_card) {
	if (_out_card == nullptr)
		return -1;


	srand((unsigned int)time(0));

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

