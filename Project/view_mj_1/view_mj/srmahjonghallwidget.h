#ifndef SRMAHJONGHALLWIDGET_H
#define SRMAHJONGHALLWIDGET_H

#include <srmjglobal.h>

#include <QWidget>

class QGridLayout;
class SRInvisibleMahjongPool;
class SRVisibleMahjongPool;
class SRMahjongWidget;
class SRMahjongSeatHallWidget;

class SRMahjongHallWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SRMahjongHallWidget(QWidget *parent = nullptr);

public:

    // �����ǽ�ϵ���
    SRInvisibleMahjongPool* getInvisibleMahjongPool(void) {return invisibleMahjongPool_;}
    unsigned char getOneCard(void);
    // ����Ƴ��е���
    SRVisibleMahjongPool* getVisibleMahjongPool(void) {return visibleMahjongPool_;}

signals:
    // ����
    void sigDealCard(enDirection direction, unsigned char data);

    // ��ҳ���
    void sigOutCard(enDirection direction, unsigned char data);

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
    // ���ɼ���
    QGridLayout* invisibleLayout_;
    SRInvisibleMahjongPool* invisibleMahjongPool_;
    QList<SRMahjongWidget*> listInvisibleMahjong_;
    // �ɼ���
    QGridLayout* visibleLayout_;
    SRVisibleMahjongPool* visibleMahjongPool_;
    QList<SRMahjongWidget*> listVisibleMahjong_;

    SRMahjongSeatHallWidget* seatHallWidget_[GAME_PLAYER];
    QWidget* hallWidget_;
    QList<SRMahjongWidget*> listUndefineMahjong_;

    unsigned char cbCardDataArray_[MAX_REPERTORY + 1];
};

#endif // SRMAHJONGHALLWIDGET_H
