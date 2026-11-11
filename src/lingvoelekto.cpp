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

#include "lingvoelekto.h"
#include "ui_lingvoelekto.h"
#include <QtGui>
#include <QtCore>
#include <funkcioj.h>
#include <filedownloader.h>
#include <QDesktopWidget>
#include <QTemporaryFile>
#include <QSettings>

lingvoelekto::lingvoelekto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lingvoelekto)
{
    ui->setupUi(this);

    this->setWindowTitle("Elektu vian lingvon / Choose your language");

}

lingvoelekto::~lingvoelekto()
{
    delete ui;
}

void lingvoelekto::elshutas()
{
   // QUrl LingvojUrl("http://kurso.com.br/datumoj/traduklisto.ini");
   // FileDownloader(LingvojUrl, "traduklisto.ini", this);
   // elektasTradukFonton();

    //connect(m_pImgCtrl, SIGNAL (downloaded()), this, SLOT (elektasTradukFonton()));
}

void lingvoelekto::elektasTradukFonton()
{
    QFile dosiero(savasLoko + "traduklisto.ini");
    if (dosiero.exists())
    {
        QSettings Tradukoj(dosiero.fileName(), QSettings::IniFormat);
        Tradukoj.setIniCodec("UTF-8");
        Tradukoj.beginGroup("0");
        QString unuaTraduko = Tradukoj.value("LingvoID", "??").toString() ;
        Tradukoj.endGroup();
        if ( unuaTraduko == "??" )
            komencasElDosierujo();
        else {
            qDebug() << "El la retejo";
            int Itemo = -1;
            int ItemoAngla = -1;
            QLocale LokaLingvo;
            QString LingvoID = LokaLingvo.name().left(2);

            for (int i = 0; i < 200; ++i)
            {
                Tradukoj.beginGroup(QString::number(i));
                QStringList lingvo;
                lingvo << Tradukoj.value("LingvoID", "??").toString();
                lingvo << Tradukoj.value("Lingvo", "?????????").toString();
                lingvo << Tradukoj.value("DosierNomo", "?????????").toString();
                lingvo << Tradukoj.value("Dato", "?????????").toString();
                Tradukoj.endGroup();
                if (lingvo.at(0) == "??")
                    break;
                LingvoListo.append(lingvo);
                ui->Lingvo->addItem( lingvo.at(1));
                if (lingvo.at(0) == LingvoID)
                    Itemo = i;

                if (lingvo.at(0) == "en")
                    ItemoAngla = i;
            }

            if (Itemo < 0)
                Itemo = ItemoAngla;


            if (Itemo >= 0)
            {
                QString LingvoNomo = LingvoListo[Itemo][1];
                QList<QListWidgetItem *> chiuj_itemoj = ui->Lingvo->findItems(LingvoNomo, Qt::MatchStartsWith);
                if (chiuj_itemoj.count() > 0 )
                    ui->Lingvo->setCurrentItem(chiuj_itemoj[0]);
            }
        }

    }
    else komencasElDosierujo();
}




void lingvoelekto::komencasElDosierujo()
{
    qDebug() << "El la dosierujo";
    QLocale LokaLingvo;
    QString LingvoID = LokaLingvo.name().left(2);

    //
    QDir dosierujo(":/tradukoj/");
    dosierujo.setFilter(QDir::Files);

    QStringList filtroj;
    filtroj << "*.trd";

    dosierujo.setNameFilters(filtroj);

    QFileInfoList Dosieroj;

    Dosieroj = dosierujo.entryInfoList();
    QString DosierNomo;

    int Itemo = -1;
    int ItemoAngla = -1;

    for (int i = 0; i < Dosieroj.size(); ++i)
    {
        QFileInfo fileInfo = Dosieroj.at(i);
        DosierNomo = fileInfo.fileName();

        QSettings Tradukado(":/tradukoj/" + DosierNomo, QSettings::IniFormat);
        Tradukado.setIniCodec("UTF-8");

        Tradukado.beginGroup("Traduko");
        QStringList lingvo;
        lingvo << Tradukado.value("LingvoID", "??").toString();
        lingvo << Tradukado.value("Lingvo", "?????????").toString();
        lingvo << DosierNomo;
        lingvo << Tradukado.value("Dato", "10.05.2020").toString();
        LingvoListo.append(lingvo);
        ui->Lingvo->addItem( lingvo.at(1));
        Tradukado.endGroup();
        if (lingvo.at(0) == LingvoID)
            Itemo = i;

        if (lingvo.at(0) == "en")
            ItemoAngla = i;
    }


    if (Itemo < 0)
        Itemo = ItemoAngla;


    if (Itemo >= 0)
    {
        QString LingvoNomo = LingvoListo[Itemo][1];
        QList<QListWidgetItem *> chiuj_itemoj = ui->Lingvo->findItems(LingvoNomo, Qt::MatchStartsWith);
        if (chiuj_itemoj.count() > 0 )
            ui->Lingvo->setCurrentItem(chiuj_itemoj[0]);
    }
}

void lingvoelekto::on_pushButton_clicked()
{
    if (ui->Lingvo->currentItem()->isSelected())
    {
        sLingvo = LingvoListo[ui->Lingvo->currentRow()][1];
        sTradukoDosiero = LingvoListo[ui->Lingvo->currentRow()][2];
        sTradukoDato = LingvoListo[ui->Lingvo->currentRow()][3];
    }
    else
    {
        sLingvo = "English - angla";
        sTradukoDosiero = "angla.trd";
        sTradukoDato = "10.05.2020";
    }


    QUrl LingvojUrl("http://kurso.com.br/datumoj/tradukoj/" + sTradukoDosiero );
    elshutilo = new FileDownloader(LingvojUrl, sTradukoDosiero , this);

    connect(elshutilo, SIGNAL (downloaded()), this, SLOT (fermasFenestron()));

    QApplication::processEvents();

}

void lingvoelekto::closeEvent(QCloseEvent *event)
{
    if (sLingvo == "" || sTradukoDosiero == "")
        on_pushButton_clicked();
    event->accept();
}

void lingvoelekto::showEvent(QShowEvent *event)
{
    QList<QScreen *> ekrano = QGuiApplication::screens();

    /*
    if (sSistemo == "android" || sSistemo == "ios") {

        this->setMaximumSize(ekrano.at(0)->size());
        this->setMinimumWidth((ekrano.at(0)->size().width() * 0.9 ));
    }
    */

    this->setMinimumHeight((ekrano.at(0)->size().height() * 0.9 ));
    this->adjustSize();

    QRect frect = frameGeometry();
    frect.moveCenter(ekrano.at(0)->availableGeometry().center());
    move(frect.topLeft());

    QUrl LingvojUrl("http://kurso.com.br/datumoj/traduklisto.ini");
    elshutilo = new FileDownloader(LingvojUrl, "traduklisto.ini", this);
    connect(elshutilo, SIGNAL (downloaded()), this, SLOT (elektasTradukFonton()));

    qApp->processEvents();

    Q_UNUSED(event)


}

void lingvoelekto::fermasFenestron()
{
    this->close();
}
