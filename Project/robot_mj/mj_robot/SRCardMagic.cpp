#include "SRCardMagic.h"
#include <vector>
#include <algorithm>


SRCardMagic::SRCardMagic(const stCardData& _cardData)
	:srcCardData_(_cardData) {
	// ת������������
	memset(cardIndex_, 0, sizeof(cardIndex_));

	// ����ת��Ϊ����ģʽ(����������󣬿��ܻ��������Խ��)
	for (int i = 0; i < MAX_COUNT; ++i) 
		cardIndex_[switchToCardIndex(_cardData.card[i])]++;
	
	int i = isWin(cardIndex_);
	analyseCard();
}

SRCardMagic::SRCardMagic(void) {
}


SRCardMagic::~SRCardMagic() {
}

bool SRCardMagic::isValidCard(BYTE cbCardData) {
	BYTE cbValue = (cbCardData&MASK_VALUE);
	BYTE cbColor = (cbCardData&MASK_COLOR) >> 4;
	return (((cbValue >= 1) && (cbValue <= 9) && (cbColor <= 2)) || ((cbValue >= 1) && (cbValue <= 7) && (cbColor == 3)));
}

int SRCardMagic::getCardSize(void) const {
	BYTE cbCardCount = 0;
	for (BYTE i = 0; i<MAX_INDEX; i++)
cbCardCount += cardIndex_[i];
return cbCardCount;
}

int SRCardMagic::getCardIndexData(BYTE * _out_cardIndex, BYTE * _out_count)
{
	if (!_out_cardIndex)
		return -1;

	memcpy(_out_cardIndex, cardIndex_, MAX_INDEX);

	if (_out_count)
		*_out_count = (BYTE)MAX_INDEX;

	return 0;
}

int SRCardMagic::addCardData(BYTE _card)
{
	cardIndex_[switchToCardIndex(_card)]++;
	return 0;
}

int SRCardMagic::delCardData(BYTE _card)
{
	if (_card > MAX_INDEX + 3)
		return -1;

	cardIndex_[switchToCardIndex(_card)]--;
	return 0;
}


int SRCardMagic::isTing(const BYTE _cardIndex[], int _indexBegin)
{
	if (_indexBegin > MAX_INDEX)
		return -2;

	BYTE card_index[MAX_INDEX] = {};
	memcpy(card_index, _cardIndex, sizeof(_cardIndex[0]) * MAX_INDEX);

	for (; _indexBegin < MAX_INDEX; ++_indexBegin) {
		++card_index[_indexBegin];

		if (0 == isWin(card_index))
			return _indexBegin;

		--card_index[_indexBegin];
	}
	return -1;
}

int SRCardMagic::isWin(const BYTE _cardIndex[], int _duiIndex)
{
	//������Ŀ				 
	BYTE card_index[MAX_INDEX] = {};
	memcpy(card_index, _cardIndex, sizeof(_cardIndex[0])*MAX_INDEX);
	BYTE cbCardCount = 0;

	for (BYTE i = 0; i < MAX_INDEX; i++)
		cbCardCount += card_index[i];

	if ((cbCardCount < 2) || (cbCardCount > MAX_COUNT) || ((cbCardCount - 2) % 3 != 0))
		return -1;



	for (int i = 0, k = 0; i < MAX_INDEX; ++i) {
		if (card_index[i] >= 2) {
			// �ý��Ƿ����ж���
			if (++k < _duiIndex)
				continue;

			// �ѽ���ȡ��
			card_index[i] -= 2;

			// ��ʼ�ж���˳����
			if (MAX_WEAVE == getKeAndShun(card_index))
				return 0;
			else
				return isWin(_cardIndex, ++_duiIndex);
		}
	}



	return -1;
}

int SRCardMagic::isSameColor(BYTE _arg1, BYTE _arg2, BYTE _arg3)
{

	return 0;
}

int SRCardMagic::isIntervalTwo(const BYTE _cardIndex[])
{
	int index = 0;
	BYTE card_index[MAX_INDEX];
	memcpy(card_index, _cardIndex, sizeof(_cardIndex[0]) * MAX_INDEX);
	// û�з��Ƶ�����±�
	const int cMax_Index = MAX_INDEX - 7;
	for (; index < MAX_INDEX - 7; ++index) {
		// �ж����� ͬһ����
		if (_cardIndex[index] > 0 && ((index % 9) < 7)) {
			if (isSameColor(_cardIndex[index], _cardIndex[index + 1], _cardIndex[index + 2])) {
				// ˳�ӵ���
				if ((_cardIndex[index - 1] > 0) && (_cardIndex[index + 1] > 0)
					|| (_cardIndex[index - 1] > 0) && (_cardIndex[index - 2] > 0)) {
					index += 2;
					continue;
				}
			}
			// ˳�ӵ���
			if ((_cardIndex[index + 1] > 0) && (_cardIndex[index + 2] > 0)
				|| (_cardIndex[index - 1] > 0) && (_cardIndex[index + 1] > 0)
				|| (_cardIndex[index - 1] > 0) && (_cardIndex[index - 2] > 0)) {
				index += 2;
				continue;
			}
			else {
				return index;
			}
		}
	}
	return -1;
}

int SRCardMagic::isIntervalOne(const BYTE _cardIndex[])
{
	return 0;
}

int SRCardMagic::getKeAndShun(const BYTE _cardIndex[]) {
	// ���޸�ԭֵ
	BYTE cbCardIndex[MAX_INDEX] = {};
	memcpy(cbCardIndex, _cardIndex, sizeof(_cardIndex[0])* MAX_INDEX);

	// ���������������		
	BYTE cbKindItemCount = 0;

	// ��ַ���
	for (BYTE i = 0; i < MAX_INDEX; i++) {
		//ͬ���ж�
		if (cbCardIndex[i] >= 3) {
			++cbKindItemCount;
			cbCardIndex[i] -= 3;
		}
		// �����ж�
		else if ((i<(MAX_INDEX - 9)) && (cbCardIndex[i]>0) && ((i % 9)<7)) {
			for (;1 <= cbCardIndex[i];) {
				// ˳�ӵ���
				if ((cbCardIndex[i + 1] >= 1) && (cbCardIndex[i + 2] >= 1)) {
					++cbKindItemCount;
					cbCardIndex[i] -= 1;
					cbCardIndex[i + 1] -= 1;
					cbCardIndex[i + 2] -= 1;
				}
				else
					break;
			}
				
		}
	}	 
	return cbKindItemCount;
}

int SRCardMagic::analyseCard(void)
{
	//// �����齫��Ŀ
	//BYTE cbCardCount = getCardSize();
	//if ((cbCardCount<2) || (cbCardCount>MAX_COUNT) || ((cbCardCount - 2) % 3 != 0))
	//	return -1;
	//BYTE cbCardIndex[MAX_INDEX];
	//memcpy(cbCardIndex, cardIndex_, sizeof(cardIndex_));

	//// ��������������
	//
	//BYTE cbKindItemCount = 0;
	//stKindItem KindItem[MAX_WEAVE];
	//memset(KindItem, 0, sizeof(KindItem));
	//							 
	//// ��ַ���
	//if (cbCardCount >= 3)
	//{
	//	for (BYTE i = 0; i < MAX_INDEX; i++)
	//	{
	//		bool haveKind = false;
	//		//ͬ���ж�
	//		if (cbCardIndex[i] >= 3) {

	//			if (cbCardIndex[i] == 4)
	//				KindItem[cbKindItemCount].cbWeaveKind = CARDTYPE_KE;
	//			else
	//				KindItem[cbKindItemCount].cbWeaveKind = CARDTYPE_GANG;

	//			memset(KindItem[cbKindItemCount].cbCardIndex, i, sizeof(KindItem[cbKindItemCount].cbCardIndex)); 
	//			KindItem[cbKindItemCount++].cbCenterCard = switchToCardData(i);

	//			// �����ǿ̻��Ǹܣ�������ƶ���������������Ϊ�ѳɺ�������
	//			//cbCardIndex[i] = 0;
	//			//continue;
	//			haveKind = true;
	//		}

	//		// �����ж�
	//		else if ((i<(MAX_INDEX - 9)) && (cbCardIndex[i]>0) && ((i % 9)<7))
	//		{
	//			for (BYTE j = 1; j <= cbCardIndex[i]; j++)
	//			{
	//				// ˳�ӵ���
	//				if ((cbCardIndex[i + 1] >= j) && (cbCardIndex[i + 2] >= j))
	//				{
	//					KindItem[cbKindItemCount].cbCardIndex[0] = i;
	//					KindItem[cbKindItemCount].cbCardIndex[1] = i + 1;
	//					KindItem[cbKindItemCount].cbCardIndex[2] = i + 2;
	//					KindItem[cbKindItemCount].cbWeaveKind = CARDTYPE_SHUN;
	//					KindItem[cbKindItemCount++].cbCenterCard = switchToCardData(i);

	//					haveKind = true;
	//				}
	//			}
	//		}

	//		// �����ж�
	//		if (!haveKind) {

	//		}

	//	}
	//}


	return 0;
}

BYTE SRCardMagic::switchToCardIndex(BYTE cbCardData) {
	return ((cbCardData&MASK_COLOR) >> 4) * 9 + (cbCardData&MASK_VALUE) - 1;
}

BYTE SRCardMagic::switchToCardData(BYTE cbCardIndex) {
	return ((cbCardIndex / 9) << 4) | (cbCardIndex % 9 + 1);   
}
