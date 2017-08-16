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


struct stCardData {
	unsigned char* card;
	int size;

	stCardData(void):card(nullptr),size(0) {}

	bool empty(void) {
		return (!card);
	}
};


// �����ƾ�
MJ_ROBOT_API int SRSetGameCardData(const stCardData _inDesktopCard,
									const stCardData _inNotShowCard);

// ���������
MJ_ROBOT_API int SRSetPlayerCardData(const stCardData _inPlayer_Left,
									const stCardData _inPlayer_Above,
									const stCardData _inPlayer_Right,
									const stCardData _inPlayer_Myself);


// ѯ�ʳ���
MJ_ROBOT_API int SRAskOutCard(unsigned char* _outCard);
										  
// ѯ����Ϊ
MJ_ROBOT_API int SRAskAction(unsigned char _inCard);

// ѯ�ʺ���
MJ_ROBOT_API int SRAskWinCard(void);
