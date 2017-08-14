#ifndef SRDESKTOP_H
#define SRDESKTOP_H

#include "stdafx.h"
#include <QWidget>

class SRDesktop : public QWidget
{
    Q_OBJECT
public:
    explicit SRDesktop(QWidget *parent = nullptr);

signals:

    // ����
    void emDealCard(enDirection direction, BYTE *data, BYTE count);

public slots:

    // ϴ��
    void onShuffle(void);


    // ����
    void onDealCard(enDirection direction, BYTE count);

private:

    BYTE cbCardDataArray_[MAX_REPERTORY + 1];

    BYTE index_;



};

#endif // SRDESKTOP_H
