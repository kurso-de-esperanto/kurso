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

#include "prononco.h"
#include "ui_prononco.h"
#include "funkcioj.h"
#include "klakbutono_nova.h"
#include <QtGui>
#include <QtCore>
#include <QScroller>


prononco::prononco(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::prononco)
{
    ui->setupUi(this);
    this->ui->PP_Prog->setVisible(false);

    this->ui->PP_Kiomope->setVisible(false);



    QScroller::grabGesture(this->ui->scrollArea->viewport(), QScroller::LeftMouseButtonGesture);

    Provizorujo = savasLoko;

    registrilo = new QAudioRecorder(this);

    QAudioEncoderSettings sonkonfiguroj;
    if (sSistemo == "android")
        sonkonfiguroj.setCodec("audio/mpeg");
    else {
        sonkonfiguroj.setCodec("audio/amr");
        sonkonfiguroj.setEncodingMode(QMultimedia::ConstantQualityEncoding);
    }
    sonkonfiguroj.setQuality(QMultimedia::NormalQuality);

    registrilo->setEncodingSettings(sonkonfiguroj);

    connect( registrilo, SIGNAL(durationChanged(qint64)), SLOT(Progreso(qint64)));

    ludilo = new QMediaPlayer(this);

}

prononco::~prononco()
{
    delete ui;
}

void prononco::on_PP_Startu_clicked()
{

    this->ui->PP_Startu->setEnabled(false);
    this->ui->PP_Haltu->setEnabled(true);
    QString EkzercoPrononco = this->objectName().right(4);
    iEk09D = _Matriz(&aEk09D,EkzercoPrononco,"D");
    this->ui->Placar->setValue(limigo(iEk09D));
    //aEk09A.clear(iEk09D);
    aEk09A.clear();
    for (int i=0; i < iEk09D; i++)
        aEk09A << false;

    this->ui->PP_Haltu->setFocus();

    novafrazo();

}

void prononco::novafrazo()
{
    int i = 0;
    QString sTeksto = "";
    QString EkzercoPrononco = this->objectName().right(4);
    QString Leciono = "Lec" + EkzercoPrononco.left(2);
    if (this->ui->PP_Haltu->isEnabled())
    {
        this->ui->butonujo->setEnabled(false);
        this->ui->PP_Kiomope->setEnabled(false);
        this->ui->Tempujo->setEnabled(false);

        if (this->ui->radio1->isChecked())
            Kiome = 1;
        else
        if (this->ui->radio2->isChecked())
            Kiome = 2;
        else
        if (this->ui->radio4->isChecked())
            Kiome = 4;

        if (this->ui->Placar->value() < Kiome)
            Kiome = this->ui->Placar->value(); // Por certigi, ke en la lasta fojo ne manku vortoj

        for (i=0; i < Kiome; i++)
        {
            iAleat9 = random(iEk09D);
            while (aEk09A[iAleat9])
                iAleat9 = random(iEk09D);
            aEk09A[iAleat9] = true;
            if (aEk09D[iAleat9].toInt() > 0)
            {
                QWidget * ujo = this->parentWidget();
                QString ujo_nomo = ujo->metaObject()->className() ;
                while ( ujo_nomo != "QTabWidget"){
                    ujo = ujo->parentWidget();
                    ujo_nomo = ujo->metaObject()->className() ;
                }

                QList<klakbutono_nova *> chiuj_butonoj =
                    ujo->findChildren<klakbutono_nova *>(Leciono + "_Button"  + aEk09D[iAleat9]);

                if (chiuj_butonoj.size() > 0)
                    aEk09T[i][0] = chiuj_butonoj.at(0)->text();
                else
                    aEk09T[i][0] = "";

                aEk09T[i][1] = "sonoj/lec" + EkzercoPrononco.left(2) + "/btn" + aEk09D[iAleat9] + mp3_finajho;
            }
            else
            {
                aEk09T[i][0] = aEk09D[iAleat9];
                sTeksto = CxSist(aEk09D[iAleat9],1);
                aEk09T[i][1] = "sonoj/lec" + EkzercoPrononco.left(2) + "/" + sTeksto + mp3_finajho;
            }
        }

        RegistrasVocxon();

        this->ui->butonujo->setEnabled(true);
        this->ui->PP_Kiomope->setEnabled(true);
        this->ui->Tempujo->setEnabled(true);

        this->ui->Placar->setValue(this->ui->Placar->value() - Kiome);
        if (this->ui->Placar->value() <= 0)
            on_PP_Haltu_clicked();
    }

}

void prononco::RegistrasVocxon()
{
    int i = 0;
    if (this->ui->PP_Haltu->isEnabled())
    {
        for (i=0; i < Kiome; i++)
        {
            if (!this->ui->PP_Haltu->isEnabled())
                break;
            this->ui->PP_Vorto->setText(aEk09T[i][0]);
            //this->ui->pagharo->setCurrentIndex(1); // auskultilo
            this->ui->bildo->setPixmap(QPixmap(":ikonoj/auskultilo.png"));

            if (sSistemo == "android")
                ludilo->setMedia(QUrl(mrLoko + aEk09T[i][1]));
            else
                ludilo->setMedia(QUrl::fromLocalFile(mrLoko + aEk09T[i][1]));
            ludilo->play();
            aEk09F[i] = int(ludilo->duration()/1000) + 2;
            Pauzu( aEk09F[i]);
            //this->ui->pagharo->setCurrentIndex(0); // mikrofono
            this->ui->bildo->setPixmap(QPixmap(":ikonoj/mikrofono.png"));

            this->ui->PP_Prog->setVisible(true);
            KiomFoje = i;
            Registru(i);
            Pauzu(this->ui->spinBox->value());

            //this->ui->pagharo->setCurrentIndex(2); // blanka pagho
            this->ui->bildo->setPixmap(QPixmap(""));

            this->ui->PP_Prog->setVisible(false);
            this->ui->PP_Prog->setValue(0);

        }

        on_PP_Aud_re_clicked();

    }

}

void prononco::on_PP_Haltu_clicked()
{
    this->ui->PP_Kiomope->setEnabled(true);
    //this->ui->pagharo->setCurrentIndex(2); // blanka pagho
    this->ui->bildo->setPixmap(QPixmap(""));

    this->ui->PP_Vorto->setText(""); //
    this->ui->butonujo->setEnabled(false);
    this->ui->PP_Startu->setEnabled(true);
    this->ui->PP_Haltu->setEnabled(false);
    this->ui->Tempujo->setEnabled(true);
    this->ui->PP_Prog->setVisible(false);
    this->ui->Placar->setValue(0);
    this->ui->PP_Startu->setFocus();
}

void prononco::on_PP_Antauen_clicked()
{
    if (this->ui->Placar->value() <= 0)
        on_PP_Haltu_clicked();
    else
        novafrazo();
}

void prononco::on_PP_Mik_re_clicked()
{
    RegistrasVocxon();
}

void prononco::on_PP_Aud_re_clicked()
{
    if ( this->ui->PP_Haltu->isEnabled())
    {
        this->ui->butonujo->setEnabled(false);
        // this->ui->pagharo->setCurrentIndex(1); // auskultilo
        this->ui->bildo->setPixmap(QPixmap(":ikonoj/auskultilo.png"));

        this->ui->PP_Kiomope->setEnabled(false);
        for (int i=0; i < Kiome; i++) // ludas registritan vochon
        {
            if (!this->ui->PP_Haltu->isEnabled())
                break;
            this->ui->PP_Vorto->setText(aEk09T[i][0]);
            qDebug() << aEk09T[i][0];
            mp3(aEk09T[i][1]);
            Pauzu( aEk09F[i] );
            LudasRegistrita(i);
            Pauzu(this->ui->spinBox->value());
        }
        //this->ui->pagharo->setCurrentIndex(2); // blanka pagho
        this->ui->bildo->setPixmap(QPixmap(""));

        this->ui->butonujo->setEnabled(true);
        this->ui->PP_Kiomope->setEnabled(true);
        this->ui->PP_Vorto->setText("");
        this->ui->PP_Antauen->setFocus();
    }
}

void prononco::Registru(int KiuFojo)
{

    QTimer::singleShot( this->ui->spinBox->value() * 1000, this, SLOT(ChesasRegistri()));
    QString dosiero = Provizorujo + "prononco" + QString::number(KiuFojo);
    registrilo->setOutputLocation(QUrl::fromLocalFile(dosiero));
    registrilo->record();

}

void prononco::ChesasRegistri()
{

    registrilo->stop();

}

void prononco::LudasRegistrita(int KiuFojo)
{
    QString dosiero = Provizorujo + "prononco" + QString::number(KiuFojo) + ((sSistemo == "windows" || sSistemo == "osx") ? ".wav" : ".mp4");
    ludilo->setMedia(QUrl::fromLocalFile(dosiero));
    ludilo->play();

}

void prononco::LudoFinita(QAudio::State statuso)
{

    Q_UNUSED(statuso)
}

void prononco::Progreso(qint64 tempo_ludita)
{
    int tempo = int((tempo_ludita / this->ui->spinBox->value()) / 10);
    this->ui->PP_Prog->setValue( tempo );
}
