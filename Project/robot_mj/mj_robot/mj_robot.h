// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MJ_ROBOT_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MJ_ROBOT_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef MJ_ROBOT_EXPORTS
#define MJ_ROBOT_API __declspec(dllexport)
#else
#define MJ_ROBOT_API __declspec(dllimport)
#endif

#include "mj_header.h"

MJ_ROBOT_API int SRResetGame(void);
// �����ƾ�
MJ_ROBOT_API int SRSetGameCardData(const stCardData _inDesktopCard,
									const stCardData _inNotShowCard);

// ���������
MJ_ROBOT_API int SRSetPlayerCardData(enDirection _inDec, stCardData _inCard);

// �������˹�
MJ_ROBOT_API int SRSetGameProtagonists(enDirection _inDec);


// ѯ�ʳ���(�Լ�����ʱ)
MJ_ROBOT_API int SRAskOutCard(unsigned char _inCard, unsigned char* _outCard);
										  
// ѯ����Ϊ(�����˳���ʱ)
MJ_ROBOT_API int SRAskAction(unsigned char _inCard);

// ѯ�ʺ���
MJ_ROBOT_API int SRAskWinCard(void);
