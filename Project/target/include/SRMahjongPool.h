#ifndef _SHANREN_MAHJONG_POOL_H_
#define _SHANREN_MAHJONG_POOL_H_

#include "srmjglobal.h"

#ifdef SRMJROBOT_EXPORTS
#define SRMJROBOT_API __declspec(dllexport)
#else
#define SRMJROBOT_API __declspec(dllimport)
#endif



class SRMJROBOT_API SRMahjongPool
{
public:

	virtual ~SRMahjongPool(void);


public:

	// ��ó�������
	int getMahjongPoolData(unsigned char* out_data, unsigned char size);

	// ���ҵ�ǰ�齫������λ��
	// ����λ���±�
	unsigned char find(unsigned char card_data)const;

	// ���ĳ���齫��ӵ�е�����
	// ����ֵ���齫�Ƶ�����
	unsigned char have(unsigned char card_data)const;

	// ǰ�˵���һ���齫��
	unsigned char pop_front(void);
	// ��˵���һ���齫��
	unsigned char pop_back(void);


private:

	unsigned char cardData_[MAX_COUNT + 1];

	unsigned char indexBegin_;
	unsigned char indexEnd_;


};

#endif // _SHANREN_MAHJONG_POOL_H_