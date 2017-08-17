#ifndef _SHANREN_ANALYZE_CARD_H_
#define _SHANREN_ANALYZE_CARD_H_

#include "mj_header.h"
#include "SRCardMagic.h"
#include <map>
#include <vector>




class SRAnalyzeCard
{
public:
	SRAnalyzeCard();
	virtual ~SRAnalyzeCard();


	// ��Ϸ������Դ����
public:
	// �����Ѵ������
	void setGameCardForShow(stCardData _data);

	// ����δ��������
	void setGameCardForHide(stCardData _data);

	// ������ҵ���
	void setGameCardForPlayer(enDirection _dec, stCardData _data);

	// �������˹����
	void setGameProtagonists(enDirection _dec);


	// ���ͷ���
public:
	// ���Ҫ������
	int getOutCard(unsigned char* _out_card);


private:
	// �����������
	void analyzeGamePlayer(enDirection _in_dec, stCardData* _out_dynamic, stCardData* _out_static);

	int analyzeProtagonists(void);


	// �����������������˳��
	void analyzeGamePlayerForChain(void);


private:



private:

	// �ѳ�������
	stCardData showCardData_;
	// δ��������
	stCardData hideCardData_;
	// �����
	std::map<enDirection, SRCardMagic> mapCardData_;

    // ���˹�������λ
	enDirection protagonists_;


};


#endif // _SHANREN_ANALYZE_CARD_H_