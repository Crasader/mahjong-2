
#ifndef _SHANREN_PLAYER_LOGIC_H_
#define _SHANREN_PLAYER_LOGIC_H_

#include "CMD_Sparrow.h"
#include <vector>

class SRPlayerLogic
{
public:


public:
	SRPlayerLogic(enDirection dir);
	virtual ~SRPlayerLogic();


	// ���һ�Ų�Ҫ���齫��
	int getDiscard(void);



private:
	// ��λ����
	enDirection direction_;
	// ��ǰ�齫
	std::vector<BYTE> vecCardData_;

};


#endif // _SHANREN_PLAYER_LOGIC_H_