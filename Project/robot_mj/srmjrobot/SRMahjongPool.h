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
	virtual int getMahjongPoolData(unsigned char* out_data, unsigned char size);

	// ���ҵ�ǰ�齫������λ��
	// ����λ���±�
	virtual unsigned char find(unsigned char card_data)const;

	// ���ĳ���齫��ӵ�е�����
	// ����ֵ���齫�Ƶ�����
	virtual unsigned char have(unsigned char card_data)const;



protected:

	unsigned char cardData_[MAX_REPERTORY + 1];

	unsigned char indexBegin_;
	unsigned char indexEnd_;


};


// ��ǽ�ϵ�����
class SRMJROBOT_API SRInvisibleMahjongPool : public SRMahjongPool {

public:
	// ǰ�˵���һ���齫��
	unsigned char pop_front(void);
	// ��˵���һ���齫��
	unsigned char pop_back(void);
	// ���ó�������
	int setMahjongPoolData(const unsigned char* _data, unsigned char size);

};


// �Ƴ��е�����
class SRMJROBOT_API SRVisibleMahjongPool : public SRMahjongPool {
public:
	// push_back
	void push_back(unsigned char data);


};

#endif // _SHANREN_MAHJONG_POOL_H_