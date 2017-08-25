#ifndef SRMAHJONGHALLWIDGET_H
#define SRMAHJONGHALLWIDGET_H

#include <srmjglobal.h>

#include <QWidget>

class SRInvisibleMahjongPool;
class SRVisibleMahjongPool;

class SRMahjongHallWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SRMahjongHallWidget(QWidget *parent = nullptr);

public:

    // �����ǽ�ϵ���
    SRInvisibleMahjongPool* getInvisibleMahjongPool(void) {return invisibleMahjongPool_;}
    // ����Ƴ��е���
    SRVisibleMahjongPool* getVisibleMahjongPool(void) {return visibleMahjongPool_;}

signals:
    // ����
    void sigDealCard(enDirection direction, BYTE data);

    // ��ҳ���
    void sigOutCard(enDirection direction, BYTE data);

public slots:

    // ϴ��
    void onShuffle(void);
    // ����
    // direction ������˭
    // count : ��������
    void onDealCard(enDirection direction, BYTE count);

    // �û����ƣ��Ʋ����Ƴ�֮��
    void onOutCardToVisibleMahjongPool(enDirection direction, unsigned char card);


protected:

    virtual void paintEvent(QPaintEvent *event);

private:
    SRInvisibleMahjongPool* invisibleMahjongPool_;
    SRVisibleMahjongPool* visibleMahjongPool_;

    unsigned char cbCardDataArray_[MAX_REPERTORY + 1];
};

#endif // SRMAHJONGHALLWIDGET_H
