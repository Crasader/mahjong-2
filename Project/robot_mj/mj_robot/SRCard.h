#ifndef _SHANREN_CARD_H_
#define _SHANREN_CARD_H_
#include "mj_header.h"
#include <vector>

class SRCard
{
public:
	SRCard();
	SRCard(const BYTE _cardIndex[]);
	virtual ~SRCard();



	// ȥ�����1����λ�Ĳ��������ƣ�����ͷ���м��Ų�
	int getIntervalOne(int _indexBegin = 0);

	// ȥ�����2����λ�Ĳ��������ƣ�����ͷ���м��Ų�
	int getIntervalTwo(int _indexBegin = 0);

	


	// �Ƿ����
	int isWin(void);

	// ��ʲô��
	std::vector<BYTE> getDeficiencyCardData(void);
	

	// ������˳
	int getSumKeShun(void);


private:
	bool isSameColor(BYTE arg1, BYTE arg2, BYTE arg3 = 0);

	int getKeAndShun(const BYTE _cardIndex[]);

	int isWin(const BYTE _cardIndex[], int _duiIndex);

private:
	BYTE cardIndex_[MAX_INDEX];
};

#endif // _SHANREN_CARD_H_