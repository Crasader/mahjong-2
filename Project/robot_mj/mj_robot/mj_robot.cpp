// mj_robot.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "mj_robot.h"


// �����ƾ�
MJ_ROBOT_API int SRSetGameCardData(const stCardData _inDesktopCard,
	const stCardData _inNotShowCard) {
	return 0;
}

// ���������
MJ_ROBOT_API int SRSetPlayerCardData(const stCardData _inPlayer_Left,
	const stCardData _inPlayer_Above,
	const stCardData _inPlayer_Right,
	const stCardData _inPlayer_Myself) {
	return 0;
}


// ѯ�ʳ���
MJ_ROBOT_API int SRAskOutCard(unsigned char* _outCard) {
	return 0;
}

// ѯ������
MJ_ROBOT_API int SRAskAction(unsigned char _inCard) {
	return 0;
}

// ѯ�ʺ���
MJ_ROBOT_API int SRAskWinCard(void) {
	return 0;
}

