#ifndef SRPLAYERDESKTOP_H
#define SRPLAYERDESKTOP_H
#include "stdafx.h"
#include <QBoxLayout>
#include <QWidget>
class QPushButton;
class SRPlayerModel;
class SRCardModel;

class SRPlayerDesktop : public QWidget
{
    Q_OBJECT
public:
    explicit SRPlayerDesktop(QWidget *parent = nullptr);

    // �������ģ��
    SRPlayerModel* getModel(void) { return model_; }

    // ���������
    void setDirection(enDirection _direction);
    enDirection getDirection(void);

    // ��÷�����ַ���
    const char * const getDirectionName();


protected:

    virtual void paintEvent(QPaintEvent *event);


signals:

    // �����ź�
    void emOutCard(enDirection direction, BYTE data);

    // ��
    void emHu(enDirection direction, BYTE* data, BYTE count);
    // ��
    void emPeng(enDirection direction, BYTE* data, BYTE count);
    // ��
    void emChi(enDirection direction, BYTE* data, BYTE count);

public slots:

    // ����
    void onDealCard(enDirection direction, BYTE *data, BYTE count);

    // ����
    void onPlayState(BYTE data);

    // �����˵ĳ���
    void onOtherPlayState(enDirection direction, BYTE data);

private:

    SRPlayerModel* model_;

    SRCardModel* cardModel_;

    QList<QPushButton*> listButton_;

    QBoxLayout* layout_;

};

#endif // SRPLAYERDESKTOP_H
