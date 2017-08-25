#ifndef _SHANREN_MAHJONG_H_
#define _SHANREN_MAHJONG_H_

#ifdef SRMJROBOT_EXPORTS
#define SRMJROBOT_API __declspec(dllexport)
#else
#define SRMJROBOT_API __declspec(dllimport)
#endif

#include "srmjglobal.h"


SRMJROBOT_API bool isValidCard(unsigned char cbCardData);

class SRMJROBOT_API SRMahjong
{
public:
	SRMahjong(unsigned char cardData[], unsigned char cardCount);
	virtual ~SRMahjong();

public:

	unsigned char have(unsigned char card);
	
	void sort(void);

	void upCardIndex(void);

	const unsigned char* data(void) const { return cardData_; }

	unsigned char length(void) const;

	void addCard(unsigned char card);

	void delCard(unsigned char card);

	unsigned char getLastTouchCard(void) const { return lastTouchCard_; }



public:

	unsigned char operator[] (const int &idx) { return cardIndex_[idx]; }
	unsigned char index(unsigned char& idx) { return cardIndex_[idx]; }
	 
public:

	// ���һ�Ź����ķ���
	int getFanPaiOne(int _indexBegin) const;

	// ��ü��1����λ�Ĳ��������ƣ�����ͷ���м��Ų�
	int getIntervalOne(int _indexBegin = 0) const;

	// ��ü��2����λ�Ĳ��������ƣ�����ͷ���м��Ų�
	int getIntervalTwo(int _indexBegin = 0) const;


protected:



	// �齫����������
	unsigned char cardIndex_[MAX_INDEX];

	unsigned char cardData_[MAX_COUNT + 1];
	unsigned char cardCount_;

	// ���һ��������
	unsigned char lastTouchCard_;

};

#endif // _SHANREN_MAHJONG_H_