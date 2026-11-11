/*
    Kurso de Esperanto - a free multimedia course to teach yourself the
    international language.
    Copyright (C) 2000-2012 Carlos Alberto Alves Pereira
    karlo@kurso.com.br

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3 as
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    Kurso de Esperanto - multrimeda komputila kurso por memlernado de
    la internacia lingvo.
    Kopirajto (C) 2000-2012 Carlos Alberto Alves Pereira
    karlo@kurso.com.br

    Tiu ĉi programo estas libera softvaro: vi povas ĝin redisdoni aŭ
    ĝin modifi laŭ la kondiĉoj de GNU-a Ĝenerala Publika Uzpermeso versio 3
    kiel publikigita de Free Software Foundation.

    Tiu ĉi programo estas disdonita kun la espero, ke ĝi estos utila,
    sed sen ia garantio; eĉ sen la implica garantio de komercebleco aŭ
    taŭgeco por specifa celo. Vidu la GNU-an Ĝeneralan Publikan Uzpermeson
    por pliaj detaloj.

    Vi devus esti ricevinta kopion de la GNU-a Ĝenerala Publika Uzpermeso
    kune kun ĉi tiu programo. Se ne, iru al <http://www.gnu.org/licenses/>.
*/

#include "lec02.h"
#include "ui_lec02.h"
#include "kurso.h"
#include "funkcioj.h"
#include <QScroller>

#ifdef Q_OS_ANDROID
#include <QQuickView>
#include <QQuickWidget>
#else
#include "videoludilo.h"
#endif



lec02::lec02(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::lec02)
{
    ui->setupUi(this);

    QScroller::grabGesture(this->ui->scrollArea->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_2->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_3->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_4->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_5->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_6->viewport(), QScroller::LeftMouseButtonGesture);




#ifdef Q_OS_ANDROID

    QQuickView *view = new QQuickView;

    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setSource(QUrl("qrc:/videoludilo.qml"));

    QWidget *container = QWidget::createWindowContainer(view);

    container->setMinimumSize(352, 272);
    container->setMaximumSize(352, 272);
    container->setFocusPolicy(Qt::TabFocus);


    QVBoxLayout *layout = new QVBoxLayout;
    QVBoxLayout *layout_tab_16 = dynamic_cast<QVBoxLayout*>(this->ui->tab_16->layout());
    layout_tab_16->insertWidget(0,container,0, Qt::AlignLeft);

    layout->addWidget(this->ui->Lec02_Label50);
    layout->addWidget(this->ui->Lec02_Label49);
    QHBoxLayout *vinilkosmo = new QHBoxLayout;
    vinilkosmo->addWidget(this->ui->label);
    vinilkosmo->addWidget(this->ui->label_21);
    layout->addLayout(vinilkosmo);
    QSpacerItem *spacilo = new QSpacerItem(1,1,  QSizePolicy::Fixed, QSizePolicy::Expanding);
    spacilo->expandingDirections().setFlag(Qt::Vertical, true);
    layout->addSpacerItem(spacilo);
    this->ui->scrollAreaWidgetContents_6->setLayout(layout);

#else
    videoludilo *videujo = new videoludilo(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(videujo);

    layout->addWidget(this->ui->Lec02_Label50);
    layout->addWidget(this->ui->Lec02_Label49);
    QHBoxLayout *vinilkosmo = new QHBoxLayout;
    vinilkosmo->addWidget(this->ui->label);
    vinilkosmo->addWidget(this->ui->label_21);
    layout->addLayout(vinilkosmo);
    QSpacerItem *spacilo = new QSpacerItem(1,1,  QSizePolicy::Fixed, QSizePolicy::Expanding);
    spacilo->expandingDirections().setFlag(Qt::Vertical, true);
    layout->addSpacerItem(spacilo);
    this->ui->scrollAreaWidgetContents_6->setLayout(layout);
#endif


}

lec02::~lec02()
{
    delete ui;
}



void lec02::on_Lec02_currentChanged(int index)
{
    kurso *chefa_fenestro = dynamic_cast<kurso*>(QApplication::activeWindow());

    // la sekvanta kodo estas por chirkauiri cimon en QT (5.14), kiu ne automate ghustigas la rulujojn (QScrollArea)
    QList<QScrollArea *> chiuj_rulujoj = ui->Lec02->currentWidget()->findChildren<QScrollArea  *>();
    int i;
    for (i=0; i < chiuj_rulujoj.count(); i++) {
        chiuj_rulujoj.at(i)->setWidgetResizable(true);
    }


    if (chefa_fenestro != nullptr) {
        chefa_fenestro->montras_koverton(ui->Lec02->currentWidget()->objectName().left(6) == "Sendas", index);
    }

}
