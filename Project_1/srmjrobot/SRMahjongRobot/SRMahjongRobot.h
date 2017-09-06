
#include "SRMahjongGlobal.h"

class SRMahjong;
class SRMahjongAnalysis;
class SRVisibleMahjongPool;
class SRInvisibleMahjongPool;

// �����Ǵ� SRMahjongRobot.dll ������
class SRMAHJONGROBOT_API SRMahjongRobot {

public:

	SRMahjongRobot(void);

public:

	// ����
	// card : ��������
	virtual int touchCard(unsigned char card);
	
	// ����
	// out_card : ���Ƶ�����
	// out_card_count : ���Ƶ�����
	virtual int getOutCard(unsigned char* out_card, unsigned char* out_card_count);
	
	// ѯ�ʶ���
	// card : �����������������
	// ����ֵΪ���嶯�������ͷ�ļ��ķ���ֵ����
	virtual int getAction(enDirection drc, unsigned char card);
	

public:
	// ������Ϸ
//	void reset(void);
	
	// ���õ�ǰ�����˵ķ�λ
	inline void setDirection(enDirection drc);
	inline enDirection getDirection(void) const { return direction_; }
	
	// �����ƾ�
	inline void setVisibleMahjongPool(SRVisibleMahjongPool* pool) { visibleMahjongPool_ = pool; }
	inline void setInvisibleMahjongPool(SRInvisibleMahjongPool* pool) { invisibleMahjongPool_ = pool; }
	
	// �����齫										  
	inline SRMahjong* getMahjong(void);
	inline const SRMahjong* getMahjong(enDirection drc) const;
	inline void setMahjong(enDirection drc, SRMahjong* mahjong);

	// ������Ҫ��Եĵж����
	inline void setEnemy(enDirection drc, int isEnemy = 1);
	
private:

	// ���Ƿ�λ
	enDirection direction_;

	// �ж����
	int enemyDirection_[4];

	// �ƾ��ִ�
	int roundNumber_;

	// �Ƴ��е��齫
	SRVisibleMahjongPool* visibleMahjongPool_;
	// ��ǽ�ϵ��齫
	SRInvisibleMahjongPool* invisibleMahjongPool_;

	SRMahjongAnalysis* analysisLogic_;

	// ���з�λ���齫
	SRMahjong* mahjong_[5];




//	// ����
//	// direction : ���Ƶķ���ǰ����:0��������:1��  Ĭ��Ϊ0
//	virtual int touchCard(unsigned char card);
//
//	// ����
//	// out_card : ���Ƶ�����
//	// out_card_count : ���Ƶ�����
//	virtual int getOutCard(unsigned char* out_card, unsigned char* out_card_count);
//
//	// ѯ�ʶ���
//	// card : �����������������
//	// ����ֵΪ���嶯�������ͷ�ļ��ķ���ֵ����
//	virtual int getAction(enDirection drc, unsigned char card);
//
//
//public:
//	// ������Ϸ
//	void reset(void);
//
//	// ���õ�ǰ�����˵ķ�λ
//	void setDirection(enDirection drc);
//	enDirection getDirection(void) const;
//
//	// �����ƾ�
//	void setVisibleMahjongPool(SRVisibleMahjongPool* pool);
//	void setInvisibleMahjongPool(SRInvisibleMahjongPool* pool);
//
//	// �����齫										  
//	SRMahjong* getMahjong(void);
//	const SRMahjong* getMahjong(enDirection drc) const;
//	void setMahjong(enDirection drc, SRMahjong* mahjong);
//
//private:
//
//	//#ifdef SRMJROBOT_EXPORTS
//private:
//	// ���Ƿ�λ
//	enDirection direction_;
//
//	// �Ƴ��е��齫
//	SRVisibleMahjongPool* visibleMahjongPool_;
//	// ��ǽ�ϵ��齫
//	SRInvisibleMahjongPool* invisibleMahjongPool_;
//
//	// ���з�λ���齫
//	SRMahjong* mahjong_[5];
//
//	// �ƾ��ִ�
//	int roundNumber_;
//
//	// �����Ƿ����
//	int isTing_;
//	// ������
//	unsigned char arrTing_[14];
//	// ����������
//	unsigned char numTing_;
//
//	//#endif
};

