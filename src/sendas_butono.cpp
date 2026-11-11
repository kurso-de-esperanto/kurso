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

#include "sendas_butono.h"
#include "korekta.h"
#include <QTabWidget>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QClipboard>
#include <QApplication>
#include <funkcioj.h>
#include <klakbutono_nova.h>
#include <neklakebla_nova.h>

sendas_butono::sendas_butono(QWidget *parent) :
    QPushButton(parent)
{
    QObject::connect(this, SIGNAL(clicked()),
            this, SLOT(klakita()));

    this->setFlat(true);
    this->setIcon(QIcon(":/ikonoj_androjdo/kopias_por_sendi.png"));
    this->setIconSize(QSize(40,48));
    this->setText("");

}

void sendas_butono::klakita()
{
    QWidget * ujo = this->parentWidget();
    QString ujo_nomo = ujo->metaObject()->className() ;
    while ( ujo_nomo != "QTabWidget"){
        ujo = ujo->parentWidget();
        ujo_nomo = ujo->metaObject()->className() ;
    }

    QString Sendota = "";
    int i;
    QString NomoPatro = ujo->parent()->objectName().mid(3,2);
    QString Leciono = "Leciono " + NomoPatro;
    QList<QLabel *> chiuj_label;

    if ( NomoPatro != "13")
    {
        chiuj_label = dynamic_cast<QTabWidget*>(ujo)->currentWidget()->findChildren<QLabel *>();
        Sendota.append(Leciono + QString::fromUtf8(" - Paĝo "));
        Sendota.append( QString::number(dynamic_cast<QTabWidget*>(ujo)->currentIndex() + 1) +  "\n\n" );
    }
    else
    {
        //QTabWidget * ekzamen_pagho = qobject_cast<QTabWidget*>(Pagxo->parent()->parent());
        for ( i = 0; i < 5; i++ )
            chiuj_label = chiuj_label + dynamic_cast<QTabWidget*>(ujo)->widget(i)->findChildren<QLabel *>();
    }
    QString TextoEdit, TextoLabel;
    QLineEdit * amiketo;
    QPlainTextEdit * amiketo2;
    for ( i = 0; i < chiuj_label.count(); i++) {
        if ( dynamic_cast<korekta*>(chiuj_label.at(i)) ||
             dynamic_cast<neklakebla_nova*>(chiuj_label.at(i)) ||
             dynamic_cast<klakbutono_nova*>(chiuj_label.at(i)) )
            continue;

        if (chiuj_label[i]->buddy() != nullptr)
        {
            TextoLabel = chiuj_label[i]->text().trimmed();
            amiketo = qobject_cast<QLineEdit*>(chiuj_label[i]->buddy());
            if (amiketo !=nullptr)
                TextoEdit = amiketo->text();
            else
            {
                amiketo2 = qobject_cast<QPlainTextEdit*>(chiuj_label[i]->buddy());
                if (amiketo2 !=nullptr)
                    TextoEdit = "\n\n" + amiketo2->toPlainText();
                else
                {
                    TextoEdit = "";
                    TextoLabel = "";
                }
            }

            if (TextoLabel != "")
                Sendota.append(TextoLabel + "\n");
            if (TextoEdit != "")
                Sendota.append(TextoEdit + "\n\n");
        }
        else
            Sendota.append("\n\n" + chiuj_label[i]->text() + "\n\n");
    }
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(CxSist(Sendota, iSistemo) );
    QMessageBox msgBox(QApplication::activeWindow());
    msgBox.setText(smTondujo);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}
