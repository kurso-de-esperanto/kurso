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

#include "videoludilo.h"
#include "ui_videoludilo.h"
#include "funkcioj.h"
#include <QtMultimediaWidgets/QVideoWidget>

videoludilo::videoludilo(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::videoludilo)
{
    ui->setupUi(this);

    if (sSistemo != "android") {

        videoLudilo = new QMediaPlayer(this);
        QWidget *enhavujo = new QWidget;
        QVideoWidget *videoWidget = new QVideoWidget(enhavujo);
        videoLudilo->setVideoOutput(videoWidget);

        QVBoxLayout *layoutV = new QVBoxLayout;
        layoutV->addWidget(videoWidget,0,Qt::AlignCenter);
        enhavujo->setLayout(layoutV);

        enhavujo->setMinimumSize(352,272);
        enhavujo->setMaximumSize(352,272);
        videoWidget->setMinimumSize(320,240);
        enhavujo->setStyleSheet("border: 16px solid Black;");

        layout.addWidget(enhavujo);
        layoutH.addWidget(ui->Ludu);
        layoutH.addWidget(ui->Pauzu);
        layoutH.addWidget(ui->Chesu);
        layoutH.addStretch(0);
        layoutH.setSpacing(0);

        layout.setSpacing(2);

        layout.addLayout(&layoutH);

        setLayout(&layout);

        connect(ui->Ludu,SIGNAL(clicked()),this,SLOT(onPlay()));
        connect(ui->Chesu, SIGNAL(clicked()), this, SLOT(onStop()));
        connect(videoLudilo, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(finite()));
        this->ui->Pauzu->setEnabled(true);
        this->ui->Pauzu->setVisible(false);
        MiaPagho = -1;
    }

}

videoludilo::~videoludilo()
{
    delete ui;
}

void videoludilo::onPlay()
{
    QWidget * ujo = this->parentWidget();
    QString ujo_nomo = ujo->metaObject()->className() ;
    //QString mrLoko = "http://kurso.com.br/datumoj/";
    while ( ujo_nomo != "QTabWidget"){
        ujo = ujo->parentWidget();
        ujo_nomo = ujo->metaObject()->className() ;
    }

    QTabWidget * MiaPagharo = qobject_cast<QTabWidget *>(ujo);

    if (MiaPagharo != nullptr)
        MiaPagho = MiaPagharo->currentIndex();

    if (videoLudilo->state() == QMediaPlayer::PlayingState)
    {
        videoLudilo->pause();
        this->setUpdatesEnabled(false);
        this->ui->Pauzu->setVisible(false);
        this->ui->Ludu->setVisible(true);
        this->setUpdatesEnabled(true);
    }
    else
    {
        if (videoLudilo->state() == QMediaPlayer::PausedState)
        {
            videoLudilo->play();
            this->setUpdatesEnabled(false);
            this->ui->Pauzu->setVisible(true);
            this->ui->Ludu->setVisible(false);
            this->setUpdatesEnabled(true);
        }
        else
        {
            //QString dosiero = mrLoko + "video/" + this->objectName().left(5).toLower() + "/" + this->objectName().mid(6) + video_finajho;
            QString dosiero = mrLoko + "video/lec02/jen_video" + video_finajho;
            // videoLudilo->setMedia(QUrl(dosiero));
            videoLudilo->setMedia(QUrl::fromLocalFile(dosiero));
            qDebug() << dosiero;

            videoLudilo->play();
            ui->Chesu->setEnabled(true);
            this->setUpdatesEnabled(false);
            this->ui->Pauzu->setVisible(true);
            this->ui->Ludu->setVisible(false);
            this->setUpdatesEnabled(true);
        }
    }
}

void videoludilo::onStop()
{
    videoLudilo->stop();
    this->setUpdatesEnabled(false);
    this->ui->Pauzu->setVisible(false);
    this->ui->Ludu->setVisible(true);
    ui->Chesu->setEnabled(false);
    this->setUpdatesEnabled(true);
}

void videoludilo::finite()
{
    if (videoLudilo->mediaStatus() == QMediaPlayer::EndOfMedia)
        onStop();
}


void videoludilo::on_Pauzu_clicked()
{
    if (videoLudilo->state() == QMediaPlayer::PlayingState)
    {
        videoLudilo->pause();
        this->setUpdatesEnabled(false);
        this->ui->Pauzu->setVisible(false);
        this->ui->Ludu->setVisible(true);
        this->setUpdatesEnabled(true);
    }

}

void videoludilo::PaghoShanghita(int NovaPagho)
{
    if (MiaPagho >= 0)
        if (NovaPagho != MiaPagho)
            if (videoLudilo->state() == QMediaPlayer::PlayingState)
                onStop();
}
