#ifndef SHANREN_CMD_SPARROW_H
#define SHANREN_CMD_SPARROW_H

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

//////////////////////////////////////////////////////////////////////////
// �����궨��

#define GAME_PLAYER					4									//��Ϸ����


// ��������
#define MAX_WEAVE					5									//������
#define MAX_INDEX					34									//�������
#define MAX_COUNT					17									//�����Ŀ
#define MAX_REPERTORY				136									//�����

enum enDirection {
	South = 0,              //���� ��
	West,					//���� ��
	North,                  //���� ��
	East,					//���� ��
};


		
#endif // SHANREN_CMD_SPARROW_H