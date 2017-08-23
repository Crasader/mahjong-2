#include "srmainwindow.h"
#include "srmahjongtablewidget.h"

#include <QAction>
#include <QDebug>
#include <QLabel>
#include <QToolBar>
#include <QMenu>
#include <QStatusBar>
#include <QMenuBar>
#include <QBoxLayout>

SRMainWindow::SRMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // ��ʼ���������
    setMinimumSize(1000,1000);
    initMenu();

    // �������Ĵ���
    mahjongTable_ = new SRMahjongTableWidget();
    setCentralWidget(mahjongTable_);
}

SRMainWindow::~SRMainWindow()
{
}

void SRMainWindow::open()
{
    qDebug() << "Game Start.";
}

void SRMainWindow::initMenu()
{
    // ������ǩ
    QAction* openAction = new QAction(tr("&Start"), this);
    openAction->setStatusTip(tr("Game Start."));
    openAction->setIcon(QIcon(":/images/UI_UI_BMP_FILE_SELECTOR_DISABLED_DIRECTORY.png"));

    connect(openAction,SIGNAL(triggered()),this,SLOT(open()));

    QLabel* msgLabel = new QLabel;
    msgLabel->setMaximumSize(msgLabel->sizeHint());
    msgLabel->setAlignment(Qt::AlignHCenter);
    statusBar()->addWidget(msgLabel);
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));

    /*
     *QMainWindow��һ��menuBar()�������᷵�ز˵���������������ڻ��Զ�����������Ѿ����ھͷ����Ǹ��� ������ָ�롣
     *ֱ��ʹ�÷���ֵ���һ���˵���Ҳ����addMenu��������һ��QString��Ҳ������ʾ�Ĳ˵����֡�Ȼ��ʹ�����QMenuָ��������QAction��
     */
    QMenu *file = menuBar()->addMenu(tr("&Game"));
    file->setStatusTip(tr("Game Action"));
    file->addAction(openAction);
}
