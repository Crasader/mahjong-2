#ifndef _SHANREN_CARD_MAGIC_H_
#define _SHANREN_CARD_MAGIC_H_

#include "mj_header.h"


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


	int getCardSize(void) const;

private:

	//�����˿�
	int analyseCard(void);



private:

	//��Ч�ж�
	bool isValidCard(BYTE cbCardData) const;

	//�˿�ת��
	BYTE switchToCardIndex(BYTE cbCardData) const;

	//�˿�ת��
	BYTE switchToCardData(BYTE cbCardIndex) const;


private:

	BYTE cardIndex_[MAX_INDEX];
	stCardData srcCardData_;
};

#endif // _SHANREN_CARD_MAGIC_H_