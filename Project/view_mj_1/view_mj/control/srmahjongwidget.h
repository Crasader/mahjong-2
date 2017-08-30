#ifndef SRMAHJONGWIDGET_H
#define SRMAHJONGWIDGET_H

#include <QWidget>
class QPen;
class QLabel;
class SRMahjongWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SRMahjongWidget(QWidget *parent = nullptr);

public:

    unsigned char getCardData(void) {return cardData_;}

public:

    bool operator< (const SRMahjongWidget& other);
    bool operator> (const SRMahjongWidget& other);
    bool operator==(const SRMahjongWidget& other);


public:

    static QString convertToText(unsigned char data);

    void setPen(QPen* pen);

signals:


    void sigDoubleClick(QWidget*);

public slots:

    void onModifyData(unsigned char data);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    /**
     * @brief : �����봰���¼�
     */
    virtual void enterEvent(QEvent *event);
    /**
     * @brief : ����뿪�����¼�
     */
    virtual void leaveEvent(QEvent *event);



    virtual void mouseDoubleClickEvent(QMouseEvent *event);

private:



private:


    QString info_;

    unsigned char cardData_;

    /*  ��ǰչʾ��ͼ��  */
    QPixmap currentPix_;

    /*  ͼ���б�  */
    QList<QPixmap> listPix_;

    QPen* pen_;

};

#endif // SRMAHJONGWIDGET_H
