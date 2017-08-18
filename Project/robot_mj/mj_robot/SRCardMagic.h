#ifndef _SHANREN_CARD_MAGIC_H_
#define _SHANREN_CARD_MAGIC_H_

#include "mj_header.h"
#include <vector>


class SRCardMagic
{

	//��������
	struct stKindItem
	{
		BYTE							cbWeaveKind;						//�������
		BYTE							cbCenterCard;						//�����˿�
		BYTE							cbCardIndex[3];						//�˿�����
	};

public:
	SRCardMagic(const stCardData& _cardData);
	SRCardMagic(void);

	virtual ~SRCardMagic();


	// ��ÿ��ƴ�С
	int getCardSize(void) const;
	// �����������
	int getCardIndexData(BYTE* _out_cardIndex, BYTE* _out_count = nullptr);
	// ���һ����
	int addCardData(BYTE _card);
	// ɾ��һ����
	int delCardData(BYTE _card);

	// ������������
	std::vector<BYTE> getRequire(void) const;


public:

	static int isTing(const BYTE _cardIndex[]);

	// �ж�����
	static int isWin(const BYTE _cardIndex[], int _duiIndex = 0);

	// ��õ�ǰ�ƵĿ�˳����
	static int getKeAndShun(const BYTE _cardIndex[]);

	//��Ч�ж�
	static bool isValidCard(BYTE cbCardData);

	//�˿�ת��
	static BYTE switchToCardIndex(BYTE cbCardData);

	//�˿�ת��
	static BYTE switchToCardData(BYTE cbCardIndex);
private:

	//�����˿�
	int analyseCard(void);



private:



private:

	BYTE cardIndex_[MAX_INDEX];
	stCardData srcCardData_;
};

#endif // _SHANREN_CARD_MAGIC_H_