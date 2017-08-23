#ifndef SRMAHJONGSEATWIDGET_H
#define SRMAHJONGSEATWIDGET_H

#include <QList>
#include <QWidget>

class SRMahjongWidget;

class SRMahjongSeatWidget : public QWidget
{
    Q_OBJECT
public:

    enum enDirection {
        South = 0,              //���� ��
        West,					//���� ��
        North,                  //���� ��
        East,					//���� ��
    };

    explicit SRMahjongSeatWidget(QWidget *parent = nullptr);

signals:

public:

    void setDirection(enDirection drc);

public slots:


protected:

    virtual void paintEvent(QPaintEvent *event);

private:



private:
    // һ��λ��Ӧ�þ߱�����
    enDirection direction_;

    QList<SRMahjongWidget*> listMahjong_;

};

#endif // SRMAHJONGSEATWIDGET_H
