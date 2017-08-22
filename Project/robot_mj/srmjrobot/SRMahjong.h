#ifndef _SHANREN_MAHJONG_H_
#define _SHANREN_MAHJONG_H_

#ifdef SRMJROBOT_EXPORTS
#define SRMJROBOT_API __declspec(dllexport)
#else
#define SRMJROBOT_API __declspec(dllimport)
#endif

#include "srmjglobal.h"

class SRMJROBOT_API SRMahjong
{
public:
	SRMahjong(unsigned char cardData[], unsigned char cardCount);
	virtual ~SRMahjong();

public:
	
	void sort(void);

	const unsigned char* data(void) const { return cardData_; }

	unsigned char size(void) const;

	void addCard(unsigned char card);

	void delCard(unsigned char card);

	unsigned char getLastTouchCard(void) const { return lastTouchCard_; }



public:

	unsigned char operator[] (const int &idx) { return cardIndex_[idx]; }
	unsigned char getIndex(unsigned char& idx) { return cardIndex_[idx]; }
	 
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
	unsigned char index_;

	// ���һ��������
	unsigned char lastTouchCard_;

};

#endif // _SHANREN_MAHJONG_H_