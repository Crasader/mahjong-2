#ifndef SRMAHJONGTABLEWIDGET_H
#define SRMAHJONGTABLEWIDGET_H

#include <srmjglobal.h>
#include <QWidget>

class SRMahjongSeatWidget;
class SRMahjongHallWidget;
class SRRobot;
class SRMahjongTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SRMahjongTableWidget(QWidget *parent = nullptr);

signals:
    // ������ҳ���
    void sigAskPlayerOutCard(enDirection drc);


public slots:

    void onOpen(void);

    // �����Ϊ ���� �� ����
    void onPlayerAction(enDirection direction, int action, unsigned char data);

    void onDealCard(enDirection direction, unsigned char data);

protected:

    virtual void paintEvent(QPaintEvent *event);


private:


    void initSeatLayout(void);

private:
    SRMahjongHallWidget* hallWidget_;
    SRMahjongSeatWidget* seatWidget_[4];

    SRRobot* robot_[4];

    // ��ǰ���Ƶ�Ŀ�귽��
    enDirection drcTarget_;


};

#endif // SRMAHJONGTABLEWIDGET_H
