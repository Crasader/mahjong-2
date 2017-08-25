#ifndef SRMAHJONGSEATWIDGET_H
#define SRMAHJONGSEATWIDGET_H
#include "srmjglobal.h"
#include <QList>
#include <QWidget>

class SRMahjongWidget;
class SRRobot;
class SRMahjong;
class SRMahjongSeatWidget : public QWidget
{
    Q_OBJECT
public:


    explicit SRMahjongSeatWidget(QWidget *parent = nullptr);

    void setRobot(SRRobot* robot);

    void setMahjong(SRMahjong* mahjong);

signals:
    // �����ź�
    void sigOutCard(enDirection direction, unsigned char data);

    // ��
    void sigHu(enDirection direction);

    // ������Ϊ ��� �г� �ҳ� �� ��
    void sigAction(enDirection direction, int action, BYTE data);
public:

    void setDirection(enDirection drc);
    enDirection getDirection(void) {return direction_;}


    // ����
    void touchCard(unsigned char data);

public slots:


    // ��ҳ���
    void onPlayerOutCard(unsigned char data);

private slots:

    // ��˫�� - ���Ƶ���˼
    void onMahjongKnockout(QWidget* object);

protected:

    virtual void paintEvent(QPaintEvent *event);

private:

    void upMahjongBox(void);

private:
    // һ��λ��Ӧ�þ߱�����
    enDirection direction_;

    QList<SRMahjongWidget*> listMahjong_;

    SRRobot* robot_;

    SRMahjong * mahjong_;

};

#endif // SRMAHJONGSEATWIDGET_H
