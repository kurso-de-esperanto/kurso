#include "video_nova.h"
#include "ui_video_nova.h"
//#include <QQuickView>
#include <QtQuickWidgets/QQuickWidget>
#include <QLayout>
#include <funkcioj.h>

video_nova::video_nova(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::video_nova)
{
    ui->setupUi(this);



    //QQuickView *view = new QQuickView(QUrl("qrc:/video.qml"));

    //QQuickView *view = new QQuickView(QUrl("qrc:/videoludilo.qml"));

    QQuickWidget *view = new QQuickWidget;

    view->setSource(QUrl("qrc:/videoludilo.qml"));


    //QWidget *container = QWidget::createWindowContainer(view, this);

    //container->setMinimumSize(320, 240);
    //container->setMaximumSize(320, 240);
    //container->setFocusPolicy(Qt::TabFocus);

    /*
    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(view);

    this->setLayout(mainLayout);
    */

    //view->setSource(QUrl("qrc:/video.qml"));

    view->show();


}

video_nova::~video_nova()
{
    delete ui;
}
