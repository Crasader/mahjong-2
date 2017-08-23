#include "SRAnalysis.h"
#include "srmjglobal.h"



SRAnalysis::SRAnalysis()
{
}


SRAnalysis::~SRAnalysis()
{
}

int SRAnalysis::isWin(const unsigned char * data, unsigned char count) {
	// �������
	if ((count < 2) || (count > MAX_COUNT) || ((count - 2) % 3 != 0))
		return -1;

	unsigned char card_index[MAX_INDEX];

	// ����ת��Ϊ����ģʽ(����������󣬿��ܻ��������Խ��)
	for (int i = 0; i < count; ++i)
		card_index[switchToCardIndex(data[i])]++;
			   

	isWin(card_index);

	return 0;
}


int SRAnalysis::isWin(const unsigned char _cardIndex[], int _duiIndex)
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


bool SRAnalysis::isValidCard(unsigned char cbCardData) {
	unsigned char cbValue = (cbCardData&MASK_VALUE);
	unsigned char cbColor = (cbCardData&MASK_COLOR) >> 4;
	return (((cbValue >= 1) && (cbValue <= 9) && (cbColor <= 2)) || ((cbValue >= 1) && (cbValue <= 7) && (cbColor == 3)));
}

int SRAnalysis::getKeAndShun(const unsigned char _cardIndex[]) {
	// ���޸�ԭֵ
	BYTE cbCardIndex[MAX_INDEX] = {};
	memcpy(cbCardIndex, _cardIndex, sizeof(_cardIndex[0])* MAX_INDEX);

	// ���������������		
	BYTE cbKindItemCount = 0;

	// ��ַ���
	for (BYTE i = 0; i < MAX_INDEX; i++) {
		//ͬ���ж�
		if (cbCardIndex[i] == 3) {
			++cbKindItemCount;
			cbCardIndex[i] -= 3;
		}
		// �����ж�
		else if ((i<(MAX_INDEX - 9)) && (cbCardIndex[i]>0) && ((i % 9)<7)) {
			for (; 1 <= cbCardIndex[i];) {
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

unsigned char SRAnalysis::switchToCardIndex(unsigned char cbCardData) {
	return ((cbCardData&MASK_COLOR) >> 4) * 9 + (cbCardData&MASK_VALUE) - 1;
}

unsigned char SRAnalysis::switchToCardData(unsigned char cbCardIndex) {
	return ((cbCardIndex / 9) << 4) | (cbCardIndex % 9 + 1);
}

int SRAnalysis::isTing(const unsigned char * data, unsigned char count, unsigned char* out_discard,
	unsigned char * out_data, unsigned char* out_count) {
	// ����У��
	if ((count < 2) || (count > MAX_COUNT) || ((count - 2) % 3 != 0))
		return -87;

	// ����ת��
	BYTE card_index[MAX_INDEX] = {};
	for (int i = 0; i < count; ++i) {
		unsigned char idx = SRAnalysis::switchToCardIndex(data[i]);
		// ��ֹidx�±�Ϊ-1
		if (idx >= 0)
			card_index[idx]++;
	};

	// ���Ʒ���
	int ret = -1;
	for (unsigned char idx = 0; idx < MAX_INDEX; ++idx) {
		if (card_index[idx] > 0)
			--card_index[idx];
		else
			continue;
		
		for (unsigned char i = 0; i < MAX_INDEX; ++i) {
			++card_index[i];

			if (0 == isWin(card_index)) {
				ret = 0;
				// ���ﻹ��Ҫ�Ż� ����� Ҫ��A�� �ɳ� B �� C �����
				if (out_data != nullptr) {
					*out_data = switchToCardIndex(i);
					++out_data;
				}
				if (out_count != nullptr)
					(*out_count)++;

				*out_discard = switchToCardIndex(idx);
				++out_discard;
			}

			--card_index[i];
		}

		++card_index[idx];
	}
			  
	return ret;
}
