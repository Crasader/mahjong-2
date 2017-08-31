// srmjrobot.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "srmjrobot.h"
#include "SRMahjong.h"	  
#include "SRMahjongPool.h"
#include "SRAnalysis.h"

#include <time.h>

SRRobot::SRRobot(void) {
	// ���Ƿ�λ
	direction_ = enDirection::None;

	// �Ƴ��е��齫
	visibleMahjongPool_ = nullptr;
	// ��ǽ�ϵ��齫				 
	invisibleMahjongPool_ = nullptr;

	// ���з�λ���齫
	for (int i = 0; i < sizeof(mahjong_) / sizeof(mahjong_[0]); ++i)
		mahjong_[i] = nullptr;
	

	// �����Ƿ����
	isTing_ = -1;
	// ������
	memset(arrTing_, 0, sizeof(arrTing_));
	// ����������
	numTing_ = 0;
	roundNumber_ = 0;
}

SRRobot::~SRRobot(void) {
}

int SRRobot::touchCard(unsigned char card) {
	SRMahjong* pmj = mahjong_[direction_];

	if (pmj == nullptr)
		return -1;

	// ����
	pmj->addCard(card);
	return 0;
}

int SRRobot::getOutCard(unsigned char * out_card, unsigned char * out_card_count) {
	// ����У��
	if (out_card == nullptr || out_card_count == nullptr)
		return -87;

	// ����ɫ����
	SRMahjong* pmj = nullptr;
	if (direction_ != enDirection::None)
		pmj = mahjong_[direction_];
	if (pmj == nullptr)
		return -1;

	pmj->upCardIndex();

	srand((unsigned int)time(0));
	// �ж�����
	if (0 == SRAnalysis::isWin(pmj->data(), pmj->length())) {
		return WIK_CHI_HU;
	}


	// ���Ʒ���
	unsigned char temp_discard[MAX_COUNT];
	memset(temp_discard, 0, sizeof(temp_discard));
	if (isTing_ > 0 || (isTing_ = SRAnalysis::isTing(pmj->data(), 
		pmj->length(), temp_discard, arrTing_, &numTing_)) > 0) {
		// ����������ͳ������	
		for (int i = 0; i < numTing_; ++i) {
			// ��������
			if (arrTing_[i] == 0)
				continue;

			// ���ɲ�
			if (invisibleMahjongPool_ == nullptr) {
				// �鿴�齫�Ƿ�����ǽ֮��
				int pool_idx = invisibleMahjongPool_->find(arrTing_[i]);

				if (pool_idx < 0) {
					// ������ǽ֮�ϣ�����Ƿ����Ƴ�֮��
					//visibleMahjongPool_->find(arrTing_[i]);

					// �����������Ƿ����������������
					for (int i = 0; i < numTing_; ++i) {

						// ����Ƿ����������
						for (int player = enDirection::South; player <= enDirection::East; ++player) {

							// ���ɲ�
							if (mahjong_[player] == nullptr)
								continue;

							if (0 < mahjong_[player]->have(arrTing_[i])) {
								// ������Ƿ�ɽ����˳��
								if (false) {
									arrTing_[i] = 0;
								}
								else {
									break;
								}
							}
						}
					}
				}

			}
			else {
				// ����Ƴ�֮���м��ſ�������
				int num = visibleMahjongPool_->have(arrTing_[i]);
				num += pmj->have(arrTing_[i]);
				if (num == 4) {
					// �޷�����
				}
			}
			
			
		}

		// ����Ƿ��ѳ�����
		{
			int temp_die = 0;
			for (int i = 0; i < numTing_; ++i)
				if (arrTing_[i] == 0)
					++temp_die;

			if (temp_die == numTing_) {
				// ˵���Ѿ����ƿ����������Բ�����Ϊ��
			}
		}
		
		
			


		*out_card = temp_discard[0];
		*out_card_count = 1;
		pmj->delCard(*out_card);

		return WIK_LISTEN;
	}


	// ��·����
	do {
		// �и��ȸ�
		for (unsigned char i = 0, s = 0; i < MAX_INDEX; ++i) {
			s = pmj->index(i);
			if (s == 4) {
				// ����������Ƶ�����£�������� �Ƿ�������, �����ǲ������ͻ��ĸ���
				int i = 0;

				*out_card = SRAnalysis::switchToCardData(s);
				*out_card_count = 4;

				for(int i = 0; i < *out_card_count; ++i)
					pmj->delCard(*out_card);

				return WIK_GANG;
			}
		}


		//// �е����ķ���������
		std::vector<int> vec_index;
		{
			for (int idx = 0; (idx = pmj->getFanPaiOne(idx)) != -1;++idx) {
				vec_index.push_back(idx);
			}
			if (!vec_index.empty()) {
				int i = rand() % vec_index.size();
				int temp = vec_index.at(i);
				// ���������ж�
				for (int i = 0; i < 4; ++i) {
					if (mahjong_[i] == nullptr && i == (int)direction_)
						continue;

					// ���кü��ţ��ȴ���������ģ��Դﵽ�������Ƶ�Ч��
					for (auto idx : vec_index) {
						if (2 <= mahjong_[i]->have(SRAnalysis::switchToCardData(idx))) {
							temp = idx;
						}
					}
				}

				*out_card = SRAnalysis::switchToCardData(temp);
				*out_card_count = 1;
				break;
			}
		}

		// ������й���2����λ�Ĳ���������  [122334 7] 
		{

			vec_index.clear();
			for (int idx = 0; (idx = pmj->getIntervalTwo(idx)) != -1;++idx) {
				if (pmj->index((unsigned char)idx) >= 2) {
					// �ж��Ƿ�Ψһ����
					continue;
				}
				vec_index.push_back(idx);
			}
			if (!vec_index.empty()) {
				int i = rand() % vec_index.size();
				int temp_index = vec_index.at(i);

				// ��������۾�����
				for (auto x : vec_index) {
					const int& temp = x % 9;
					if (temp <= 1 || temp >= 7) {
						temp_index = x;
						break;
					}
				}

				// ���������ж�
				for (int i = 0; i < 4; ++i) {
					if (mahjong_[i] == nullptr && i == (int)direction_)
						continue;

					// ���кü��ţ��ȴ���������ģ��Դﵽ�������Ƶ�Ч��
					for (auto idx : vec_index) {
						if (2 <= mahjong_[i]->have(SRAnalysis::switchToCardData(idx))) {
							temp_index = idx;
						}
					}
				}
				*out_card = SRAnalysis::switchToCardData(temp_index);
				*out_card_count = 1;
				break;
			}

		}


		// ������пɹ�����Ĳ��������� [1 3 567]   
		{
			vec_index.clear();
			for (int idx = 0; (idx = pmj->getIntervalOne(idx)) != -1;++idx) {
				if (pmj->index((unsigned char)idx) >= 2) {
					// �ж��Ƿ�Ψһ����
					continue;
				}
				vec_index.push_back(idx);
			}
			// ����Ƿ��е��ƿɳ�
			if (!vec_index.empty()) {
				// ![����] ȷ��������Ʋ��ǽ��Ƽ������ϣ����ⲻ��Ψһ����

				int i = rand() % vec_index.size();
				int temp_index = vec_index.at(i);
				// ��������۾�����
				for (auto x : vec_index) {
					const int& temp = x % 9;
					if (temp <= 1 || temp >= 7) {
						temp_index = x;
						break;
					}
				}
				*out_card = SRAnalysis::switchToCardData(temp_index);
				*out_card_count = 1;
				break;
			}
		}


		// ��� 1233 1223  7789 �����Ľ���,��Ϊ�޽�������
		{
			vec_index.clear();
			for (int idx = 0; (idx = pmj->getShunDopant(idx)) != -1; ++idx) {
				vec_index.push_back(idx);
			}
			// ����Ƿ����ƿɳ�
			if (!vec_index.empty()) {
				int i = rand() % vec_index.size();
				int temp_index = vec_index.at(i);
				// ��������۾�����
				for (auto x : vec_index) {
					const int& temp = x % 9;
					if (temp <= 1 || temp >= 7) {
						temp_index = x;
						break;
					}
				}
				*out_card = SRAnalysis::switchToCardData(temp_index);
				*out_card_count = 1;
				break;
			}
			
		}


		// [112  223 344]
		{
			vec_index.clear();
			for (int idx = 0; (idx = pmj->getDanDui(idx)) != -1; ++idx) {
				vec_index.push_back(idx);
			}
			// ����Ƿ����ƿɳ�
			if (!vec_index.empty()) {

				int i = rand() % vec_index.size();
				int temp_index = vec_index.at(i);

				// ������ѳ���
				for (auto v_index : vec_index) {
					// ȷ������ [122,223]
					unsigned char temp_dui = v_index;
					unsigned char temp_dan = v_index + 1;
					if (pmj->index(v_index) == 1) {
						// [122]
						temp_dui = v_index + 1;
						temp_dan = v_index;
					}

					// �������Ψһ�Ľ��ƣ����������
					if (vec_index.size() == 1) {
						temp_index = temp_dan;
						break;
					}


					// ��������Ѿ������������
					if (2 == visibleMahjongPool_->have(SRAnalysis::switchToCardData(temp_dui))) {
						temp_index = temp_dui;
						break;
					}

					// ���� [122 || 899] �������
					if (temp_dan % 9 == 0 || temp_dui % 9 == 8) {
						temp_index = temp_dan;
						break;
					}

					// ����������п�������������������š�  
					// ���� A���� [12357] ���Ǽҵ����� [455],��� 4
					for (int i = 0; i < 4; ++i) {
						if (mahjong_[i] == nullptr && i == (int)direction_)
							continue;

						if (0 != mahjong_[i]->getIntervalOne(SRAnalysis::switchToCardData(temp_dui))) {
							temp_index = temp_dan;
						}
						
					}

				}



				*out_card = SRAnalysis::switchToCardData(temp_index);
				*out_card_count = 1;
				break;
			}
		}


		// ������зǿ̷�˳����
		{
			vec_index.clear();
			for (int idx = 0; (idx = pmj->getNotShunKe(idx)) != -1; ++idx) {
				vec_index.push_back(idx);
			}
			// ����Ƿ��ж���
			for (auto iter_begin = vec_index.begin(); iter_begin != vec_index.end();
				++iter_begin) {
				if (*iter_begin == 2) {
					iter_begin = vec_index.erase(iter_begin);
				}
			}
			// ����Ƿ����ƿɳ�
			if (!vec_index.empty()) {


				int i = rand() % vec_index.size();
				int temp_index = vec_index.at(i);


				*out_card = SRAnalysis::switchToCardData(temp_index);
				*out_card_count = 1;
				break;
			}
		}


		// ���������е����˵�����ͱȽϸ����ˣ���Ҫ����Ȩ�ظ��������ȷ���
		*out_card = pmj->getLastTouchCard();
		*out_card_count = 1;
	} while (false);

	// ɾ���������
	for (int i = 0; i < (*out_card_count); ++i)
		pmj->delCard(*out_card);

	return WIK_NULL;
}

int SRRobot::getNewOutCard(unsigned char * out_card, unsigned char * out_card_count) {
	// ����У��
	if (out_card == nullptr || out_card_count == nullptr)
		return -87;


	// ����ɫ����
	SRMahjong* pmj = nullptr;
	if (direction_ != enDirection::None)
		pmj = mahjong_[direction_];
	if (pmj == nullptr)
		return -1;

	pmj->upCardIndex();
	srand((unsigned int)time(0));



	// �ж�����
	if (0 == SRAnalysis::isWin(pmj->data(), pmj->length())) {
		return WIK_CHI_HU;
	}


	int ret = WIK_NULL;

	// ����
	unsigned char temp_discard[MAX_COUNT];
	memset(temp_discard, 0, sizeof(temp_discard));
	if (isTing_ > 0 || (isTing_ = SRAnalysis::isTing(pmj->data(),
		pmj->length(), temp_discard, arrTing_, &numTing_)) > 0) {

		*out_card = SRAnalysis::switchToCardData(temp_discard[0]);
		*out_card_count = 1;
		ret = WIK_LISTEN;
	}


	// ����
	do {

		
		// �и��ȸ�
		{
			for (unsigned char i = 0, s = 0; i < MAX_INDEX; ++i) {
				s = pmj->index(i);
				if (s == 4) {
					// ����������Ƶ�����£�������� �Ƿ�������, �����ǲ������ͻ��ĸ���
					int i = 0;

					*out_card = SRAnalysis::switchToCardData(s);
					*out_card_count = 4;


					return WIK_GANG;
				}
			}
		}
		

		// �е����ķ���������
		{	   
			std::vector<int> vec_index;
			for (int idx = 0; (idx = pmj->getFanPaiOne(idx)) != -1; ++idx) {
				vec_index.push_back(idx);
			}
			if (!vec_index.empty()) {
				int i = rand() % vec_index.size();
				int temp = vec_index.at(i);
				// ���������ж�
				for (int i = 0; i < 4; ++i) {
					if (mahjong_[i] == nullptr && i == (int)direction_)
						continue;

					// ���кü��ţ��ȴ���������ģ��Դﵽ�������Ƶ�Ч��
					for (auto idx : vec_index) {
						if (2 <= mahjong_[i]->have(SRAnalysis::switchToCardData(idx))) {
							temp = idx;
						}
					}
				}

				*out_card = SRAnalysis::switchToCardData(temp);
				*out_card_count = 1;
				break;
			}
		}


		// ��������
		{
			// �������
			unsigned char card_index[MAX_INDEX] = {};
			for (int i = 0; i < MAX_INDEX; ++i)
				card_index[i] = pmj->index(i);

			
			// ��ʼ����
			{
				std::vector<int> vec_index;

				// ���ͽ���
				{
					for (int i = 0; i < 3; ++i) {
						// ����±������
						unsigned char temp_card_index[MAX_COUNT] = {};
						char temp_count = 0;
						// ������ǰ����Ļ���
						SRAnalysis::analysisHuaPai(&card_index[i * 9], &card_index[i * 9 + 9],
							temp_card_index, &temp_count);

						// �����Ƶ��±��������
						for (int n = 0; n < temp_count; ++n)
							vec_index.push_back((temp_card_index[n] + i * 9));
					}
				}


				// ������ѳ���
				{
					if (!vec_index.empty()) {
						int temp_i = rand() % vec_index.size();
						int temp_index = vec_index.at(temp_i);


						// ת������ �� 12  34 ����
						std::vector<int> vec_shun_index;
						{
							for (int i = 0; i < vec_index.size(); ++i) {
								// ���±�[i+1] �� �±� [i] ���ڣ���ת��
								if (i != 0 && 
									vec_index.at(i - 1) + 1 == vec_index.at(i)) {
									vec_shun_index.push_back(vec_index.at(i));
									vec_shun_index.push_back(vec_index.at(i - 1));
									vec_index.erase(vec_index.begin() + i);
									vec_index.erase(vec_index.begin() + i - 1);
								}
							}
							// Ĭ�ϳ� 12  34 ˳��
							if (!vec_shun_index.empty()) {
								temp_index = vec_shun_index.at(rand() % vec_shun_index.size());
							}
						}

						// ת�ƽ���
						std::vector<int> vec_double_index;
						{
							for (auto iter = vec_index.begin();
								iter != vec_index.end();) {

								if (2 <= pmj->index(*iter)) {
									vec_double_index.push_back(*iter);
									iter = vec_index.erase(iter);
								}
								else {
									++iter;
								}
							}
							// �����Ʋ���Ψһ�ң�û��ɢ˳�ɳ�����Ĭ�ϳ�����
							if (vec_double_index.size() > 1 && vec_shun_index.empty())
								temp_index = vec_double_index.at(
									rand() % vec_double_index.size());
						}
						

						// ������е��ƣ���Ĭ�ϳ�����
						if (!vec_index.empty()) {
							temp_index = vec_index.at(
								rand() % vec_index.size());
						}

						// �жϿ�������
						if (roundNumber_ <= 6 && roundNumber_ >= 0) {
							// ���������ж�
							int sign_index = 0;
							for (int i = (int)enDirection::South;
								i <= (int)enDirection::East; ++i) {
								if (mahjong_[i] == nullptr || i == (int)direction_)
									continue;

								// �鿴���ӵ�е�����
								for (auto idx : vec_index) {
									if (2 == mahjong_[i]->have(SRAnalysis::switchToCardData(idx))) {
										sign_index = idx;
									}
								}
							}
							// �ж��Ƿ��и������Ʊ�׼������
							if (sign_index != 0 && temp_index != sign_index) {
								(*out_card) = SRAnalysis::switchToCardData(sign_index);
								(*out_card_count) = 1;
								break;
							}
						} // end ���������жϽ���

						  // ��������۾�����
						for (auto x : vec_index) {
							const int& temp = x % 9;
							if (temp <= 1 || temp >= 7) {
								temp_index = x;
								break;
							}
						}


						
						(*out_card) = SRAnalysis::switchToCardData(temp_index);
						(*out_card_count) = 1;
						break;
					}
				}

			}
			
		}


		return -1;
	} while (false);


	//for (int i = 0; i < *out_card_count; ++i)
	//	pmj->delCard(*out_card);

	return WIK_NULL;
}

int SRRobot::analysisOutCard(unsigned char * out_card, unsigned char * out_card_count)
{	
	return getNewOutCard(out_card, out_card_count);

	// ����У��
	if (out_card == nullptr || out_card_count == nullptr)
		return -87;

	// ����ɫ����
	SRMahjong* pmj = nullptr;
	if (direction_ != enDirection::None)
		pmj = mahjong_[direction_];
	if (pmj == nullptr)
		return -1;
	pmj->upCardIndex();

	srand((unsigned int)time(0));
	// �ж�����
	if (0 == SRAnalysis::isWin(pmj->data(), pmj->length())) {
		return WIK_CHI_HU;
	}


	// ���Ʒ���
	unsigned char temp_discard[MAX_COUNT];
	memset(temp_discard, 0, sizeof(temp_discard));
	if (isTing_ > 0 || (isTing_ = SRAnalysis::isTing(pmj->data(),
		pmj->length(), temp_discard, arrTing_, &numTing_)) > 0) {
		// ����������ͳ������	
		for (int i = 0; i < numTing_; ++i) {
			// ��������
			if (arrTing_[i] == 0)
				continue;

			// ���ɲ�
			if (invisibleMahjongPool_ == nullptr) {
				// �鿴�齫�Ƿ�����ǽ֮��
				int pool_idx = invisibleMahjongPool_->find(arrTing_[i]);

				if (pool_idx < 0) {
					// ������ǽ֮�ϣ�����Ƿ����Ƴ�֮��
					//visibleMahjongPool_->find(arrTing_[i]);

					// �����������Ƿ����������������
					for (int i = 0; i < numTing_; ++i) {

						// ����Ƿ����������
						for (int player = enDirection::South; player <= enDirection::East; ++player) {

							// ���ɲ�
							if (mahjong_[player] == nullptr)
								continue;

							if (0 < mahjong_[player]->have(arrTing_[i])) {
								// ������Ƿ�ɽ����˳��
								if (false) {
									arrTing_[i] = 0;
								}
								else {
									break;
								}
							}
						}
					}
				}

			}
			else {
				// ����Ƴ�֮���м��ſ�������
				int num = visibleMahjongPool_->have(arrTing_[i]);
				num += pmj->have(arrTing_[i]);
				if (num == 4) {
					// �޷�����
				}
			}


		}

		// ����Ƿ��ѳ�����
		{
			int temp_die = 0;
			for (int i = 0; i < numTing_; ++i)
				if (arrTing_[i] == 0)
					++temp_die;

			if (temp_die == numTing_) {
				// ˵���Ѿ����ƿ����������Բ�����Ϊ��
			}
		}





		*out_card = temp_discard[0];
		*out_card_count = 1;
		pmj->delCard(*out_card);

		return WIK_LISTEN;
	}


	// ��·����
	do {
		// �и��ȸ�
		for (unsigned char i = 0, s = 0; i < MAX_INDEX; ++i) {
			s = pmj->index(i);
			if (s == 4) {
				// ����������Ƶ�����£�������� �Ƿ�������, �����ǲ������ͻ��ĸ���
				int i = 0;

				*out_card = SRAnalysis::switchToCardData(s);
				*out_card_count = 4;


				return WIK_GANG;
			}
		}


		//// �е����ķ���������
		std::vector<int> vec_index;
		{
			for (int idx = 0; (idx = pmj->getFanPaiOne(idx)) != -1; ++idx) {
				vec_index.push_back(idx);
			}
			if (!vec_index.empty()) {
				int i = rand() % vec_index.size();
				int temp = vec_index.at(i);
				// ���������ж�
				for (int i = 0; i < 4; ++i) {
					if (mahjong_[i] == nullptr && i != (int)direction_)
						continue;

					// ���кü��ţ��ȴ���������ģ��Դﵽ�������Ƶ�Ч��
					for (auto idx : vec_index) {
						if (2 <= mahjong_[i]->have(SRAnalysis::switchToCardData(idx))) {
							temp = idx;
						}
					}
				}

				*out_card = SRAnalysis::switchToCardData(temp);
				*out_card_count = 1;
				break;
			}
		}

		// ������й���2����λ�Ĳ���������  [122334 7] 
		{
			vec_index.clear();
			for (int idx = 0; (idx = pmj->getIntervalTwo(idx)) != -1; ++idx) {
				if (pmj->index((unsigned char)idx) >= 2) {
					// �ж��Ƿ�Ψһ����
					continue;
				}
				vec_index.push_back(idx);
			}
			if (!vec_index.empty()) {
				int i = rand() % vec_index.size();
				int temp_index = vec_index.at(i);

				// ��������۾�����
				for (auto x : vec_index) {
					const int& temp = x % 9;
					if (temp <= 1 || temp >= 7) {
						temp_index = x;
						break;
					}
				}

				// ���������ж�
				for (int i = 0; i < 4; ++i) {
					if (mahjong_[i] == nullptr && i != (int)direction_)
						continue;

					// ���кü��ţ��ȴ���������ģ��Դﵽ�������Ƶ�Ч��
					for (auto idx : vec_index) {
						if (2 <= mahjong_[i]->have(SRAnalysis::switchToCardData(idx))) {
							temp_index = idx;
						}
					}
				}
				*out_card = SRAnalysis::switchToCardData(temp_index);
				*out_card_count = 1;
				break;
			}

		}

		// ������пɹ�����Ĳ��������� [1 3 567]   
		{
			vec_index.clear();
			for (int idx = 0; (idx = pmj->getIntervalOne(idx)) != -1; ++idx) {
				if (pmj->index((unsigned char)idx) >= 2) {
					// �ж��Ƿ�Ψһ����
					continue;
				}
				vec_index.push_back(idx);
			}
			// ����Ƿ��е��ƿɳ�
			if (!vec_index.empty()) {
				// ![����] ȷ��������Ʋ��ǽ��Ƽ������ϣ����ⲻ��Ψһ����

				int i = rand() % vec_index.size();
				int temp_index = vec_index.at(i);
				// ��������۾�����
				for (auto x : vec_index) {
					const int& temp = x % 9;
					if (temp <= 1 || temp >= 7) {
						temp_index = x;
						break;
					}
				}
				*out_card = SRAnalysis::switchToCardData(temp_index);
				*out_card_count = 1;
				break;
			}
		}


		// ��� 1233 1223  7789 �����Ľ���,��Ϊ�޽�������
		{
			vec_index.clear();
			for (int idx = 0; (idx = pmj->getShunDopant(idx)) != -1; ++idx) {
				vec_index.push_back(idx);
			}
			// ����Ƿ����ƿɳ�
			if (!vec_index.empty()) {
				int i = rand() % vec_index.size();
				int temp_index = vec_index.at(i);
				// ��������۾�����
				for (auto x : vec_index) {
					const int& temp = x % 9;
					if (temp <= 1 || temp >= 7) {
						temp_index = x;
						break;
					}
				}
				*out_card = SRAnalysis::switchToCardData(temp_index);
				*out_card_count = 1;
				break;
			}

		}


		{
			vec_index.clear();
			for (int idx = 0; (idx = pmj->getDanDui(idx)) != -1; ++idx) {
				vec_index.push_back(idx);
			}
			// ����Ƿ����ƿɳ�
			if (!vec_index.empty()) {
				int temp_index = vec_index.at(0);

				// ������ѳ���
				for (auto v_index : vec_index) {
					// ȷ������ [122,223]
					unsigned char temp_dui = v_index;
					unsigned char temp_dan = v_index + 1;
					if (pmj->index(v_index) == 1) {
						// [122]
						temp_dui = v_index + 1;
						temp_dan = v_index;
					}

					// �������Ψһ���ƣ������
					if (vec_index.size() == 1) {
						temp_index = temp_dan;
						break;
					}


					// ��������Ѿ�������������Ƴ�֮��������
					if (2 == visibleMahjongPool_->have(SRAnalysis::switchToCardData(temp_dui))) {
						temp_index = temp_dui;
						break;
					}

					// ���� [122 || 899] �������
					if (temp_dan % 9 == 0 || temp_dui % 9 == 8) {
						temp_index = temp_dan;
						break;
					}

					// ����������п�������������������š�  
					// ���� A���� [12357] ���Ǽҵ����� [455],��� 4
					for (int i = 0; i < 4; ++i) {
						if (mahjong_[i] == nullptr && i == (int)direction_)
							continue;

						if (0 != mahjong_[i]->getIntervalOne(SRAnalysis::switchToCardData(temp_dui))) {
							temp_index = temp_dan;
						}

					}

				}

				*out_card = SRAnalysis::switchToCardData(temp_index);
				*out_card_count = 1;
				break;
			}
		}

		// ������зǿ̷�˳����
		{
			vec_index.clear();
			for (int idx = 0; (idx = pmj->getNotShunKe(idx)) != -1; ++idx) {
				vec_index.push_back(idx);
			}
			// ����Ƿ��ж���
			for (auto iter_begin = vec_index.begin(); iter_begin != vec_index.end();
				++iter_begin) {
				if (*iter_begin == 2) {
					iter_begin = vec_index.erase(iter_begin);
				}
			}
			// ����Ƿ����ƿɳ�
			if (!vec_index.empty()) {
				
					
				int i = rand() % vec_index.size();
				int temp_index = vec_index.at(i);


				*out_card = SRAnalysis::switchToCardData(temp_index);
				*out_card_count = 1;
				break;
			}
		}

		// ���������е����˵�����ͱȽϸ����ˣ���Ҫ����Ȩ�ظ��������ȷ���
		*out_card = pmj->getLastTouchCard();
		*out_card_count = 1;
	} while (false);


	return WIK_NULL;
}

int SRRobot::analysisCard(unsigned char * out_card, unsigned char * out_card_count)
{
	if (out_card == nullptr || out_card_count == nullptr)
		return -87;

	// ����ɫ����
	SRMahjong* pmj = nullptr;
	if (direction_ != enDirection::None)
		pmj = mahjong_[direction_];
	if (pmj == nullptr)
		return -1;
	pmj->upCardIndex();

	srand((unsigned int)time(0));
	// �ж�����
	if (0 == SRAnalysis::isWin(pmj->data(), pmj->length())) {
		return WIK_CHI_HU;
	}


	// ���Ʒ���
	unsigned char temp_discard[MAX_COUNT];
	memset(temp_discard, 0, sizeof(temp_discard));
	if (isTing_ > 0 || (isTing_ = SRAnalysis::isTing(pmj->data(),
		pmj->length(), temp_discard, arrTing_, &numTing_)) > 0) {
		// ����������ͳ������	
		for (int i = 0; i < numTing_; ++i) {
			// ��������
			if (arrTing_[i] == 0)
				continue;

			// ���ɲ�
			if (invisibleMahjongPool_ == nullptr) {
				// �鿴�齫�Ƿ�����ǽ֮��
				int pool_idx = invisibleMahjongPool_->find(arrTing_[i]);

				if (pool_idx < 0) {
					// ������ǽ֮�ϣ�����Ƿ����Ƴ�֮��
					//visibleMahjongPool_->find(arrTing_[i]);

					// �����������Ƿ����������������
					for (int i = 0; i < numTing_; ++i) {

						// ����Ƿ����������
						for (int player = enDirection::South; player <= enDirection::East; ++player) {

							// ���ɲ�
							if (mahjong_[player] == nullptr)
								continue;

							if (0 < mahjong_[player]->have(arrTing_[i])) {
								// ������Ƿ�ɽ����˳��
								if (false) {
									arrTing_[i] = 0;
								}
								else {
									break;
								}
							}
						}
					}
				}

			}
			else {
				// ����Ƴ�֮���м��ſ�������
				int num = visibleMahjongPool_->have(arrTing_[i]);
				num += pmj->have(arrTing_[i]);
				if (num == 4) {
					// �޷�����
				}
			}


		}

		// ����Ƿ��ѳ�����
		{
			int temp_die = 0;
			for (int i = 0; i < numTing_; ++i)
				if (arrTing_[i] == 0)
					++temp_die;

			if (temp_die == numTing_) {
				// ˵���Ѿ����ƿ����������Բ�����Ϊ��
			}
		}





		*out_card = temp_discard[0];
		*out_card_count = 1;
		pmj->delCard(*out_card);

		return WIK_LISTEN;
	}


	// ��·����
	do {
		// �и��ȸ�
		for (unsigned char i = 0, s = 0; i < MAX_INDEX; ++i) {
			s = pmj->index(i);
			if (s == 4) {
				// ����������Ƶ�����£�������� �Ƿ�������, �����ǲ������ͻ��ĸ���
				int i = 0;

				*out_card = SRAnalysis::switchToCardData(s);
				*out_card_count = 4;


				return WIK_GANG;
			}
		}


		//// �е����ķ���������
		std::vector<int> vec_index;
		{
			for (int idx = 0; (idx = pmj->getFanPaiOne(idx)) != -1; ++idx) {
				vec_index.push_back(idx);
			}
			if (!vec_index.empty()) {
				for (auto temp : vec_index) {
					*out_card = SRAnalysis::switchToCardData(temp);
					out_card++;
					*out_card_count += 1;
				}
			}
		}

		// ������й���2����λ�Ĳ���������  [122334 7] 
		{

			vec_index.clear();
			for (int idx = 0; (idx = pmj->getIntervalTwo(idx)) != -1; ++idx) {
				if (pmj->index((unsigned char)idx) >= 2) {
					// �ж��Ƿ�Ψһ����
					continue;
				}
				vec_index.push_back(idx);
			}
			if (!vec_index.empty()) {
				for (auto temp : vec_index) {
					*out_card = SRAnalysis::switchToCardData(temp);
					out_card++;
					*out_card_count += 1;
				}
			}

		}




		// ������пɹ�����Ĳ��������� [1 3 567]   
		{
			vec_index.clear();
			for (int idx = 0; (idx = pmj->getIntervalOne(idx)) != -1; ++idx) {
				if (pmj->index((unsigned char)idx) >= 2) {
					// �ж��Ƿ�Ψһ����
					continue;
				}
				vec_index.push_back(idx);
			}
			// ����Ƿ��е��ƿɳ�
			if (!vec_index.empty()) {
				for (auto temp : vec_index) {
					*out_card = SRAnalysis::switchToCardData(temp);
					out_card++;
					*out_card_count += 1;
				}
			}
		}


		// ��� 1233 1223  7789 �����Ľ���,��Ϊ�޽�������
		{
			vec_index.clear();
			for (int idx = 0; (idx = pmj->getShunDopant(idx)) != -1; ++idx) {
				vec_index.push_back(idx);
			}
			// ����Ƿ����ƿɳ�
			if (!vec_index.empty()) {
				for (auto temp : vec_index) {
					*out_card = SRAnalysis::switchToCardData(temp);
					out_card++;
					*out_card_count += 1;
				}
			}

		}

		{
			vec_index.clear();
			for (int idx = 0; (idx = pmj->getDanDui(idx)) != -1; ++idx) {
				vec_index.push_back(idx);
			}
			// ����Ƿ����ƿɳ�
			if (!vec_index.empty()) {
				int temp_index = vec_index.at(0);

				for (auto v_index : vec_index) {
					

					*out_card = SRAnalysis::switchToCardData(v_index);
					out_card++;
					*out_card_count += 1;

				}


				break;
			}
		}

	} while (false);


	return WIK_NULL;
}

int SRRobot::getAction(enDirection drc, unsigned char card) {
	// �������
	if (!SRAnalysis::isValidCard(card) || drc == enDirection::None)
		return -87;

	// �䱸����
	SRMahjong* pmj = nullptr;
	if (direction_ != enDirection::None)
		pmj = mahjong_[direction_];

	if (pmj == nullptr)
		return -1;

	// ����ɺ�
	SRMahjong temp_mj(*pmj);
	temp_mj.addCard(card);

	if (0 == SRAnalysis::isWin(temp_mj.data(), temp_mj.length())) {
		return WIK_CHI_HU;
	}

	int have_card_count = pmj->have(card);
	// �������ܣ��Ĵ��齫ֻ�����ܣ�
	if (have_card_count == 3) {
		// �����߼�����
		pmj->delCard(card);
		pmj->delCard(card);
		pmj->delCard(card);
		return WIK_GANG;
	}
	else if (have_card_count == 2) {
		// �����߼�����  
		pmj->delCard(card);
		pmj->delCard(card);
		return WIK_PENG;
	}
	
	return WIK_NULL;
}

void SRRobot::reset(void) {

	// �Ƴ��е��齫
	if (visibleMahjongPool_ != nullptr)
		delete visibleMahjongPool_;
	visibleMahjongPool_ = nullptr;
	// ��ǽ�ϵ��齫				 
	if (invisibleMahjongPool_ != nullptr)
		delete invisibleMahjongPool_;
	invisibleMahjongPool_ = nullptr;

	// ���з�λ���齫
	for (int i = 0; i < sizeof(mahjong_) / sizeof(mahjong_[0]); ++i) {
		if (mahjong_[i] != nullptr)
			delete mahjong_[i];
		mahjong_[i] = nullptr;
	}

	// �����Ƿ����
	isTing_ = -1;
	// ������
	memset(arrTing_, 0, sizeof(arrTing_));
	// ����������
	numTing_ = 0;
}

void SRRobot::setDirection(enDirection drc) {
	direction_ = drc;
}

enDirection SRRobot::getDirection(void) const {
	return direction_;
}

void SRRobot::setVisibleMahjongPool(SRVisibleMahjongPool * pool) {
	visibleMahjongPool_ = pool;
}

void SRRobot::setInvisibleMahjongPool(SRInvisibleMahjongPool * pool) {
	invisibleMahjongPool_ = pool;
}

SRMahjong * SRRobot::getMahjong(void) {
	return mahjong_[direction_];
}

const SRMahjong * SRRobot::getMahjong(enDirection drc) const {
	return mahjong_[drc];
}

void SRRobot::setMahjong(enDirection drc, SRMahjong * mahjong) {
	mahjong_[drc] = mahjong;
}

