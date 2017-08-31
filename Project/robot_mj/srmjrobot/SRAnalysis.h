#ifndef _SHANREN_ANALYSIS_H_
#define _SHANREN_ANALYSIS_H_


#include <vector>
#include <map>

class SRAnalysis
{
public:
	struct stKindKind {

	};

public:
	SRAnalysis();
	virtual ~SRAnalysis();

public:

	//�˿�ת��
	static unsigned char switchToCardIndex(unsigned char cbCardData);

	//�˿�ת��
	static unsigned char switchToCardData(unsigned char cbCardIndex);

	static int isTing(const unsigned char* data, unsigned char count, unsigned char* out_discard,
		unsigned char * out_data = nullptr, unsigned char* out_count = nullptr);

	static int isWin(const unsigned char* data, unsigned char count);

	static bool isValidCard(unsigned char cbCardData);

	// ���Ʒ��� ��Ͳ
	// outCardIndex : �������͵��±�
	static int analysisHuaPai(const unsigned char * cardIndexBegin, const unsigned char* cardIndexEnd,
		unsigned char* outCardIndex, char* outCount);

protected:

	static int isWin(const unsigned char _cardIndex[], int _duiIndex = 0);


	static int getKeAndShun(const unsigned char _cardIndex[]);

	static int isAllKeAndShun(const unsigned char _cardIndex[]);

private:

};

#endif // _SHANREN_ANALYSIS_H_