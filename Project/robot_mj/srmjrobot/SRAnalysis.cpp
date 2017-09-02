#include "SRAnalysis.h"
#include "srmjglobal.h"
#include <iostream>


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

	unsigned char card_index[MAX_INDEX] = {};

	// ����ת��Ϊ����ģʽ(����������󣬿��ܻ��������Խ��)
	for (int i = 0; i < MAX_COUNT; ++i)
		card_index[switchToCardIndex(data[i])]++;
			   

	return isWin(card_index);
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
			if (0 == isAllKeAndShun(card_index))
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

int SRAnalysis::analysisHuaPai(const unsigned char * cardIndexBegin, const unsigned char * cardIndexEnd,
	unsigned char* outCardIndex, char* outCount) {
	if (outCount!=nullptr)
		(*outCount) = 0;
	// ���Ķ�����Դ
	unsigned char card_index[10] = {};
	const int& data_size = cardIndexEnd - cardIndexBegin;

#ifdef _DEBUG
	if (data_size > 10) {
		std::cout << __FUNCTION__ << "warning: cache overflow!" << std::endl;
	}
#endif
	memcpy(card_index, cardIndexBegin, data_size);

	// ����Ȩ��ָ��
	int ret_weight = 10;
	do {
		


		// �������Ʒ��� ��������
		ret_weight--;
		{

			for (int index_begin = 0; index_begin < data_size; ++index_begin) {
				// û���� ���� ����ָ���ķ�Χ֮ǰ ��ѡ������
				if (card_index[index_begin] == 0)
					continue;

				const int& arg1 = index_begin - 1, &arg2 = index_begin - 2;
				const int& arg3 = index_begin + 1, &arg4 = index_begin + 2;

				// �ж�����
				if ((arg1 >= 0 && card_index[arg1] > 0)
					|| (arg2 >= 0 && card_index[arg2] > 0)
					|| (arg3 < data_size && card_index[arg3] > 0)
					|| (arg4 < data_size && card_index[arg4] > 0)
					// ����Ҳ��
					|| (card_index[index_begin] >= 2)) {
					continue;
				}

				// ����������
				(*outCardIndex) = index_begin;
				++outCardIndex;
				(*outCount)++;
			}
			if ((*outCount) > 0)
				break;
		}

		// 1234  2345 ���ͷ���
		ret_weight--;
		{

		}

		// ��һ������
		ret_weight--;
		{
			for (int index_begin = 0; index_begin < data_size; ++index_begin) {
				// û���� ���� ����ָ���ķ�Χ֮ǰ ��ѡ������
				if (card_index[index_begin] == 0)
					continue;

				const int& arg1 = index_begin - 1;
				const int& arg3 = index_begin + 1;

				// �ж�����
				if ((arg1 >= 0 && card_index[arg1] > 0)
					|| (arg3 < data_size && card_index[arg3] > 0)
					|| (card_index[index_begin] == 3)) {
					continue;
				}

				// ����������
				(*outCardIndex) = index_begin;
				++outCardIndex;
				(*outCount)++;
			}
			if ((*outCount) > 0)
				break;
		}
		

		// 1123  5667 5677 56778
		ret_weight--;
		{
			// ���������������		
			BYTE kind_item_count = 0;
			stTeamKind team_kind[MAX_COUNT];
			memset(team_kind, 0, sizeof(team_kind));

			for (BYTE i = 0; i < data_size; i++) {
				if ((card_index[i] == 0) || ((i % 9) > 7))
					continue;

				if ((card_index[i + 1] >= 1) && (card_index[i + 2] >= 1))
				{
					team_kind[kind_item_count].card[0] = i;
					team_kind[kind_item_count].card[1] = i + 1;
					team_kind[kind_item_count].card[2] = i + 2;
					team_kind[kind_item_count].kind = WIK_LEFT;
					team_kind[kind_item_count++].eye = i;
				}

			}


			for (int i = 0; i < kind_item_count; ++i) {
				const int& ridx1 = team_kind[i].card[0];
				const int& ridx2 = team_kind[i].card[1];
				const int& ridx3 = team_kind[i].card[2];

				// ˳���Ƶ�������
				int temp_team_count = card_index[ridx1] + card_index[ridx2] + card_index[ridx3];

				// ˵������ ���� ���� [1123   1223  1122333 1112223333]
				if (temp_team_count % 3 == 1) {
					// Ѱ����С������  
					const int& rnum = (card_index[ridx1] <= card_index[ridx2])
						? card_index[ridx1] : card_index[ridx2];

					unsigned char temp_index;
					if (card_index[ridx1] != rnum) {
						temp_index = (unsigned char)ridx1;
					}
					else if (card_index[ridx2] != rnum) {
						temp_index = (unsigned char)ridx2;
					}
					else if (card_index[ridx3] != rnum) {
						// ������Ҫ����ϸ��һ��  
						const int& temp_next_kind_head = team_kind[i + 1].eye;
						if (temp_next_kind_head <= ridx3 + 1) {
							// ��һ������������뵱ǰ����ص��齫 �������� [123345 12335789]
							// ��������������һ��
							continue;
						}

						temp_index = (unsigned char)ridx3;
					}
					 
					(*outCardIndex) = temp_index;
					outCardIndex++;
					(*outCount)++;
				}
			}

			if (*outCount > 0)
				break;
		}


		// 112 334 455
		ret_weight--;
		{
			BYTE kind_item_count = 0;
			stTeamKind team_kind[MAX_COUNT] = {};
			// �õ����� ���� [0ab0] ������
			for (BYTE i = 0; i < data_size; i++) {
				if (card_index[i] == 0)
					continue;

				// �ж��Ƿ񸽺�Ҫ��  [0ab0]
				if ((card_index[i + 1] >= 1) && (card_index[i + 2] == 0)
					&& (card_index[i - 1] == 0)) {
					team_kind[kind_item_count].card[0] = i;
					team_kind[kind_item_count].card[1] = i + 1;
					team_kind[kind_item_count].kind = WIK_RIGHT;
					team_kind[kind_item_count++].eye = i;
				}

			}


			for (int i = 0; i < kind_item_count; ++i) {
				const int& ridx1 = team_kind[i].card[0];
				const int& ridx2 = team_kind[i].card[1];

				// ˳���Ƶ�������
				int temp_team_count = card_index[ridx1] + card_index[ridx2];

				// ˵������ ���� ���� [112 122]
				if (temp_team_count != 3)
					continue;

				unsigned char temp_index = card_index[ridx1] > card_index[ridx2] ?
					ridx1 : ridx2;

				(*outCardIndex) = temp_index;
				outCardIndex++;
				(*outCount)++;
			}

			if (*outCount > 0)
				break;
		}


		// ���������Ϸ����������card_index���������޸ģ�
		ret_weight--;
		{
			for (int i = 0; i < data_size; ++i) {
				// @bug : 11123 567 678 999
				// ͬ���ж�
				if (card_index[i] == 3) {
					card_index[i] -= 3;
				}
				// �����ж�
				else if ((card_index[i]>0) && ((i % 9)<7)) {
					for (; 1 <= card_index[i];) {
						// ˳�ӵ���
						if ((card_index[i + 1] >= 1) && (card_index[i + 2] >= 1)) {
							card_index[i] -= 1;
							card_index[i + 1] -= 1;
							card_index[i + 2] -= 1;
						}
						else
							break;
					}

				}
			}

			for (int i = 0; i < data_size; ++i) {
				if (card_index[i] == 0)
					continue;

				(*outCardIndex) = i;
				outCardIndex++;
				(*outCount)++;
			}



			if ((*outCount) > 0)
				break;
		}

		return -1;

	} while (false);

	return ret_weight;
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
		else if ((i<(MAX_INDEX - 4)) && (cbCardIndex[i]>0) && ((i % 9)<7)) {
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


int SRAnalysis::isAllKeAndShun(const unsigned char _cardIndex[]) {
	// ���޸�ԭֵ
	BYTE cbCardIndex[MAX_INDEX] = {};
	memcpy(cbCardIndex, _cardIndex, sizeof(_cardIndex[0])* MAX_INDEX);


	// ��ַ���
	for (BYTE i = 0; i < MAX_INDEX; i++) {
		//ͬ���ж�
		if (cbCardIndex[i] == 3) {
			cbCardIndex[i] -= 3;
		}
		// �����ж�
		else if ((i<(MAX_INDEX - 4)) && (cbCardIndex[i]>0) && ((i % 9)<7)) {
			for (; 1 <= cbCardIndex[i];) {
				// ˳�ӵ���
				if ((cbCardIndex[i + 1] >= 1) && (cbCardIndex[i + 2] >= 1)) {
					cbCardIndex[i] -= 1;
					cbCardIndex[i + 1] -= 1;
					cbCardIndex[i + 2] -= 1;
				}
				else
					break;
			}

		}
	}
	int card_count = 0;
	for (auto item : cbCardIndex) {
		card_count += item;
	}
	return card_count;
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
		if (card_index[idx] == 0)
			continue;

		--card_index[idx];
		
		for (unsigned char i = 0; i < MAX_INDEX; ++i) {
			++card_index[i];

			if (0 == isWin(card_index)) {
				ret = 1;
				// ![����]���ﻹ��Ҫ�Ż� ����� Ҫ��A�� �ɳ� B �� C ����� [123 234 33 5 7 9]
				if (out_data != nullptr) {
					*out_data = switchToCardData(i);
					++out_data;
				}
				if (out_count != nullptr)
					(*out_count)++;

				*out_discard = switchToCardData(idx);
				++out_discard;
			}

			--card_index[i];
		}

		++card_index[idx];
	}
			  
	return ret;
}
