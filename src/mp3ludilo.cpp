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

#include "mp3ludilo.h"
#include "ui_mp3ludilo.h"
#include "funkcioj.h"

mp3ludilo::mp3ludilo(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::mp3ludilo)
{
    ui->setupUi(this);

    ludilo = new QMediaPlayer(this);

    connect(ludilo, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(finite()));
    this->ui->Pauzu->setEnabled(true);
    this->ui->Pauzu->setVisible(false);
    MiaPagho = -1;
}

mp3ludilo::~mp3ludilo()
{
    delete ui;
}


void mp3ludilo::on_Ludu_clicked()
{

    QWidget * ujo = this->parentWidget();
    QString ujo_nomo = ujo->metaObject()->className() ;
    // QString mrLoko = "http://kurso.com.br/datumoj/";
    while ( ujo_nomo != "QTabWidget"){
        ujo = ujo->parentWidget();
        ujo_nomo = ujo->metaObject()->className() ;
    }

    QTabWidget * MiaPagharo = qobject_cast<QTabWidget *>(ujo);

    if (MiaPagharo != nullptr)
        MiaPagho = MiaPagharo->currentIndex();

    if (ludilo->state() == QMediaPlayer::PlayingState)
    {
        ludilo->pause();
        this->setUpdatesEnabled(false);
        this->ui->Pauzu->setVisible(false);
        this->ui->Ludu->setVisible(true);
        this->setUpdatesEnabled(true);
    }
    else
    {
        if (ludilo->state() == QMediaPlayer::PausedState)
        {
            ludilo->play();
            this->setUpdatesEnabled(false);
            this->ui->Pauzu->setVisible(true);
            this->ui->Ludu->setVisible(false);
            this->setUpdatesEnabled(true);
        }
        else
        {
            QString dosiero = mrLoko + "sonoj/" + this->objectName().left(5).toLower() + "/" + this->objectName().mid(6) + ".mp3";//mp3_finajho;
            if (sSistemo == "android")
                ludilo->setMedia(QUrl(dosiero));
            else
                ludilo->setMedia(QUrl::fromLocalFile(dosiero));
                //ludilo->setMedia(QUrl(dosiero));
            ludilo->play();
            this->setUpdatesEnabled(false);
            this->ui->Chesu->setEnabled(true);
            this->ui->Pauzu->setVisible(true);
            this->ui->Ludu->setVisible(false);
            this->setUpdatesEnabled(true);
        }
    }
}


void mp3ludilo::on_Chesu_clicked()
{
        ludilo->stop();
        this->setUpdatesEnabled(false);
        this->ui->Chesu->setEnabled(false);
        this->ui->Pauzu->setVisible(false);
        this->ui->Ludu->setVisible(true);
        this->setUpdatesEnabled(true);

}

void mp3ludilo::finite()
{
    if (ludilo->mediaStatus() == QMediaPlayer::EndOfMedia)
        on_Chesu_clicked();
}

void mp3ludilo::on_Pauzu_clicked()
{
    if (ludilo->state() == QMediaPlayer::PlayingState)
    {
        ludilo->pause();
        this->setUpdatesEnabled(false);
        this->ui->Pauzu->setVisible(false);
        this->ui->Ludu->setVisible(true);
        this->setUpdatesEnabled(true);
    }

}



void mp3ludilo::PaghoShanghita(int NovaPagho)
{
    if (MiaPagho >= 0)
        if (NovaPagho != MiaPagho)
            if (ludilo->state() == QMediaPlayer::PlayingState)
                on_Chesu_clicked();
}

void mp3ludilo::PaghoFragoj(int NovaPagho)
{
    if (MiaPagho >= 0)
        if ( (NovaPagho != MiaPagho + 1) && (NovaPagho != MiaPagho) )
            if (ludilo->state() == QMediaPlayer::PlayingState)
                on_Chesu_clicked();
}
