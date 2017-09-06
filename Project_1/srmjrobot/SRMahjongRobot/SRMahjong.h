#pragma once

#include "SRMahjongGlobal.h"



class SRMAHJONGROBOT_API SRMahjong {

public:

	SRMahjong(void);

	virtual ~SRMahjong(void);

public:

	// �����������
	inline const BYTE* getData(void) const { return cardData_; }

	// ������������
	void setCardData(const BYTE * _cardData, BYTE _cardCount);

	// ͨ���±������������
	inline BYTE index(int idx) const { return cardIndex_[idx]; }
	// ͨ���±������������
	inline const BYTE* getIndex(int idx) const { return &cardIndex_[idx]; }
						
	// ��ѯĳ�����ж�����
	int have(BYTE _card);

	// ɾ��һ������
	int removeCardData(BYTE _card);

	// ���һ������
	int addCardData(BYTE _card);

	// ��ǰ��������
	inline int count(void) const;

	// ������һ����ӵ���
	inline BYTE getLastTouchCard(void) const { return lastTouchCard_; }

public:

	static unsigned char switchToCardIndex(unsigned char cbCardData) {
		return ((cbCardData&MASK_COLOR) >> 4) * 9 + (cbCardData&MASK_VALUE) - 1;
	}

	static unsigned char switchToCardData(unsigned char cbCardIndex) {
		return ((cbCardIndex / 9) << 4) | (cbCardIndex % 9 + 1);
	}

protected:

	// �����齫�Ƶ���������
	void upCardIndex(void);

	inline int maxSize(void) const;

protected:

	BYTE cardData_[MAX_COUNT];

	BYTE cardIndex_[MAX_INDEX];

private:

	// ���һ��������
	unsigned char lastTouchCard_;

};


class SRMAHJONGROBOT_API SRMahjongCard : public SRMahjong {

public:
	SRMahjongCard(void);

	// ���һ�Ź����ķ���
	int getFanPaiOne(int _indexBegin = 0) const;

	// ��ü��1����λ�Ĳ������ƣ�����ͷ���м��Ų�
	int getIntervalOne(int _indexBegin = 0) const;

	// ��ü��2����λ�Ĳ������ƣ�����ͷ���м��Ų�
	int getIntervalTwo(int _indexBegin = 0) const;

	// 1123  5667 5677
	int getShunDopant(int _indexBegin = 0) const;

	// 112  899  233
	int getDanDui(int _indexBegin = 0) const;

	int getNotShunKe(int _indexBegin = 0) const;

	int analysis(void);

protected:

	int analysisHuaPai(const BYTE * cardIndexBegin, 
		const BYTE * cardIndexEnd, BYTE * outCardIndexState)const;



private:
	// 0x00 ������ 0x01 �������� 0x02 ������ 0x04 ������ 0x08 ˳������  
	BYTE cardIndexState_[MAX_INDEX];

};