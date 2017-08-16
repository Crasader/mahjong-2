#ifndef _SHANREN_INTERFACE_BASE_H_
#define _SHANREN_INTERFACE_BASE_H_

#include "CMD_Sparrow.h"


class SRCardBase {
	SRCardBase(void) {};

	virtual ~SRCardBase(void) {};

	virtual BYTE* data(void) { return cardData_; }

	virtual void setData(BYTE* _data, int size);


private:
	BYTE* cardData_;
	int size_;
};

class SRInterfaceBase
{
public:

	SRInterfaceBase()
	{
	}

	virtual ~SRInterfaceBase()
	{
	}



	// ���������齫����
	virtual int getDesktopCardData(SRCardBase* _outCard) = 0;
														
	// ���ǽ�����е��齫���� (������������)
	virtual int getWallCardData(SRCardBase* _outCard) = 0;

	// ���ָ����ҵ��齫����
	virtual int getPlayerCardData(enDirection _drc, SRCardBase* _outCard) = 0;


	// ��õ�ǰ��Ϸ�غ���
	virtual int getBout(int* _outBout) = 0;
};

#endif // _SHANREN_INTERFACE_BASE_H_