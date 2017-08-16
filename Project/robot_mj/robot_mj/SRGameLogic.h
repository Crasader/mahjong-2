#ifndef _SHANREN_GAME_LOGIC_H_
#define _SHANREN_GAME_LOGIC_H_

#include "CMD_Sparrow.h"
#include "SRPlayerLogic.h"
#include "SRInterfaceBase.h"

#include <vector>


// *  ��������  * //

// ƽ�����Ŀ��ƣ���һ�Խ�

// �ԶԺ���ÿ���ƶ�������һ�����ƣ���111��222��

// ���ܺ������˸ܵ�ʱ�����ƺ�

// ��һɫ��ȫ������һ�ֻ�ɫ����123����567����234 ����888����99��

// �۾��ƣ�ÿ���ƶ���һ���

// �߶ԣ����Ƶ�ʱ�����߶��ƣ���11��22��99��44Ͳ��66Ͳ��88Ͳ��99Ͳ

// ���߶ԣ����߶ԵĻ����ϣ���������������һ���ġ���ע��:�������Ʋ����Ǹܵ��ƣ� ��11��11��99��44Ͳ��66Ͳ��88Ͳ��99Ͳ

// ��ԣ�һ�ֻ�ɫ�Ĵ���ӡ���111��444��222��999��66�򣬵��ķ֡�

// ���ԣ��������塢�˵Ĵ���ӣ���222�� 555�� 888�� 222�� 55Ͳ�����ķ֡�

// �������������ƾ���Ȼ�ɺ�����8�֡�

// �غ������մ��һ���ƾͳɺ�����8�֡�

		   


//��Ϸ�߼���
class SRGameLogic
{
						//��������
public:
	
	/*
		���캯��				
		_gameId		: ��ϷID
		_ruleId		: ��Ϸ����ID
		_playerNum	: ��Ϸ����
		_character	: �������Ը���Ѷ�
	*/
	SRGameLogic(int _gameId = 0, int _ruleId = 0, int _playerNum = 4, int character = 0);

	//��������
	virtual ~SRGameLogic(void);

public:

	// ѯ�ʳ���														 
	int askChuCard(BYTE* _card);

	// ѯ������														 
	int askPengCard(BYTE* _card);

	// ѯ�ʸ���														 
	int askGangCard(BYTE* _card);

	// ѯ�ʳ���														 
	int askChiCard(BYTE _inCard1, BYTE _inCard2, BYTE* _outCard);

	// ѯ�ʺ���														 
	int askHuCard(void);
	  





	// ��Ϸ�߼�

public:



	// ��Ϸ����������Ϣ�䱸
private:
	/*
	��װ��Ϸ����	  	
	_gameId		: ��ϷID
	_ruleId		: ��Ϸ����ID
	_playerNum	: ��Ϸ����
	_character	: �������Ը���Ѷ�
	*/
	void installGameScene(int _gameId, int _ruleId, int _playerNum, int character);


private:

	// �����Դ��
	std::vector<SRPlayerLogic*> vecPlayer_;


};


#endif // _SHANREN_GAME_LOGIC_H_