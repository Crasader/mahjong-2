// srmjrobot.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "srmjrobot.h"
#include "SRMahjong.h"	  
#include "SRMahjongPool.h"
#include "SRAnalysis.h"


SRRobot::SRRobot(void) {
	reset();
	std::cout << "hello robot!" << std::endl;
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
		//{
		//	for (int idx = 0; (idx = pmj->getFanPaiOne(idx)) != -1;++idx) {
		//		vec_index.push_back(idx);
		//	}
		//	if (!vec_index.empty()) {
		//		int i = rand() % vec_index.size();
		//		int temp = vec_index.at(i);
		//		// ������Ը���һ��
		//		for (int i = 0; i < 4; ++i) {
		//			if (mahjong_[i] == nullptr && i != (int)direction_)
		//				continue;

		//			// ���кü��ţ��ȴ���������ģ��Դﵽ�������Ƶ�Ч��
		//			for (auto idx : vec_index) {
		//				if (2 <= mahjong_[i]->have(idx)) {
		//					temp = idx;
		//				}
		//			}
		//		}

		//		*out_card = SRAnalysis::switchToCardData(temp);
		//		*out_card_count = 1;
		//		break;
		//	}
		//}

		// ������й���2����λ�Ĳ���������  [122334 7] 
		//{

		//	vec_index.clear();
		//	for (int idx = 0; (idx = pmj->getIntervalTwo(idx)) != -1;++idx) {
		//		if (pmj->index((unsigned char)idx) >= 2) {
		//			// �ж��Ƿ�Ψһ����
		//			continue;
		//		}
		//		vec_index.push_back(idx);
		//	}
		//	if (!vec_index.empty()) {
		//		int i = rand() % vec_index.size();
		//		int temp_index = vec_index.at(i);

		//		// ��������۾�����
		//		for (auto x : vec_index) {
		//			const int& temp = x % 9;
		//			if (temp <= 1 || temp >= 7) {
		//				temp_index = x;
		//				break;
		//			}
		//		}

		//		*out_card = SRAnalysis::switchToCardData(temp_index);
		//		*out_card_count = 1;
		//		break;
		//	}

		//}

		


		// ������пɹ�����Ĳ��������� [1 3 567]   
		//{
		//	vec_index.clear();
		//	for (int idx = 0; (idx = pmj->getIntervalOne(idx)) != -1;++idx) {
		//		if (pmj->index((unsigned char)idx) >= 2) {
		//			// �ж��Ƿ�Ψһ����
		//			continue;
		//		}
		//		vec_index.push_back(idx);
		//	}
		//	// ����Ƿ��е��ƿɳ�
		//	if (!vec_index.empty()) {
		//		// ![����] ȷ��������Ʋ��ǽ��Ƽ������ϣ����ⲻ��Ψһ����

		//		int i = rand() % vec_index.size();
		//		int temp_index = vec_index.at(i);
		//		// ��������۾�����
		//		for (auto x : vec_index) {
		//			const int& temp = x % 9;
		//			if (temp <= 1 || temp >= 7) {
		//				temp_index = x;
		//				break;
		//			}
		//		}
		//		*out_card = SRAnalysis::switchToCardData(temp_index);
		//		*out_card_count = 1;
		//		break;
		//	}
		//}


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



		// ���������е����˵�����ͱȽϸ����ˣ���Ҫ����Ȩ�ظ��������ȷ���
		*out_card = pmj->getLastTouchCard();
		*out_card_count = 1;
	} while (false);

	// ɾ���������
	for (int i = 0; i < (*out_card_count); ++i)
		pmj->delCard(*out_card);

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

	// �������ܣ��Ĵ��齫ֻ�����ܣ�
	for (unsigned char i = 0; i < MAX_INDEX; ++i) {
		if (pmj->index(i) == 3) {
			// �����߼�����
			return WIK_GANG;
		}
		else if (pmj->index(i) == 2) {
			// �����߼�����
			return WIK_PENG;
		}
	}
	return WIK_NULL;
}

void SRRobot::reset(void) {	
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

const SRMahjong * SRRobot::getMahjong(void) const {
	return mahjong_[direction_];
}

const SRMahjong * SRRobot::getMahjong(enDirection drc) const {
	return mahjong_[drc];
}

void SRRobot::setMahjong(enDirection drc, SRMahjong * mahjong) {
	mahjong_[drc] = mahjong;
}

