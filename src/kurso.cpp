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


#include "kurso.h"
#include "ui_kurso.h"
#include <QtGui>
#include <QtCore>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>
#include <funkcioj.h>
#include <lingvoelekto.h>
#include <klakbutono.h>
#include <lec01.h>
#include <lec02.h>
#include <lec03.h>
#include <lec04.h>
#include <lec05.h>
#include <lec06.h>
#include <lec07.h>
#include <lec08.h>
#include <lec09.h>
#include <lec10.h>
#include <lec11.h>
#include <lec12.h>
#include <lec13.h>
#include <QScroller>
#include <QSysInfo>
#include <QScrollArea>

kurso::kurso(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::kurso)
{
    randomize();

    ui->setupUi(this);

    QScroller::grabGesture(this->ui->scrollArea->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_3->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_2->viewport(), QScroller::LeftMouseButtonGesture);
    QScroller::grabGesture(this->ui->scrollArea_5->viewport(), QScroller::LeftMouseButtonGesture);

    QIcon kurso_ikono(":kurso5.ico");
    QApplication::setWindowIcon(kurso_ikono);

    ui->prog_printilo->setVisible(false);
    ui->printilo->setVisible(false); // La funkcio "printi lecionon" ne plu estas signifa post la versio por porteblaj aparatoj
    ui->Sendas->setVisible(false); // La sendilo farighis kopiilo kaj restas nun che la fino de chiu sendota ekzerco
    ui->Konfig_Label4->setVisible(false); // ne plu bezonata, char Unikodo estas vaste uzata nuntempe
    ui->konfig_send_literoj->setVisible(false); // ne plu bezonata, char Unikodo estas vaste uzata nuntempe

    if (sSistemo == "android" || sSistemo == "ios") ui->tradukilo->setVisible(false); // Tradukilo ne bone montrighis en Androjdo

    ui->shanghasKonfigurojn->setVisible(false);

    ui->butonujo->setVisible(false);
    ui->navigujo->setVisible(false);
    ui->paghopiedo->setVisible(false);

    Malalta_Fenestro = false;
    Eta_Fenestro = false;
    JamMontrita = false;

    ludilo = new QMediaPlayer(this);

    TradukitajLecionoj << "" << "" << "" << "" << "" << "" << "" << "" << "" << "" << "" << "" << "";



    komencakonfiguro();
    // Traduku();
    //ListigasLingvojn();
    //Konfiguru();
    //Stilo();


    ui->Paghujo->setCurrentIndex(0); // iras al la komenca pagho

    tradukilo = nullptr;

    antaua = nullptr;

}

kurso::~kurso()
{
    delete ui;
}

void kurso::on_Hejmo_clicked()
{

    ui->shanghasKonfigurojn->setVisible(false);
    ui->navigujo->setVisible(false);
    ui->butonujo->setVisible(false);
    ui->paghopiedo->setVisible(false);
    ui->Paghujo->setCurrentIndex(0);

}

void kurso::komencakonfiguro()
{
    QString Dirnomo = savasLoko;

    QSettings Konfiguro(Dirnomo + "kursokape.ini", QSettings::IniFormat);
    Konfiguro.setIniCodec("UTF-8");
    Konfiguro.beginGroup("Gxenerala");
    sLingvo = Konfiguro.value("Lingvo", "").toString();
    sTradukoDosiero = Konfiguro.value("Dosiero", "").toString();

    iLiterGrando = Konfiguro.value("LiterGrando", 11).toInt();

    sTiparo     = Konfiguro.value("Tiparo",   (sSistemo == "osx" ? "Helvetica Neue" : "DejaVu Sans")).toString();
    sTiparoEo   = Konfiguro.value("TiparoEo", (sSistemo == "osx" ? "Helvetica Neue" : "DejaVu Sans")).toString();
    lCxapeligo  = Konfiguro.value("Cxapeligo", true).toBool();
    iSistemo    = Konfiguro.value("Sistemo", 0).toInt();
    LastaLeciono = Konfiguro.value("LastaLeciono", 1).toInt();
    LastaPagxo  = Konfiguro.value("LastaPagxo", 0).toInt();
    lSxaltilo   = Konfiguro.value("Sxaltilo", true).toBool();
    lNoteto     = Konfiguro.value("Noteto", true).toBool();
    iLiterGrandoEo= Konfiguro.value("LiterGrandoEo", 11).toInt();
    iFenestraStilo= Konfiguro.value("FenestraStilo", 0).toInt();

    if (sLingvo == "" || sTradukoDosiero == "") {
        lingvoelekto nova;
        nova.exec();
        iLiterGrando = 11; // mezgranda litero, la uzulo povas ghin shanghi poste.
        Traduku();
    }
    else {
        QFile dosiero(savasLoko + "traduklisto.ini");
        if (dosiero.exists() ) {
            QFileInfo informo = QFileInfo(dosiero);
            QDateTime datoDosiero = informo.birthTime();
            if ( datoDosiero.date().addDays(7) < QDate::currentDate() ) {
                QUrl LingvojUrl("http://kurso.com.br/datumoj/traduklisto.ini");
                elshutilo = new FileDownloader(LingvojUrl, "traduklisto.ini", this);
                connect(elshutilo, SIGNAL ( downloaded() ), this, SLOT ( aktualigasTradukon() ) );
            }
            else Traduku();
        }
        else {
            QUrl LingvojUrl("http://kurso.com.br/datumoj/traduklisto.ini");
            elshutilo = new FileDownloader(LingvojUrl, "traduklisto.ini", this);
            connect(elshutilo, SIGNAL ( downloaded() ), this, SLOT ( aktualigasTradukon() ) );
        }
    }
}

void kurso::aktualigasTradukon() {

    QSettings Tradukado(savasLoko + sTradukoDosiero, QSettings::IniFormat);
    Tradukado.setIniCodec("UTF-8");

    Tradukado.beginGroup("Traduko");
    sLingvoID = Tradukado.value("LingvoID", "en").toString();
    QDate TradukDato;
    TradukDato = QDate::fromString(Tradukado.value("Dato", "01.01.2000").toString(), "dd.MM.yyyy");
    qDebug() << "Data lida do arquivo: " << Tradukado.value("Dato", "01.01.2000").toString();
    Tradukado.endGroup();

    QDate NovaTraduko;

    QFile dosiero(savasLoko + "traduklisto.ini");
    if (dosiero.exists())
    {
        QSettings Tradukoj(dosiero.fileName(), QSettings::IniFormat);
        Tradukoj.setIniCodec("UTF-8");
        for (int i = 0; i < 200; i++) {
            Tradukoj.beginGroup(QString::number(i));
            if (Tradukoj.value("LingvoID", "??").toString().trimmed() == sLingvoID.trimmed() ) {
                NovaTraduko = QDate::fromString(Tradukoj.value("Dato", "01.01.2000").toString(), "dd.MM.yyyy") ;
                qDebug() << "Nova Traduko " <<  NovaTraduko.toString("dd.MM.yyyy");
                break;
            }
            Tradukoj.endGroup();
        }



        qDebug() << "Traduko malnova " << TradukDato.toString("dd.MM.yyyy");

        if (TradukDato < NovaTraduko) {
            QUrl LingvojUrl("http://kurso.com.br/datumoj/tradukoj/" + sTradukoDosiero );
            elshutilo = new FileDownloader(LingvojUrl, sTradukoDosiero , this);

            connect(elshutilo, SIGNAL ( downloaded() ), this, SLOT ( Traduku() ) );
        }
        else Traduku();

    }
    else Traduku();


}

void kurso::Traduku()
{

    QString tradukDosiero;

    QFile novaTraduko(savasLoko + sTradukoDosiero);
    if ( novaTraduko.exists())
        tradukDosiero = savasLoko + sTradukoDosiero;
    else {
        tradukDosiero = ":/tradukoj/" + sTradukoDosiero;
        QFile fTraduko(tradukDosiero);
        if (! fTraduko.exists()) {
            QMessageBox msgBox(QApplication::activeWindow());
            tradukDosiero = ":/tradukoj/angla.trd";
            QFile fTraduko1(tradukDosiero);
            if (fTraduko1.exists()) {
                msgBox.setText("The translation file " + sTradukoDosiero  + " could not be found. English translation will be used as default.");
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.exec();
                sTradukoDosiero = "angla.trd";
                sLingvo = "English — Angla";
            }
            else {
                msgBox.setText("The translation file " + sTradukoDosiero + " could not be found. The English translation file (angla.trd) could not be found either. \nPlease check the path or reinstall Kurso. \nProgram will quit now.");
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.exec();
                NeEkzistasTraduko = true;
                qApp->exit(1);
            }
        }
    }

    qDebug() << tradukDosiero;

    QSettings Tradukado(tradukDosiero, QSettings::IniFormat);
    Tradukado.setIniCodec("UTF-8");

    Tradukado.beginGroup("Traduko");
    sTradukinto = Tradukado.value("Tradukinto", "").toString();
    sLingvoID = Tradukado.value("LingvoID", "en").toString();
    Tradukado.endGroup();

    Tradukado.beginGroup("Mesagxoj");
    smRekomencu = Tradukado.value("smRekomencu", "Ne Tradukita").toString();
    smGratulon  = Tradukado.value("smGratulon",  "Ne Tradukita").toString();
    smDenove =    Tradukado.value("smDenove",    "Ne Tradukita").toString();
    smModifis =   Tradukado.value("smModifis",   "Ne Tradukita").toString();
    smTondujo =   Tradukado.value("smTondujo",   "Ne Tradukita").toString();
    smDevasHaviKor = Tradukado.value("smDevasHaviKor", "Ne Tradukita").toString();
    smDevasSavi = Tradukado.value("smDevasSavi", "Ne Tradukita").toString();
    smKoverto   = Tradukado.value("smKoverto",   "Ne Tradukita").toString();
    smDisketo   = Tradukado.value("smDisketo",   "Ne Tradukita").toString();
    smPordo     = Tradukado.value("smPordo",     "Ne Tradukita").toString();
    smLigilo    = Tradukado.value("smLigilo",    "Ne Tradukita").toString();
    Antauen     = Tradukado.value("Antauen",     "Ne Tradukita").toString();
    Nuligi      = Tradukado.value("Nuligi",      "Ne Tradukita").toString();
    smNeSono    = Tradukado.value("smNeSono",    "Ne Tradukita").toString();
    Tradukado.endGroup();

    Direkto = Tradukado.value("Traduko/Direkto", "LTR").toString();
    QString RTL_Marko, LTR_Marko;
    LTR_Marko = QString::fromUtf8("\u200E");
    RTL_Marko = QString::fromUtf8("\u200F");
    if (Direkto == "LTR")
         QApplication::setLayoutDirection(Qt::LeftToRight);
    else
         QApplication::setLayoutDirection(Qt::RightToLeft);


    Tradukado.beginGroup("Menuo");

    ui->label_Kio->setText( Tradukado.value("KioEstas",    "Ne Tradukita").toString() );

    ui->label_Kiel->setText(Tradukado.value("KielUzi",    "Ne Tradukita").toString() );

    ui->label_Konfiguroj->setText(Tradukado.value("Konfigurado",    "Ne Tradukita").toString());
    ui->Label_Konfigurado->setText(Tradukado.value("Konfigurado",    "Ne Tradukita").toString() );

    ui->label_Kreditoj->setText( Tradukado.value("Kreditoj",    "Ne Tradukita").toString() );
    ui->Label_Kreditoj->setText(Tradukado.value("Kreditoj",    "Ne Tradukita").toString() );

    ui->label_Eliri->setText( Tradukado.value("Eliri",    "Ne Tradukita").toString() );
    ui->label_Kie->setText(Tradukado.value("KieButono",    "Ne Tradukita").toString() );
    Tradukado.endGroup();

    int i;
    Tradukado.beginGroup("Konfig");
    QList<QLabel *> chiuj_label = ui->Pagho_Konfigurado->findChildren<QLabel *>();
    QString Tradukota, Tradukita;
    for (i = 0; i < chiuj_label.count(); i++)
    {
        if ( chiuj_label[i]->objectName().left(6) == "Konfig" )
        {
            Tradukota = chiuj_label[i]->objectName().mid(7);
            Tradukita = Tradukado.value(Tradukota, "Ne Tradukita").toString();
            chiuj_label[i]->setText(Tradukita);
        }
    }
    ui->radioButton->setText(ui->radioButton->text() + LTR_Marko);
    ui->radioButton_2->setText(ui->radioButton_2->text() + LTR_Marko);
    ui->radioButton_3->setText(ui->radioButton_3->text() + LTR_Marko);
    Tradukado.endGroup();


    Tradukado.beginGroup("Menuo4");
    chiuj_label = ui->Kredit->findChildren<QLabel *>();
    for (i = 0; i < chiuj_label.count(); i++)
    {
        if ( chiuj_label[i]->objectName().left(6) == "Kredit" )
        {
            Tradukota = chiuj_label[i]->objectName().mid(7);
            chiuj_label[i]->setText( Tradukado.value(Tradukota, "Ne Tradukita").toString());
        }
    }
    ui->Tradukinto->setText(sTradukinto);

    ListigasLingvojn();
}


void kurso::ListigasLingvojn()
{
    // plenigas la liston de lingvoj en la panelo "Konfiguroj"
    bool komencasElDosierujo = false;
    QFile dosiero(savasLoko + "traduklisto.ini");
    if (dosiero.exists()) {
        QSettings Tradukoj(dosiero.fileName(), QSettings::IniFormat);
        Tradukoj.setIniCodec("UTF-8");
        Tradukoj.beginGroup("0");
        QString unuaTraduko = Tradukoj.value("LingvoID", "??").toString() ;
        Tradukoj.endGroup();
        if ( unuaTraduko == "??" )
            komencasElDosierujo = true;
        else {

            for (int i = 0; i < 200; ++i) {
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
            }
        }
    }
    else komencasElDosierujo = true;

    if (komencasElDosierujo) {

        QString DosierNomo;
        QDirIterator it(":/tradukoj", QDirIterator::NoIteratorFlags);
        while (it.hasNext()) {
            QFileInfo fileInfo = it.next();
            DosierNomo = fileInfo.fileName();
            if (! DosierNomo.endsWith("trd"))
                continue;

            QSettings Tradukado(":/tradukoj/" + DosierNomo, QSettings::IniFormat);
            Tradukado.setIniCodec("UTF-8");

            Tradukado.beginGroup("Traduko");
            QStringList lingvo;
            lingvo << Tradukado.value("LingvoID", "??").toString();
            lingvo << Tradukado.value("Lingvo", "?????????").toString();
            lingvo << DosierNomo;
            lingvo << Tradukado.value("Dato", "?????????").toString();
            LingvoListo.append(lingvo);
            ui->Lingvo->addItem( lingvo.at(1));
            Tradukado.endGroup();
            }
    }

    Konfiguru();


}

void kurso::Konfiguru()
    {

    int trovita = ui->Lingvo->findText(sLingvo);
    ui->Lingvo->blockSignals(true);
    ui->Lingvo->setCurrentIndex(trovita);
    ui->Lingvo->blockSignals(false);

    if (iSistemo == 0)
        ui->radioButton->setChecked(true);
    else if (iSistemo == 1)
        ui->radioButton_2->setChecked(true);
    else
        ui->radioButton_3->setChecked(true);

    ui->Cxapeligo->setChecked(lCxapeligo);
    ui->Parolo->setChecked(lSxaltilo);
    ui->Noteto->setChecked(lNoteto);

    QFont novaTiparo(sTiparo);
    QFont novaTiparoEo(sTiparoEo);

    ui->Tiparo->blockSignals(true);
    ui->TiparoEo->blockSignals(true);
    ui->LiterGrando->blockSignals(true);
    ui->LiterGrandoEo->blockSignals(true);
    ui->glitilo_eo->blockSignals(true);
    ui->glitilo_traduko->blockSignals(true);

    ui->Tiparo->setCurrentFont(novaTiparo);
    ui->TiparoEo->setCurrentFont(novaTiparoEo);
    ui->LiterGrando->setValue(iLiterGrando);
    ui->LiterGrandoEo->setValue(iLiterGrandoEo);
    ui->glitilo_eo->setValue(iLiterGrandoEo);
    ui->glitilo_traduko->setValue(iLiterGrando);

    ui->tekstoEo->setStyleSheet("font-family: \"" + sTiparoEo + "\"; font-size: " + QString::number(ghustigas_tiparon(iLiterGrandoEo)) + "pt;");
    ui->tekstoLingvo->setStyleSheet("font-family: \"" + sTiparo + "\"; font-size: " + QString::number(ghustigas_tiparon(iLiterGrando)) + "pt;");


    ui->Tiparo->blockSignals(false);
    ui->LiterGrando->blockSignals(false);
    ui->TiparoEo->blockSignals(false);
    ui->LiterGrandoEo->blockSignals(false);
    ui->glitilo_eo->blockSignals(false);
    ui->glitilo_traduko->blockSignals(false);

    ui->tekstoLingvo->setText(sLingvo);

    QApplication::processEvents();

    Stilo();

}


void kurso::on_Sendas_clicked()
{
    QList<QTabWidget *> chiuj_tab =  ui->Paghujo->currentWidget()->findChildren<QTabWidget *>();
    if (chiuj_tab.count() > 0)
        Sendas(chiuj_tab[0]->currentWidget(), chiuj_tab[0]->currentIndex() + 1);
}


void kurso::on_printilo_clicked()
{
    QList<QTabWidget *> chiuj_tab =  ui->Paghujo->currentWidget()->findChildren<QTabWidget *>();
    if (chiuj_tab.count() > 0)
        Sendas_Printilo(chiuj_tab[0], "Leciono " + chiuj_tab[0]->objectName().mid(3,2), ui->prog_printilo);
}

void kurso::on_Cxapeligo_toggled(bool checked)
{
    lCxapeligo = checked;
    //ui->checkBox->setChecked(checked);
}


void kurso::on_radioButton_clicked(bool checked)
{
    //if (checked)
    //    iSistemo = 0;
    Q_UNUSED(checked)
}

void kurso::on_radioButton_2_clicked(bool checked)
{
    //if (checked)
    //    iSistemo = 1;
    Q_UNUSED(checked)
}

void kurso::on_radioButton_3_clicked(bool checked)
{
    //if (checked)
    //    iSistemo = 2;
    Q_UNUSED(checked)
}

void kurso::on_Lingvo_activated(int index)
{
    ui->tekstoLingvo->setText(ui->Lingvo->currentText());
    shanghitajKonfiguroj();
    Q_UNUSED(index)
}

void kurso::SavasKonfig2(Qt::ApplicationState state)
{
    if ( state == Qt::ApplicationSuspended ) {
        SavasKonfig();
        qDebug() << "Ghi savis la konfigurojn";
    }
}

void kurso::SavasKonfig()
{
    int i;

    QList<QTabWidget *> chiuj_tab = ui->Paghujo->findChildren<QTabWidget *>();

    for (i=0; i < chiuj_tab.count(); i++)
    {
        if ( (chiuj_tab.at(i)->objectName().left(3) == "Lec") || (chiuj_tab.at(i)->objectName() == "Fina_Ekzameno"))
            SxargxasEk(chiuj_tab.at(i), true);
    }

    QString Dirnomo = savasLoko;
    if (Dirnomo.right(1) != "/")
        Dirnomo.append("/");
    QSettings Konfiguro(Dirnomo + "kursokape.ini", QSettings::IniFormat);
    Konfiguro.setIniCodec("UTF-8");
    Konfiguro.beginGroup("Gxenerala");
    Konfiguro.setValue("Lingvo", sLingvo);
    Konfiguro.setValue("Tiparo", sTiparo);
    Konfiguro.setValue("TiparoEo", sTiparoEo);
    Konfiguro.setValue("Dosiero", sTradukoDosiero);
    Konfiguro.setValue("Cxapeligo", lCxapeligo);
    Konfiguro.setValue("Sistemo", iSistemo);
    Konfiguro.setValue("LastaLeciono", LastaLeciono);
    Konfiguro.setValue("LastaPagxo", LastaPagxo);
    Konfiguro.setValue("Sxaltilo", lSxaltilo);
    Konfiguro.setValue("Noteto", lNoteto);
    Konfiguro.setValue("LiterGrando", iLiterGrando );
    Konfiguro.setValue("LiterGrandoEo", iLiterGrandoEo );
    Konfiguro.setValue("FenestraStilo", iFenestraStilo);
    Konfiguro.endGroup();
    Konfiguro.sync();

    qDebug() << "Ekzercoj savitaj !!  ";

}

/*

void kurso::closeEvent(QCloseEvent *event)
{

    if (ui->Paghujo->currentIndex() > 0) // la uzulo estas en leciono, tiam Kurso revenas al la chefa pagho.
    {
        ui->Hejmo->click();
        event->ignore();
    }
    else
    {

        if (lSxaltilo)
        {
            Adiau();
            while (this->ludilo->mediaStatus() == QMediaPlayer::LoadingMedia || this->ludilo->state() == QMediaPlayer::PlayingState || this->ludilo->mediaStatus() == QMediaPlayer::BufferingMedia)
                QApplication::processEvents();
        }

        event->accept();
    }

        int i;

        QList<QTabWidget *> chiuj_tab = ui->Paghujo->findChildren<QTabWidget *>();

        for (i=0; i < chiuj_tab.count(); i++)
        {
            if ( (chiuj_tab.at(i)->objectName().left(3) == "Lec") || (chiuj_tab.at(i)->objectName() == "Fina_Ekzameno"))
                SxargxasEk(chiuj_tab.at(i), true);
        }

        SavasKonfig();

        QString Provizorujo = QDir::tempPath();
        if (Provizorujo.right(1) != "/")
            Provizorujo.append("/");

        // KODO POR FORIGI LA PORTEMPAJN PRONONCAJN DOSIEROJN
        for (i = 0; i < 4; i++)
            QFile::remove(Provizorujo + "prononco" + QString::number(i) + ".raw");


        if (lSxaltilo)
        {
            while (this->ludilo->mediaStatus() == QMediaPlayer::LoadingMedia || this->ludilo->state() == QMediaPlayer::PlayingState || this->ludilo->mediaStatus() == QMediaPlayer::BufferingMedia)
                QApplication::processEvents();
        }

        event->accept();
    }

}

*/

void kurso::on_KieButono_clicked()
{

    // klakas la butonon de la laste vizitita leciono
    switch (LastaLeciono) {
    case 1: ui->Leciono1->click(); break;
    case 2: ui->Leciono2->click(); break;
    case 3: ui->Leciono3->click(); break;
    case 4: ui->Leciono4->click(); break;
    case 5: ui->Leciono5->click(); break;
    case 6: ui->Leciono6->click(); break;
    case 7: ui->Leciono7->click(); break;
    case 8: ui->Leciono8->click(); break;
    case 9: ui->Leciono9->click(); break;
    case 10: ui->Leciono10->click(); break;
    case 11: ui->Leciono11->click(); break;
    case 12: ui->Leciono12->click(); break;
    case 13: ui->Leciono13->click(); break;
    }

}

void kurso::Stilo()
{

    this->setUpdatesEnabled(false);

    ShanghasTiparStilon();

    QFile file5( ":stiloj/kurso.qss");
    file5.open(QFile::ReadOnly);
    QString kurso = QLatin1String(file5.readAll());

    ui->Paghujo->setStyleSheet(kurso);

    this->setUpdatesEnabled(true);


}

void kurso::on_Tiparo_currentIndexChanged(const QString &arg1)
{
    ui->tekstoLingvo->setStyleSheet("font-family: \"" + arg1 + "\"; font-size: " + QString::number(ghustigas_tiparon(ui->LiterGrando->value())) + "pt;");
    shanghitajKonfiguroj();

}

void kurso::on_TiparoEo_currentIndexChanged(const QString &arg1)
{
    ui->tekstoEo->setStyleSheet("font-family: \"" + arg1 + "\"; font-size: " + QString::number(ghustigas_tiparon(ui->LiterGrandoEo->value())) + "pt;");
    shanghitajKonfiguroj();
}


void kurso::on_LiterGrando_valueChanged(int arg1)
{
    ui->tekstoLingvo->setStyleSheet("font-family: \"" + ui->Tiparo->currentText() + "\"; font-size: " + QString::number(ghustigas_tiparon(arg1)) + "pt;");
    ui->glitilo_traduko->blockSignals(true);
    ui->glitilo_traduko->setValue(arg1);
    ui->glitilo_traduko->blockSignals(false);
    shanghitajKonfiguroj();
}


void kurso::on_LiterGrandoEo_valueChanged(int arg1)
{
    ui->tekstoEo->setStyleSheet("font-family: \"" + ui->TiparoEo->currentText() + "\"; font-size: " + QString::number(ghustigas_tiparon(arg1)) + "pt;");
    ui->glitilo_eo->blockSignals(true);
    ui->glitilo_eo->setValue(arg1);
    ui->glitilo_eo->blockSignals(false);
    shanghitajKonfiguroj();
}

void kurso::ShanghasTiparon()
{
    QCursor malnova = this->cursor();
    QCursor atendu = QCursor( Qt::WaitCursor);
    this->setCursor( atendu );
    QApplication::processEvents();

    ShanghasTiparStilon();

    QApplication::processEvents();

    this->setCursor( malnova );
}

void kurso::ShanghasTiparStilon()
{

    QString NovaStilo;

    int iGrandoEo = ghustigas_tiparon(iLiterGrandoEo);
    int iGrando = ghustigas_tiparon(iLiterGrando);
    QFont traduka(sTiparo);
    traduka.setPointSize(iGrando);
    qApp->setFont(traduka);
    NovaStilo.append( "myLabel#label_Kie, #label_Kreditoj, #label_Kio, #label_Konfiguroj, #label_Kiel, #label_Eliri { font-size: " + QString::number( int(iGrando  -1) ) + "pt; font-weight: bold; } " );
    NovaStilo.append( "titolo { font-size: " + QString::number( int(iGrando   * 1.25) ) + "pt; font-weight: bold; min-height: 1.2em;} " );
    NovaStilo.append( "QLabel[lingvo=\"eo\"], klakbutono_nova, neklakebla_nova, korekta, cx_edit, cx_plainedit, cx_edit_minuskla { font-family: \""+ sTiparoEo + "\";  font-size: " + QString::number( iGrandoEo ) + "pt;} " );
    NovaStilo.append( "titolo[lingvo=\"eo\"], QPushButton[tipo=\"speciala\"], QLabel[tipo=\"afikso\"]  { font-family: \""+ sTiparoEo + "\"; font-size: " + QString::number( int(iGrandoEo * 1.25) ) + "pt; font-weight: bold; min-height: 1.2em;} " );

    ui->centralWidget->setStyleSheet(NovaStilo);


}


void kurso::on_Konfigurado_clicked()
{

    QList<QWidget *> chiuj_paghoj = ui->Paghujo->findChildren<QWidget *>("Pagho_Konfigurado");
    if (chiuj_paghoj.size() > 0)
        ui->Paghujo->setCurrentWidget(chiuj_paghoj.at(0));
    ui->butonujo->setVisible(true);
    ui->shanghasKonfigurojn->setVisible(true);
}

void kurso::on_KioEstas_clicked()
{
    QDesktopServices::openUrl(QUrl(helpdosiero("kio"), QUrl::TolerantMode));

}

void kurso::on_KielUzi_clicked()
{

    QDesktopServices::openUrl(QUrl(helpdosiero("kiel"), QUrl::TolerantMode));
}

void kurso::on_Kreditoj_clicked()
{
    QList<QWidget *> chiuj_paghoj = ui->Paghujo->findChildren<QWidget *>("Pagho_Kreditoj");
    if (chiuj_paghoj.size() > 0)
    {
        ui->Paghujo->setCurrentWidget(chiuj_paghoj.at(0));
        ui->Kredit->setCurrentIndex(0);
        ui->butonujo->setVisible(true);
    }

}

void kurso::on_Parolo_toggled(bool checked)
{
    lSxaltilo = checked;
}

void kurso::on_Noteto_toggled(bool checked)
{
    lNoteto = checked;
}


void kurso::ShanghasPaghon(QString Nomo, QFrame * lecionujo)
{
    QList<QWidget *> chiuj_paghoj = ui->Paghujo->findChildren<QWidget *>(Nomo);
    if (chiuj_paghoj.size() > 0)
    {
        // Kreas la lecionan paghon ene de la pagho "paghujo"
        if (lecionujo == nullptr){
            qDebug() << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss,zzz");

            if (Nomo == "Pagho01") {
                    frame_lec01 = new lec01(chiuj_paghoj.at(0));
                    chiuj_paghoj.at(0)->layout()->addWidget(frame_lec01);}
            else if (Nomo == "Pagho02") {
                    frame_lec02 = new lec02(chiuj_paghoj.at(0));
                    chiuj_paghoj.at(0)->layout()->addWidget(frame_lec02);}
            else if (Nomo == "Pagho03") {
                    frame_lec03 = new lec03(chiuj_paghoj.at(0));
                    chiuj_paghoj.at(0)->layout()->addWidget(frame_lec03);}
            else if (Nomo == "Pagho04") {
                    frame_lec04 = new lec04(chiuj_paghoj.at(0));
                    chiuj_paghoj.at(0)->layout()->addWidget(frame_lec04);}
            else if (Nomo == "Pagho05") {
                    frame_lec05 = new lec05(chiuj_paghoj.at(0));
                   chiuj_paghoj.at(0)->layout()->addWidget(frame_lec05);}
            else if (Nomo == "Pagho06") {
                    frame_lec06 = new lec06(chiuj_paghoj.at(0));
                    chiuj_paghoj.at(0)->layout()->addWidget(frame_lec06);}
            else if (Nomo == "Pagho07") {
                    frame_lec07 = new lec07(chiuj_paghoj.at(0));
                    chiuj_paghoj.at(0)->layout()->addWidget(frame_lec07);}
            else if (Nomo == "Pagho08") {
                    frame_lec08 = new lec08(chiuj_paghoj.at(0));
                    chiuj_paghoj.at(0)->layout()->addWidget(frame_lec08);}
            else if (Nomo == "Pagho09") {
                    frame_lec09 = new lec09(chiuj_paghoj.at(0));
                    chiuj_paghoj.at(0)->layout()->addWidget(frame_lec09);}
            else if (Nomo == "Pagho10") {
                    frame_lec10 = new lec10(chiuj_paghoj.at(0));
                    chiuj_paghoj.at(0)->layout()->addWidget(frame_lec10);}
            else if (Nomo == "Pagho11") {
                    frame_lec11 = new lec11(chiuj_paghoj.at(0));
                    chiuj_paghoj.at(0)->layout()->addWidget(frame_lec11);}
            else if (Nomo == "Pagho12") {
                    frame_lec12 = new lec12(chiuj_paghoj.at(0));
                    chiuj_paghoj.at(0)->layout()->addWidget(frame_lec12);}
            else if (Nomo == "Pagho13") {
                    frame_lec13 = new lec13(chiuj_paghoj.at(0));
                    chiuj_paghoj.at(0)->layout()->addWidget(frame_lec13);}
            // fino de la kreado de la leciona pagho
            qDebug() << "La unua fojo " + QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss,zzz");

            // kashas la supran parton (tab) de la paghoj
            if (sSistemo == "osx")
                chiuj_paghoj.at(0)->setStyleSheet("QTabWidget::pane {top: -1em;}   QTabBar::tab {height: 0px; width: 0px;} QTabWidget::tab-bar {height: 0px; width: 0px;}");
            else
                chiuj_paghoj.at(0)->setStyleSheet("QTabBar::tab {height: 0px; width: 0px;} QTabWidget::tab-bar {height: 0px; width: 0px;}");

            // Sxargxas la respondon al la skribaj ekzercoj
            int i;
            QList<QTabWidget *> chiuj_tab_nova = chiuj_paghoj.at(0)->findChildren<QTabWidget *>();
            for (i=0; i < chiuj_tab_nova.count(); i++)
            {
                if ( (chiuj_tab_nova.at(i)->objectName().left(3) == "Lec") || (chiuj_tab_nova.at(i)->objectName() == "Fina_Ekzameno"))
                    SxargxasEk(chiuj_tab_nova.at(i), false);
            }
            // fino de la sxargxado


            // la sekvanta kodo estas por chirkauiri cimon en QT (5.14), kiu ne automate ghustigas la rulujojn (QScrollArea)
            QList<QScrollArea *> chiuj_rulujoj = chiuj_paghoj.at(0)->findChildren<QScrollArea  *>();
            for (i=0; i < chiuj_rulujoj.count(); i++) {
                chiuj_rulujoj.at(i)->setWidgetResizable(false);
            }
            // En la leciona klaso-dosiero, estas kodo por ghustigi la rulujon chiufoje, kiam pagho shanghigas.

            QApplication::processEvents();
        }

        ui->Paghujo->setCurrentWidget(chiuj_paghoj.at(0));
        QList<QTabWidget *> chiuj_tab = chiuj_paghoj.at(0)->findChildren<QTabWidget *>();
        if (chiuj_tab.count() > 0)
        {
            int iLeciono = Nomo.right(2).toInt();
            if (TradukitajLecionoj[iLeciono - 1] != sTradukoDosiero) {
                // TRADUKAS la lecionon se chi tiu estas la unuja fojo, ke ghi montrighas AU se la uzulo shanghis la traduklingvon
                Trad(chiuj_paghoj.at(0), chiuj_tab.at(0)->objectName() );
                TradukitajLecionoj[iLeciono - 1] = sTradukoDosiero;

            }
            // la sekvanta kodo estas por chirkauiri cimon en QT (5.14), kiu ne automate ghustigas la rulujojn (QScrollArea)
            if (chiuj_tab.at(0)->currentIndex() == 0
                || (chiuj_tab.at(0)->currentIndex() == LastaPagxo
                && ui->Paghujo->currentIndex() == LastaLeciono)) {
                QList<QScrollArea *> chiuj_rulujoj = chiuj_tab.at(0)->currentWidget()->findChildren<QScrollArea  *>();
                int i;
                for (i=0; i < chiuj_rulujoj.count(); i++) {
                    chiuj_rulujoj.at(i)->setWidgetResizable(true);
                }
            }

            if (LastaLeciono != ui->Paghujo->currentIndex()) {
                LastaPagxo = 0;
                chiuj_tab.at(0)->setCurrentIndex(0);
            }
            else chiuj_tab.at(0)->setCurrentIndex(LastaPagxo);


            LastaLeciono = ui->Paghujo->currentIndex();


        }

        ui->butonujo->setVisible(true);
        ui->paghopiedo->setVisible(false);
        /*
        if (QSysInfo::productType() != "android" &&
            QSysInfo::productType() != "ios")
            ui->printilo->setVisible(true); // la funkcieco "printi lecionon" ne estas signifa se oni uzas porteblan aparaton
        */
        ui->navigujo->setVisible(true);
        ui->Paghujo->updateGeometry();
        komencas_navigujon();
    }
}

void kurso::montras_koverton(bool chu, int pagho)
{
    //if (!tradukilo)
    //   ui->Sendas->setVisible(chu);
    LastaPagxo = pagho;
    Q_UNUSED(chu)
}


void kurso::on_Leciono1_clicked()
{
    ShanghasPaghon("Pagho01", frame_lec01);
}

void kurso::on_Leciono2_clicked()
{
    EkzercoAkuzativoTrad = "0204";
    ShanghasPaghon("Pagho02", frame_lec02);
}

void kurso::on_Leciono3_clicked()
{
    ShanghasPaghon("Pagho03", frame_lec03);
}

void kurso::on_Leciono4_clicked()
{
    ShanghasPaghon("Pagho04", frame_lec04);
}
void kurso::on_Leciono5_clicked()
{
    ShanghasPaghon("Pagho05", frame_lec05);
}
void kurso::on_Leciono6_clicked()
{
    EkzercoAkuzativoTrad = "0605";
    ShanghasPaghon("Pagho06", frame_lec06);
}
void kurso::on_Leciono7_clicked()
{
    ShanghasPaghon("Pagho07", frame_lec07);
}
void kurso::on_Leciono8_clicked()
{
    EkzercoAkuzativoTrad = "0802";
    ShanghasPaghon("Pagho08", frame_lec08);
}
void kurso::on_Leciono9_clicked()
{
    ShanghasPaghon("Pagho09", frame_lec09);
}
void kurso::on_Leciono10_clicked()
{
    EkzercoAkuzativoTrad = "1001";
    ShanghasPaghon("Pagho10", frame_lec10);
}
void kurso::on_Leciono11_clicked()
{
    ShanghasPaghon("Pagho11", frame_lec11);
}
void kurso::on_Leciono12_clicked()
{
    EkzercoAkuzativoTrad = "1202";
    ShanghasPaghon("Pagho12", frame_lec12);
}
void kurso::on_Leciono13_clicked()
{
    ShanghasPaghon("Pagho13", frame_lec13);
}


void kurso::Saluton()
{
    if (lSxaltilo)
    {
        int iAleat6;
        QString sMp3dos;
        iAleat6 = random(2);
        if (iAleat6 == 0)
            sMp3dos = "saluton";
        else
        {
            QTime nun = QTime::currentTime();
            int horo = nun.hour();

            if ((horo >= 16) && (horo <= 20))
                sMp3dos = "vespero";
            else if ((horo >= 5) && (horo <= 11))
            {
                iAleat6 = random(2);
                if (iAleat6 == 0)
                    sMp3dos = "matenon";
                else  sMp3dos = "tagon";
            }
            else if ((horo >= 12) && (horo <= 15))
                sMp3dos = "tagon";
            else sMp3dos = "nokton";
        }

        QDir sonoj(mrLoko + "sonoj/");
        QStringList filtriloj;
        filtriloj << sMp3dos + "?" + mp3_finajho;
        sonoj.setNameFilters(filtriloj);
        if (sonoj.count() > 0) {
            int kvanto = sizeof(sonoj.count());
            iAleat6 = random(kvanto);
            QString dosiernomo = "sonoj/" + sonoj.entryList().at(iAleat6);
            if (sSistemo == "android")
                ludilo->setMedia(QUrl(mrLoko + dosiernomo.toLower()));
            else
                ludilo->setMedia(QUrl::fromLocalFile(mrLoko + dosiernomo.toLower()));

            ludilo->play();

        }

    }

}


void kurso::Ghustigas_fenestron()
{

    //ShanghasTiparStilon();
    // Stilo();

    //QApplication::processEvents();
    /*

    resize(1,1);
    QApplication::processEvents();

    QDesktopWidget *tela = QApplication::desktop();
    int nrotela = tela->primaryScreen();
    QRect grandeco = tela->availableGeometry(nrotela);
    QRect ekstera_grandeco = frameGeometry();
    QRect interna_grandeco = geometry();

    alteco_originala = interna_grandeco.height();
    largheco_originala = interna_grandeco.width();

    alteco_maksimuma = grandeco.height() - (ekstera_grandeco.height() - interna_grandeco.height());
    largheco_maksimuma = grandeco.width() - (ekstera_grandeco.width() - interna_grandeco.width()) ;


    if (largheco_maksimuma < largheco_originala)
    {
        Eta_Fenestro = true;
        largheco_originala = largheco_maksimuma;
    }


    if (alteco_maksimuma < alteco_originala)
    {
        Malalta_Fenestro = true;
        alteco_originala = alteco_maksimuma;
    }

    this->setMaximumSize(largheco_maksimuma, alteco_maksimuma);
    */

}

void kurso::Centrigas_Fenestron()
{
    QList<QScreen *> ekrano = QGuiApplication::screens();
    this->adjustSize();
    qApp->processEvents();
    QRect frect = frameGeometry();
    frect.moveCenter(ekrano.at(0)->availableGeometry().center());
    move(frect.topLeft());

}

void kurso::showEvent ( QShowEvent * event )
{
    /* ne plu bezonata ekde Kurso 5 (kape)*/

    Q_UNUSED(event)


}


void kurso::Fenestra_Stilo()
{

}

void kurso::ReGrandigas_Fenestron()
{

}

void kurso::Malgrandigas()
{

}

void kurso::lokigas_paghotrad(QString novapagho)
{
    if      (novapagho == "Pagho01")
        ShanghasPaghon(novapagho, frame_lec01);
    else if (novapagho == "Pagho02")
        ShanghasPaghon(novapagho, frame_lec02);
    else if (novapagho == "Pagho03")
        ShanghasPaghon(novapagho, frame_lec03);
    else if (novapagho == "Pagho04")
        ShanghasPaghon(novapagho, frame_lec04);
    else if (novapagho == "Pagho05")
        ShanghasPaghon(novapagho, frame_lec05);
    else if (novapagho == "Pagho06")
        ShanghasPaghon(novapagho, frame_lec06);
    else if (novapagho == "Pagho07")
        ShanghasPaghon(novapagho, frame_lec07);
    else if (novapagho == "Pagho08")
        ShanghasPaghon(novapagho, frame_lec08);
    else if (novapagho == "Pagho09")
        ShanghasPaghon(novapagho, frame_lec09);
    else if (novapagho == "Pagho10")
        ShanghasPaghon(novapagho, frame_lec10);
    else if (novapagho == "Pagho11")
        ShanghasPaghon(novapagho, frame_lec11);
    else if (novapagho == "Pagho12")
        ShanghasPaghon(novapagho, frame_lec12);
    else if (novapagho == "Pagho13")
        ShanghasPaghon(novapagho, frame_lec13);

}

void kurso::lokigas_frazotrad(QString novapagho, QString novafrazo)
{
    QList<QWidget *> chiuj_paghoj = ui->Paghujo->findChildren<QWidget *>(novapagho);
    if (chiuj_paghoj.size() > 0)
    {
        if (novafrazo.left(3) == "Lec" )
        {
            QList<QTabWidget *> chiuj_tab = chiuj_paghoj.at(0)->findChildren<QTabWidget *>();
            if (chiuj_tab.count() > 0)
            {

                QList<QLabel *> chiuj_label = chiuj_tab.at(0)->findChildren<QLabel *>(novafrazo);
                if (chiuj_label.size() > 0)
                {
                    int indice;
                    QWidget * ujo = chiuj_label.at(0)->parentWidget();
                    QString ujo_nomo = ujo->metaObject()->className() ;
                    while ( ujo_nomo != "QScrollArea"){
                        ujo = ujo->parentWidget();
                        ujo_nomo = ujo->metaObject()->className() ;
                    }

                    indice = chiuj_tab.at(0)->indexOf( ujo->parentWidget() );

                    chiuj_tab.at(0)->setCurrentIndex(indice);
                    komencas_navigujon();

                    if (antaua)
                        antaua->setFrameShape(QFrame::NoFrame);

                    chiuj_label.at(0)->setFrameShape(QFrame::Box);

                    QScrollArea *rulujo = dynamic_cast<QScrollArea*>( ujo);
                    rulujo->ensureWidgetVisible(chiuj_label.at(0));

                    antaua = chiuj_label.at(0);

                }
            }
        }
        if (novapagho == "Pagho_Konfigurado")
        {
            QList<QLabel *> chiuj_label = chiuj_paghoj.at(0)->findChildren<QLabel *>(novafrazo);
            if (chiuj_label.size() > 0)
            {
                if (antaua)
                    antaua->setFrameShape(QFrame::NoFrame);

                chiuj_label.at(0)->setFrameShape(QFrame::Box);

                antaua = chiuj_label.at(0);

            }

        }
    }

}

void kurso::listigas_trad()
{
    QString nome_arq (":/tradukoj/tradukendaj.tdf");
    QSettings traduko(nome_arq, QSettings::IniFormat);
    traduko.setIniCodec("UTF-8");
    QString sekcio = "Eraro", teksto, nomo;

    QList<QTabWidget *> chiuj_paghoj = ui->Paghujo->findChildren<QTabWidget *>();
    int i, j, k, contador;

    for (i = 0; i < chiuj_paghoj.size(); i++)
    {
        sekcio = chiuj_paghoj.at(i)->objectName();

        traduko.beginGroup(sekcio);

        contador = 0;

        for (k = 0; k < chiuj_paghoj.at(i)->count(); k++)
        {


            QList<QLabel *> chiuj_label = chiuj_paghoj.at(i)->widget(k)->findChildren<QLabel *>();


            for (j = 0; j < chiuj_label.size(); j++)
            {
                if ((chiuj_label.at(j)->objectName().contains(sekcio + "_") || chiuj_label.at(j)->objectName() == "Ekz_Plen2" ) &&
                        !( chiuj_label.at(j)->objectName().contains("Pan") || (chiuj_label.at(j)->objectName().contains("Memo"))) )
                {
                    nomo = "";
                    if ( chiuj_label.at(j)->objectName().contains(sekcio + "_"))
                        nomo = chiuj_label.at(j)->objectName().replace(sekcio + "_", "");
                    else
                        if (chiuj_label.at(j)->objectName() == "Ekz_Plen2")
                            nomo = ( chiuj_label[j]->parentWidget()->objectName().mid(5,1) != "B") ?  "TFrame41.Label84" : "Frame42.Label84";

                    if (nomo != "")
                    {
                        teksto = "000" + QString::number(contador);
                        traduko.setValue(teksto.right(3), nomo);
                        contador++;
                    }
                }
            }
        }

        traduko.endGroup();


    }

    traduko.sync();
}

void kurso::on_shanghasKonfigurojn_clicked()
{
    bool shanghasStilon = false;
    if (ui->radioButton->isChecked()) iSistemo = 0;
    if (ui->radioButton_2->isChecked()) iSistemo = 1;
    if (ui->radioButton_3->isChecked()) iSistemo = 2;

    if (ui->Lingvo->currentText() != sLingvo) {
        sLingvo = LingvoListo[ui->Lingvo->currentIndex()][1];
        sTradukoDosiero = LingvoListo[ui->Lingvo->currentIndex()][2];
        // elshutas la novan tradukon
        QUrl LingvojUrl("http://kurso.com.br/datumoj/tradukoj/" + sTradukoDosiero );
        elshutilo = new FileDownloader(LingvojUrl, sTradukoDosiero , this);

        connect(elshutilo, SIGNAL (downloaded()), this, SLOT (Traduku()));
    }

    if (ui->Tiparo->currentText() != sTiparo) {
        sTiparo = ui->Tiparo->currentText();
        shanghasStilon = true;
    }
    if (ui->TiparoEo->currentText() != sTiparoEo) {
        sTiparoEo = ui->TiparoEo->currentText();
        shanghasStilon = true;
    }

    if (ui->LiterGrando->value() != iLiterGrando) {
        iLiterGrando = ui->LiterGrando->value();
        shanghasStilon = true;
    }
    if (ui->LiterGrandoEo->value() != iLiterGrandoEo) {
        iLiterGrandoEo = ui->LiterGrandoEo->value();
        shanghasStilon = true;
    }


    if (shanghasStilon) ShanghasTiparStilon();
    ui->shanghasKonfigurojn->setEnabled(false);
    ui->shanghasKonfigurojn->setVisible(false);
    ui->Hejmo->click();


}

void kurso::shanghitajKonfiguroj()
{
    int novaSistemo = 0;
    if (ui->radioButton->isChecked()) novaSistemo = 0;
    if (ui->radioButton_2->isChecked()) novaSistemo = 1;
    if (ui->radioButton_3->isChecked()) novaSistemo = 2;

    if ( ui->Lingvo->currentText() != sLingvo ||
         ui->Tiparo->currentText() != sTiparo ||
        ui->TiparoEo->currentText() != sTiparoEo ||
        ui->LiterGrando->value() != iLiterGrando ||
        ui->LiterGrandoEo->value() != iLiterGrandoEo ||
        novaSistemo != iSistemo )
        ui->shanghasKonfigurojn->setEnabled(true);
    else
        ui->shanghasKonfigurojn->setEnabled(false);

}


void kurso::on_dekstren_clicked()
{
    // iras dekstren en la pagharo
    QList<QTabWidget *> chiuj_tab = ui->Paghujo->currentWidget()->findChildren<QTabWidget *>();
    if (chiuj_tab.count()> 0){
        int KiomdaPaghoj = chiuj_tab.at(0)->count();
        int NunaPagho = chiuj_tab.at(0)->currentIndex();


        if (NunaPagho == KiomdaPaghoj-1) NunaPagho = 0;
        else NunaPagho++;

        this->ui->kiom_da_paghoj->setText(QString::number(NunaPagho+1) + "/" + QString::number(KiomdaPaghoj));
        chiuj_tab.at(0)->setCurrentIndex(NunaPagho);
    }


}

void kurso::on_maldekstren_clicked()
{
    // iras maldekstren en la pagharo
    QList<QTabWidget *> chiuj_tab = ui->Paghujo->currentWidget()->findChildren<QTabWidget *>();
    if (chiuj_tab.count()> 0){
        int KiomdaPaghoj = chiuj_tab.at(0)->count();
        int NunaPagho = chiuj_tab.at(0)->currentIndex();


        if (NunaPagho == 0) NunaPagho = KiomdaPaghoj-1;
        else NunaPagho--;

        this->ui->kiom_da_paghoj->setText(QString::number(NunaPagho+1) + "/" + QString::number(KiomdaPaghoj));
        chiuj_tab.at(0)->setCurrentIndex(NunaPagho);
    }

}

void kurso::komencas_navigujon()
{
    // montras la navigujon kiam la leciono montrighas
    QString tradukDosiero;

    QFile novaTraduko(savasLoko + sTradukoDosiero)    ;
    if ( novaTraduko.exists())
        tradukDosiero = savasLoko + sTradukoDosiero;
    else
        tradukDosiero = ":/tradukoj/" + sTradukoDosiero;

    QSettings Tradukado(tradukDosiero, QSettings::IniFormat);
    Tradukado.setIniCodec("UTF-8");
    QString Direkto = Tradukado.value("Traduko/Direkto", "LTR").toString();

    if (Direkto == "LTR") {
        ui->maldekstren->setIcon(QIcon(":/ikonoj_androjdo/baseline_arrow_back_black_36.png"));
        ui->dekstren->setIcon(QIcon(":/ikonoj_androjdo/baseline_arrow_forward_black_36.png"));

    }
    else {
        ui->dekstren->setIcon(QIcon(":/ikonoj_androjdo/baseline_arrow_back_black_36.png"));
        ui->maldekstren->setIcon(QIcon(":/ikonoj_androjdo/baseline_arrow_forward_black_36.png"));

    }


    QList<QTabWidget *> chiuj_tab = ui->Paghujo->currentWidget()->findChildren<QTabWidget *>();
    if (chiuj_tab.count()> 0){
        int KiomdaPaghoj = chiuj_tab.at(0)->count();
        int NunaPagho = chiuj_tab.at(0)->currentIndex();
        this->ui->kiom_da_paghoj->setText(QString::number(NunaPagho+1) + "/" + QString::number(KiomdaPaghoj));

        QString bildo = ":/ikonoj_androjdo/hejmo/leciono" + chiuj_tab.at(0)->parent()->objectName().mid(3) + ".png";
        this->ui->leciono->setPixmap(QPixmap(bildo));
    }
    ui->shanghasKonfigurojn->setVisible(false);

}

void kurso::on_butono_androjdo_clicked()
{
    ui->paghopiedo->setVisible(! ui->paghopiedo->isVisible());
}

/* Chi tiu parto eniros en venonta versio
void kurso::on_Bildoludo_butono_clicked()
{
    QList<QWidget *> chiuj_paghoj = ui->Paghujo->findChildren<QWidget *>("Bildoludo");
    if (chiuj_paghoj.size() > 0)
    {
        // Kreas la bildoludan paghon ene de la pagho "paghujo"
        if (frame_bildoludo == nullptr){
            qDebug() << QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss,zzz");
            frame_bildoludo = new bildoludo(chiuj_paghoj.at(0));
            QVBoxLayout *layout = new QVBoxLayout;
            layout->setMargin(0);
            layout->addWidget(frame_bildoludo);
            chiuj_paghoj.at(0)->setLayout(layout);
            qDebug() << "BildoLudo: " + QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss,zzz");
        }
        ui->Paghujo->setCurrentWidget(chiuj_paghoj.at(0));
        ui->butonujo->setVisible(true);

    }
}
*/

void kurso::on_tradukilo_clicked()
{

    if (!tradukilo)
    {
        tradukilo = new traduko(this);
        tradukilo->setWindowModality(Qt::NonModal);
        QApplication::processEvents();
        QFont tiparo(sTiparoEo);
        tiparo.setPointSize(ghustigas_tiparon(iLiterGrandoEo));
        tradukilo->setFont(tiparo);
        connect(tradukilo, SIGNAL(novapagho(QString)), this, SLOT(lokigas_paghotrad(QString)), Qt::DirectConnection);
        connect(tradukilo, SIGNAL(novafrazo(QString, QString)), this, SLOT(lokigas_frazotrad(QString, QString)), Qt::DirectConnection);
    }

    tradukilo->show();
    tradukilo->raise();
    tradukilo->activateWindow();
}


void kurso::on_glitilo_eo_valueChanged(int value)
{
    ui->LiterGrandoEo->setValue(value);
}

void kurso::on_glitilo_traduko_valueChanged(int value)
{
    ui->LiterGrando->setValue(value);
}

void kurso::on_Eliri_clicked()
{
    if (lSxaltilo) {
        Adiau();
        while (this->ludilo->mediaStatus() == QMediaPlayer::LoadingMedia
               || this->ludilo->state() == QMediaPlayer::PlayingState
               || this->ludilo->mediaStatus() == QMediaPlayer::BufferingMedia)
            QApplication::processEvents();
    }

    qApp->quit();
}

void kurso::on_label_Kie_clicked()
{
    on_KieButono_clicked();
}

void kurso::on_label_Kreditoj_clicked()
{
    on_Kreditoj_clicked();
}

void kurso::on_label_Kio_clicked()
{
    on_KioEstas_clicked();
}

void kurso::on_label_Konfiguroj_clicked()
{
    on_Konfigurado_clicked();
}

void kurso::on_label_Kiel_clicked()
{
    on_KielUzi_clicked();
}

void kurso::on_label_Eliri_clicked()
{
    on_Eliri_clicked();
}
