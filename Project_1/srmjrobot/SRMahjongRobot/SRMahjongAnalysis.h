#pragma once


#include "SRMahjongGlobal.h"

#define STATE_NULL	(0x00)
#define STATE_DUI	(0x01)
#define STATE_KE	(0x02)
#define STATE_GANG	(0x04)
#define STATE_SHUN	(0x08)


class SRMahjong;

class SRMahjongAnalysis
{
public:
	SRMahjongAnalysis(void);
	virtual ~SRMahjongAnalysis(void);


public:

	virtual int analysis(void);

	virtual int analysis(const BYTE* _cardIndexBegin, const BYTE* _cardIndexEnd);

public:

	inline int index(int idx) const { return cardIndexState_[idx]; }

	void setMahjong(SRMahjong* mahjong) { mahjong_ = mahjong; }
	const SRMahjong* getMahjong(void) { return mahjong_; }

protected:

	int analysisHuaPai(const BYTE * cardIndexBegin,
		const BYTE * cardIndexEnd, BYTE * outCardIndexState)const;



private:
	// 0x00 ������ 0x01 �������� 0x02 ������ 0x04 ������ 0x08 ˳������  
	BYTE cardIndexState_[MAX_INDEX];

	SRMahjong* mahjong_;

};

