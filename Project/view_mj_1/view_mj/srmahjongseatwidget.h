#ifndef SRMAHJONGSEATWIDGET_H
#define SRMAHJONGSEATWIDGET_H
#include "srmjglobal.h"
#include <QList>
#include <QWidget>
class QPushButton;
class SRMahjongWidget;
class SRMahjongHallWidget;
class SRMahjongSeatHallWidget;

class SRRobot;
class SRMahjong;

class SRMahjongSeatWidget : public QWidget
{
    Q_OBJECT
public:


    explicit SRMahjongSeatWidget(QWidget *parent = nullptr);

    void setRobot(SRRobot* robot);

    void setMahjong(SRMahjong* mahjong);

    void setHallWidget(SRMahjongHallWidget* hall) {hallWidget_ = hall;}

signals:
    // �����ź�
    void sigOutCard(enDirection direction, unsigned char data);

    // ��
    void sigHu(enDirection direction);

    // ������Ϊ ��� �г� �ҳ� �� ��
    void sigAction(enDirection direction, int action, unsigned char data);
public:

    void setDirection(enDirection drc);
    enDirection getDirection(void) {return direction_;}


    // ����
    void touchCard(unsigned char data);

    void upMahjongBox(void);
public slots:


    // ��ҳ���
    void onPlayerOutCard(enDirection drc, unsigned char data);

private slots:

    // ��˫�� - ���Ƶ���˼
    void onMahjongKnockout(QWidget* object);

    void onTouchCard(void);
    void onAnalysisOutCard(void);
    void onAnalysisCard(void);

protected:
    // ����
    void mahjongKnockout(unsigned char card);

    virtual void paintEvent(QPaintEvent *event);



private:
    SRMahjongHallWidget* hallWidget_;

    // һ��λ��Ӧ�þ߱�����
    enDirection direction_;

    QList<SRMahjongWidget*> listMahjong_;

    unsigned char lastOutCard_;

    SRRobot* robot_;

    SRMahjong * mahjong_;

    QPushButton* touchCard_;
    QPushButton* analysisOutCard_;
    QPushButton* analysisCard_;

    SRMahjongSeatHallWidget* seatHallWidget_;
};

#endif // SRMAHJONGSEATWIDGET_H
