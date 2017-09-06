#pragma once
#include "SRMahjongGlobal.h"


class SRMAHJONGROBOT_API SRMahjongPool
{
public:
	SRMahjongPool();
	virtual ~SRMahjongPool();

	BYTE pop_front(void) { return cardData_[iteratorBegin_++]; }
	BYTE pop_back(void) { return cardData_[iteratorEnd_--]; }

	// ����齫����
	const BYTE* getCardData(void) const { return &(cardData_[iteratorBegin_]); }

	// ��õ�ǰ�齫����
	BYTE getCardDataCount(void) const { return (iteratorBegin_ - iteratorEnd_); }

	// ����ĳ���Ƶ�λ��
	int find(BYTE _card) const ;

protected:

	// ����齫�������
	BYTE getCardMaxCount(void) const { return (sizeof(cardData_) / sizeof(cardData_[0])); }

protected:

	// �˿�����
	BYTE cardData_[MAX_REPERTORY];

	BYTE iteratorBegin_;
	BYTE iteratorEnd_;

private:
	// 
};



// ��ǽ�ϵ�����
class SRMAHJONGROBOT_API SRInvisibleMahjongPool : public SRMahjongPool {

public:

	SRInvisibleMahjongPool(void);

public:
	
	// ϴ��
	int randCardData(void);


protected:

	// ϴ��
	// _cardData: Ҫϴ����
	// _maxCount: �Ƶ�����
	int randCardData(BYTE *_cardData, BYTE _maxCount);


private:



};


// �Ƴ��е�����
class SRMAHJONGROBOT_API SRVisibleMahjongPool : public SRMahjongPool {

public:

	SRVisibleMahjongPool(void);

public:

	// push_back
	void push_back(BYTE data) { cardData_[iteratorEnd_++] = data; }

	


};