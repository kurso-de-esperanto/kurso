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

#include "lec10.h"
#include "ui_lec10.h"
#include "kurso.h"
#include <QScroller>

lec10::lec10(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::lec10)
{
    ui->setupUi(this);

    QScroller::grabGesture(this->ui->scrollArea->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_2->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_3->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_4->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_10->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_6->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_7->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_8->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_9->viewport(), QScroller::LeftMouseButtonGesture);

}

lec10::~lec10()
{
    delete ui;
}

void lec10::on_Lec10_currentChanged(int index)
{
    kurso *chefa_fenestro = dynamic_cast<kurso*>(QApplication::activeWindow());
    // la sekvanta kodo estas por chirkauiri cimon en QT (5.14), kiu ne automate ghustigas la rulujojn (QScrollArea)
    QList<QScrollArea *> chiuj_rulujoj = ui->Lec10->currentWidget()->findChildren<QScrollArea  *>();
    int i;
    for (i=0; i < chiuj_rulujoj.count(); i++) {
        chiuj_rulujoj.at(i)->setWidgetResizable(true);
    }
    if (chefa_fenestro != nullptr)
        chefa_fenestro->montras_koverton(ui->Lec10->currentWidget()->objectName().left(6) == "Sendas", index);
}
