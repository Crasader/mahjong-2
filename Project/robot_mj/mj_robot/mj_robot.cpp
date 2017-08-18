// mj_robot.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "mj_robot.h"
#include "SRAnalyzeCard.h"

static SRAnalyzeCard gAnalyzeCard;


MJ_ROBOT_API int SRResetGame(void)
{
	gAnalyzeCard.reset();
	return 0;
}

// �����ƾ�
MJ_ROBOT_API int SRSetGameCardData(const stCardData _inDesktopCard,
	const stCardData _inNotShowCard) {
	gAnalyzeCard.setGameCardForShow(_inDesktopCard);
	gAnalyzeCard.setGameCardForHide(_inNotShowCard);
	return 0;
}

// ���������
MJ_ROBOT_API int SRSetPlayerCardData(enDirection _dec, stCardData _data) {
	gAnalyzeCard.setGameCardForPlayer(_dec, _data);
	return 0;
}

MJ_ROBOT_API int SRSetGameProtagonists(enDirection _inDec) {
	gAnalyzeCard.setGameProtagonists(_inDec);
	return 0;
}


// ѯ�ʳ���
MJ_ROBOT_API int SRAskOutCard(unsigned char _inCard, unsigned char* _outCard) {
	return gAnalyzeCard.getOutCard(_inCard, _outCard);
}

// ѯ������
MJ_ROBOT_API int SRAskAction(unsigned char _inCard) {
	return gAnalyzeCard.getAction(_inCard);
}

// ѯ�ʺ���
MJ_ROBOT_API int SRAskWinCard(void) {
	return 0;
}

