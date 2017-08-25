#ifndef _SHANREN_CARD_H_
#define _SHANREN_CARD_H_
#include "mj_header.h"
#include <vector>

class SRCard
{
private:
	//��������
	struct stKindItem {
		BYTE							cbWeaveKind;						//�������
		BYTE							cbCenterCard;						//�����˿�
		BYTE							cbCardIndex[3];						//�˿�����
	};
	struct stWinItem {
		BYTE dual;
		BYTE itemSize;
		stKindItem item[4];
		BYTE wantCard[5];
	};
public:
	SRCard();
	SRCard(const BYTE _cardIndex[]);
	virtual ~SRCard();

				   
	BYTE getOutCard(void);

	int getFanPaiOne(int _indexBegin = 0);

	// ��ü��1����λ�Ĳ��������ƣ�����ͷ���м��Ų�
	int getIntervalOne(int _indexBegin = 0);

	// ��ü��2����λ�Ĳ��������ƣ�����ͷ���м��Ų�
	int getIntervalTwo(int _indexBegin = 0);

	


	// �Ƿ����
	int isWin(void);

	// ��ʲô��
	std::vector<BYTE> getDeficiencyCardData(void);
	

	// ������˳
	int getSumKeShun(void);


public:
	
	int operator [] (const int &index) { return cardIndex_[index]; }

private:

	int analyseCard(BYTE _cardIndex[MAX_INDEX]);


	// ���ͬ��ɫ
	bool isSameColor(BYTE arg1, BYTE arg2, BYTE arg3 = 0);

	// �������Ȩ��
	int getCardWeight(BYTE card);

	// ��ÿ�˳����
	int getKeAndShun(const BYTE _cardIndex[], stWinItem & _winItem);
	int getKeAndShun(const BYTE _cardIndex[]);

	int isWin(const BYTE _cardIndex[], int _duiIndex);

	int isAllKeAndShun(const BYTE _cardIndex[]);

private:
	BYTE cardIndex_[MAX_INDEX];

	stWinItem winModel_;
};

#endif // _SHANREN_CARD_H_