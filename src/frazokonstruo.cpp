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

#include "frazokonstruo.h"
#include "ui_frazokonstruo.h"
#include "funkcioj.h"
#include <QLabel>
#include <QtCore>
#include <QTime>
#include <QScroller>
#include "flowlayout_nova.h"
#include "neklakebla_nova.h"
#include "klakbutono_nova.h"
#include "korekta.h"
#include <QSpacerItem>




frazokonstruo::frazokonstruo(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::frazokonstruo)
{
    ui->setupUi(this);

    setUpdatesEnabled(false);


    FlowLayout *flowLayout1 = new FlowLayout(6, 9);
    FlowLayout *flowLayout2 = new FlowLayout(12,12);

    int i;
    for (i = 0; i < 18; i++) {
        flowLayout1->addWidget(new QPushButton(QString::number(i)));
    }

    this->ui->Vortoj->setLayout(flowLayout1);


    for (i = 0; i < 18; i++) {
        flowLayout2->addWidget(new QPushButton(QString::number(i)));
    }

    this->ui->Disponeblaj->setLayout(flowLayout2);

    this->ui->Vortoj->setVisible(false);
    this->ui->Disponeblaj->setVisible(false);
    this->ui->Antauen->setVisible(false);
    this->ui->Korekta->setText("");
    this->ui->Traduko1->setText("");

    chiuj_vortoj = this->ui->Vortoj->findChildren<QPushButton *>();
    chiuj_disponeblaj = this->ui->Disponeblaj->findChildren<QPushButton *>();

    QFile file5( ":stiloj/butono_vortoj.qss");
    file5.open(QFile::ReadOnly);
    QString stilo = QLatin1String(file5.readAll());

    for (i = 0; i < chiuj_vortoj.size(); i++) {
        // flowLayout1->setAlignment(chiuj_vortoj.at(i), Qt::AlignHCenter);
        chiuj_vortoj.at(i)->setStyleSheet(stilo);
        chiuj_vortoj.at(i)->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        chiuj_vortoj.at(i)->setVisible(false);
        connect(chiuj_vortoj.at(i), SIGNAL(clicked()), this, SLOT( vortoforigo()));
    }

    QFile file6( ":stiloj/butono_disponeblaj.qss");
    file6.open(QFile::ReadOnly);
    stilo = QLatin1String(file6.readAll());

    for (i = 0; i < chiuj_disponeblaj.size(); i++) {
        chiuj_disponeblaj.at(i)->setStyleSheet(stilo);
        chiuj_disponeblaj.at(i)->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        chiuj_disponeblaj.at(i)->setVisible(false);
        connect(chiuj_disponeblaj.at(i), SIGNAL(clicked()), this, SLOT( vortoklako()));
    }

    QScroller::grabGesture(this->ui->scrollArea->viewport(), QScroller::LeftMouseButtonGesture);

    setUpdatesEnabled(true);

    qApp->processEvents();


}

frazokonstruo::~frazokonstruo()
{
    delete ui;
}

void frazokonstruo::on_BitBtn1_clicked()
{
    ujo = this->parentWidget();
    QString ujo_nomo = ujo->metaObject()->className() ;
    while ( ujo_nomo != "QTabWidget"){
        ujo = ujo->parentWidget();
        ujo_nomo = ujo->metaObject()->className() ;
    }

    int i;

    for (i = 0; i < chiuj_vortoj.size(); i++)
        chiuj_vortoj.at(i)->setFont(this->ui->Korekta->font());


    for (i = 0; i < chiuj_disponeblaj.size(); i++)
        chiuj_disponeblaj.at(i)->setFont(this->ui->Korekta->font());


    aEk02A.clear();
    aEk02D.clear();
    aEk02K.clear();
    aEk02R.clear();
    aEk02T.clear();
    Klarigoj.clear();

    QString Ekzercofrazokonstruo = this->objectName().right(4);

    iEk02D = _Matriz(&aEk02D, Ekzercofrazokonstruo, "D");

    _Matriz(&aEk02T, Ekzercofrazokonstruo,"R");
    while (aEk02T.size() < iEk02D)
        aEk02T.append("ERARO");

    QList<klakbutono_nova *> chiuj_butonoj;
    QList<neklakebla_nova *> chiuj_butonoj2;
    QList<korekta *> chiuj_butonoj3;
    QList<QLabel *> chiuj_label;

    for (i = 0; i < iEk02D; i++) {
        chiuj_butonoj =  ujo->findChildren<klakbutono_nova *>(this->objectName().left(6) + "Button"  + aEk02D[i]);
        if (chiuj_butonoj.size() > 0) {
            Klarigoj.append(chiuj_butonoj.at(0)->text());
            aEk02R.append( chiuj_butonoj.at(0)->text().trimmed().split(" ") );
        }
        else {
            chiuj_butonoj2 = ujo->findChildren<neklakebla_nova *>(this->objectName().left(6) + "Button"  + aEk02D[i]);
            if (chiuj_butonoj2.size() > 0) {
                Klarigoj.append(chiuj_butonoj2.at(0)->text());
                aEk02R.append( chiuj_butonoj2.at(0)->text().trimmed().split(" ") );
            }
            else {
                chiuj_butonoj3 = ujo->findChildren<korekta *>(this->objectName().left(6) + "Button"  + aEk02D[i]);
                if (chiuj_butonoj3.size() > 0) {
                    Klarigoj.append(chiuj_butonoj3.at(0)->text());
                    aEk02R.append( chiuj_butonoj3.at(0)->text().trimmed().split(" ") );
                }
                else {
                    Klarigoj.append("");
                    aEk02R.append(QStringList(""));
                }
            }
        }

        chiuj_label = ujo->findChildren<QLabel *>(this->objectName().left(6) + "Label"  + aEk02T[i]);
        if (chiuj_label.size() > 0) {
            QString traduko = chiuj_label.at(0)->text().trimmed();
            if ( traduko[0].isDigit() ){
                do {
                    traduko.remove(0,1);
                }
                while (traduko[0].isDigit() || traduko[0] == ".");
            }

            aEk02K.append( traduko.trimmed() );
        }
        else
            aEk02K.append( "ERARO" );

        aEk02A << false;
    }


    this->ui->BitBtn1->setEnabled(false);
    this->ui->BitBtn3->setEnabled(true);
    this->ui->Placar1->setValue(iEk02D);
    this->ui->Placar2->setValue(0);
    this->ui->Placar3->setValue(0);
    this->ui->Placar4->setValue(0);
    iKorektaj = 0;
    iEraraj = 0;


    this->ui->Vortoj->setVisible(true);
    this->ui->Disponeblaj->setVisible(true);

    this->ui->BitBtn2->setEnabled(true);
    this->ui->BitBtn2->setFocus();
    novafrazo();
}

void frazokonstruo::on_BitBtn3_clicked()
{
    this->ui->BitBtn1->setEnabled(true);
    this->ui->BitBtn2->setEnabled(false);
    this->ui->BitBtn3->setEnabled(false);
    this->ui->Vortoj->setVisible(false);
    this->ui->Disponeblaj->setVisible(false);
    this->ui->Antauen->setVisible(false);
    this->ui->Traduko1->setText("");
    this->ui->Korekta->setText("");

    this->ui->BitBtn1->setFocus();

}


void frazokonstruo::novafrazo()
{
    int i;

    setUpdatesEnabled(false);

    for (i = 0; i < chiuj_vortoj.size(); i++)
        chiuj_vortoj.at(i)->setVisible(false);


    for (i = 0; i < chiuj_disponeblaj.size(); i++) {
        chiuj_disponeblaj.at(i)->setText("");
        chiuj_disponeblaj.at(i)->setVisible(false);
    }


    iAleat2 = random(iEk02D);
    while (aEk02A[iAleat2])
        iAleat2 = random(iEk02D);

    this->ui->Korekta->setText("");
    this->ui->Traduko1->setText(aEk02K[iAleat2]);
    this->ui->Vortoj->setEnabled(true);
    this->ui->Disponeblaj->setEnabled(true);


    vortoj = aEk02R[iAleat2];

    QStringList disponeblaj;

    int iAleat, limo;
    limo =  ( round(vortoj.size() * 1.7) < chiuj_disponeblaj.size() ) ? round(vortoj.size() * 1.7) : chiuj_disponeblaj.size();

    for (i = 0; i < vortoj.size(); i++) {
        iAleat = random(limo);
        while (chiuj_disponeblaj.at(iAleat)->text() != "")
            iAleat = random(limo);
        chiuj_disponeblaj.at(iAleat)->setVisible(true);
        chiuj_disponeblaj.at(iAleat)->setText(vortoj.at(i));
        disponeblaj << vortoj.at(i);
    }

    int iAleat3, iAleat4;

    for (i = vortoj.size(); i < limo; i++) {
        iAleat3 = random(iEk02D);
        while ( iAleat3 == iAleat2)  iAleat3 = random(iEk02D);

        int j = 0;
        do {
            iAleat4 = random( aEk02R[iAleat3].size());
            if ( j > aEk02R[iAleat3].size() ) {
                iAleat3 = random(iEk02D);
                while ( iAleat3 == iAleat2)  iAleat3 = random(iEk02D);
                j = 0;
            }
            else j++;

        }
        while ( disponeblaj.indexOf( aEk02R[iAleat3][iAleat4].trimmed() ) >= 0 );

        iAleat = random(limo);
        while (chiuj_disponeblaj.at(iAleat)->text() != "")
            iAleat = random(limo);
        chiuj_disponeblaj.at(iAleat)->setVisible(true);
        chiuj_disponeblaj.at(iAleat)->setText(aEk02R[iAleat3][iAleat4]);
        disponeblaj << aEk02R[iAleat3][iAleat4];

    }


    this->ui->BitBtn2->setEnabled(true);
    this->ui->BitBtn2->setVisible(true);
    this->ui->BitBtn3->setEnabled(true);

    setUpdatesEnabled(true);

    qApp->processEvents();


}


void frazokonstruo::on_BitBtn2_clicked()
{

    int i, kiomdavortoj = 0;
    bool lPrava;
    lPrava = true;
    for (i = 0; i < chiuj_vortoj.size(); i++)
        if (chiuj_vortoj.at(i)->isVisible())
            kiomdavortoj++;

    if ( kiomdavortoj == aEk02R[iAleat2].size()) {
        int j = 0 ;
        i = 0;
        do {
            if (chiuj_vortoj.at(j)->isVisible()) {

                if ( chiuj_vortoj.at(j)->text() != aEk02R[iAleat2][i] ) {
                    lPrava = false;
                    break;
                }
                i++;
            }
            j++;

        }
        while ( i < kiomdavortoj);
    }
    else lPrava = false;

    if (lPrava)
    {
        Jes();

        iKorektaj++;

        this->ui->Placar1->setValue(iEk02D - iKorektaj);
        this->ui->Placar2->setValue(iKorektaj);
        aEk02A[iAleat2] = true;

        this->ui->BitBtn3->setEnabled(false);
        this->ui->BitBtn2->setEnabled(false);


        Atendu = false;

        Pauzu(1);
    }
    else
    {
        Ne();

        iEraraj++;
        this->ui->Placar3->setValue(iEraraj);

        Atendu = true;

        tekstoblinko();

    }

    this->ui->Placar4->setValue((iKorektaj * 100)/(iEraraj + iKorektaj));

    if (!Atendu) {
        if ( (iEk02D-iKorektaj) > 0)
            novafrazo();
        else
        {
            Mesagxo(iEraraj, iKorektaj); // prezentas gratulan mesagxon!
            on_BitBtn3_clicked();
        }
    }

}

void frazokonstruo::vortoklako()
{

    QPushButton* klakita = dynamic_cast<QPushButton*>(QObject::sender());
    for (int i = 0; i < chiuj_vortoj.size(); i++) {
        if ( ! chiuj_vortoj.at(i)->isVisible() ) {
            chiuj_vortoj.at(i)->setText(klakita->text());
            chiuj_vortoj.at(i)->setVisible(true);
            klakita->setVisible(false);
            break;
        }
    }


}

void frazokonstruo::vortoforigo()
{

    QPushButton* klakita = dynamic_cast<QPushButton*>(QObject::sender());

    for (int i = 0; i < chiuj_disponeblaj.size(); i++) {
        if ( ! chiuj_disponeblaj.at(i)->isVisible()  && chiuj_disponeblaj.at(i)->text() == klakita->text()) {
            chiuj_disponeblaj.at(i)->setVisible(true);
            klakita->setVisible(false);
            break;
        }
    }
}


void frazokonstruo::tekstoblinko()
{

    this->ui->Antauen->setVisible(true);
    this->ui->BitBtn2->setVisible(false);
    this->ui->Vortoj->setEnabled(false);
    this->ui->Disponeblaj->setEnabled(false);
    this->ui->Korekta->setText(Klarigoj[iAleat2]);

}



void frazokonstruo::on_Antauen_clicked()
{
    this->ui->Korekta->setText("");
    this->ui->Antauen->setVisible(false);
    this->ui->BitBtn2->setVisible(true);

    Atendu = false;
    novafrazo();
}
