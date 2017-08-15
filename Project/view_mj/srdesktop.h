#ifndef SRDESKTOP_H
#define SRDESKTOP_H

#include "stdafx.h"
#include <QWidget>

class QPushButton;
class QGridLayout;
class QBoxLayout;

class SRDesktop : public QWidget
{
    Q_OBJECT
public:
    explicit SRDesktop(QWidget *parent = nullptr);

signals:

    // ����
    void emDealCard(enDirection direction, BYTE *data, BYTE count);

    // ����
    void emPlayCard(enDirection direction, BYTE data);

public slots:

    // ϴ��
    void onShuffle(void);

    // ����
    void onDealCard(enDirection direction, BYTE count);

    // ����
    void onStart(void);

private:

    BYTE cbCardDataArray_[MAX_REPERTORY + 1];

    BYTE index_;

    QGridLayout* darkCardLayout_;
    QGridLayout* brightnessCardLayout_;
    QBoxLayout* layout_;

    QList<QSharedPointer<QPushButton> > listDarkPushButton_;
    QList<QSharedPointer<QPushButton> > listBrightnessPushButton_;

};

#endif // SRDESKTOP_H
