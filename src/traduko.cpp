#include "traduko.h"
#include "ui_traduko.h"
#include "QtGui"
#include "QtCore"
#include "funkcioj.h"
//#include "kurso.h"
#include <QDesktopServices>
#include <QMessageBox>
#include <QFileDialog>
#include <QScroller>
#include <QScrollBar>

traduko::traduko(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::traduko)
{
    ui->setupUi(this);

    this->setWindowTitle("Tradukilo");

    QScroller::grabGesture(this->ui->scrollArea->viewport(), QScroller::LeftMouseButtonGesture);

    QScrollBar* scrollbar = ui->scrollArea->verticalScrollBar();
    QObject::connect(scrollbar, SIGNAL(rangeChanged(int,int)), this, SLOT(moveScrollBarToBottom(int, int)));

    QStringList tradukeroj;
    tradukeroj << "Gheneralaj"
    << "Lec01"
    << "Lec02"
    << "Lec03"
    << "Lec04"
    << "Lec05"
    << "Lec06"
    << "Lec07"
    << "Lec08"
    << "Lec09"
    << "Lec10"
    << "Lec11"
    << "Lec12"
    << "Lec13"
    << "Konfig"
    << "Menuo"
    << "Menuo4"
    << "Mesagxoj"
    << "Ekzerco-0204"
    << "Ekzerco-0502"
    << "Ekzerco-0602"
    << "Ekzerco-0605"
    << "Ekzerco-0702"
    << "Ekzerco-0801"
    << "Ekzerco-0802"
    << "Ekzerco-0902"
    << "Ekzerco-1001"
    << "Ekzerco-1002"
    << "Ekzerco-1202"
    << "Ekzerco-Klarigoj" ;
    ui->Listo->addItems(tradukeroj);

    ListigasLingvojn();

    konfiguro();

}

traduko::~traduko()
{
    delete ui;
}

void traduko::on_literGrando_valueChanged(int arg1)
{
    ui->horizontalSlider->blockSignals(true);
    ui->horizontalSlider->setValue(ui->literGrando->value());
    ui->horizontalSlider->blockSignals(false);
    on_tiparo_currentIndexChanged(ui->tiparo->currentText());
    Q_UNUSED(arg1)
}

void traduko::on_tiparo_currentIndexChanged(const QString &arg1)
{
    int iGrando = ghustigas_tiparon(ui->literGrando->value());
    ui->Memo1->setStyleSheet("font-family: \"" + arg1 + "\"; font-size: " + QString::number(iGrando) + "pt;");
    ui->Memo2->setStyleSheet("font-family: \"" + arg1 + "\"; font-size: " + QString::number(iGrando) + "pt;"
                             "background-color: rgb(199, 227, 255); padding: 5px;");
    ui->Memo3->setStyleSheet("font-family: \"" + arg1 + "\"; font-size: " + QString::number(iGrando) + "pt;"
                             "background-color: rgb(213, 255, 191); padding: 5px;");

}

void traduko::konfiguro()
{
    QSettings Konfiguro(savasLoko + "kursokape.ini", QSettings::IniFormat );
    Konfiguro.setIniCodec("UTF-8");
    Konfiguro.beginGroup("Tradukilo");
    ui->dulitera_lingvokodo->setText( Konfiguro.value("LingvoID", "").toString() );
    ui->Edit1->setText( Konfiguro.value("Lingvo", "").toString() );
    ui->Edit_dosiero->setText( Konfiguro.value("Dosiero", "mia_traduko.trd").toString() );
    ui->Edit2->setText( Konfiguro.value("Tradukinto", "").toString() );

    ui->dulitera_lingvokodo->setPlaceholderText("aa");
    ui->Edit1->setPlaceholderText(QString::fromUtf8("Skribu ĉi tie la nomon de via lingvo"));
    ui->Edit2->setPlaceholderText(QString::fromUtf8("Skribu ĉi tie vian nomon"));
    ui->Edit_dosiero->setPlaceholderText(QString::fromUtf8("Skribu ĉi tie la nomon de la dosiero"));

    iLiterGrando = Konfiguro.value("LiterGrando", 12).toInt();

    QString sTiparo     = Konfiguro.value("Tiparo", "DejaVu Sans").toString();
    Referenca1  = Konfiguro.value("Referenca1", "esperanto.trd").toString();
    Referenca2  = Konfiguro.value("Referenca2", "angla.trd").toString();
    Leciono     = Konfiguro.value("LastaLeciono", 0).toInt();
    Pozicio     = Konfiguro.value("Pozicio", 0).toInt();

    Dosierujo = savasLoko;

    ui->vojo_dosierujo->setText(Dosierujo);

    Konfiguro.endGroup();

    QFont novaTiparo(sTiparo);

    ui->tiparo->blockSignals(true);
    ui->literGrando->blockSignals(true);
    ui->horizontalSlider->blockSignals(true);

    ui->tiparo->setCurrentFont(novaTiparo);
    ui->literGrando->setValue(iLiterGrando);
    ui->horizontalSlider->setValue(iLiterGrando);

    ui->tiparo->blockSignals(false);
    ui->literGrando->blockSignals(false);
    ui->horizontalSlider->blockSignals(false);

    on_tiparo_currentIndexChanged(sTiparo);

    bool Ekzistas1 = false, Ekzistas2 = false;

    for (int i = 0; i < LingvoListo.size(); i++)
    {
        if (LingvoListo.at(i).at(2) == Referenca1)
        {
            ui->lingvoj1->setCurrentIndex(i);
            Ekzistas1 = true;
        }

        if (LingvoListo.at(i).at(2) == Referenca2)
        {
            ui->lingvoj2->setCurrentIndex(i);
            Ekzistas2 = true;
        }
    }

    if ( ! ( Ekzistas1 && Ekzistas2 ) )
    {
        QMessageBox msgBox(QApplication::activeWindow());
        msgBox.setText(QString::fromUtf8("Mankas la tradukdosiero por antaŭe elektita referenca lingvo.\nAlia lingvo estas elektita por referenco.\nBonvolu kontroli tion.") );
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        if ( ! Ekzistas1 )
        {
            Referenca1 = LingvoListo.at(0).at(2);
            ui->lingvoj1->setCurrentIndex(0);
            ui->lingvoj1->setFocus();
        }

        if ( ! Ekzistas2 )
        {
            Referenca2 = LingvoListo.at(0).at(2);
            ui->lingvoj2->setCurrentIndex(0);
            ui->lingvoj2->setFocus();
        }
    }

    ui->Listo->blockSignals(true);
    ui->Listo->setCurrentIndex(Leciono);
    ui->Listo->blockSignals(false);

    QApplication::processEvents();

    aktualaSekcio = ui->Listo->currentText();

    SharghasTrad(ui->Listo->currentText());

    NunaPozicio = Pozicio;

    Movighas("");
}

void traduko::showEvent(QShowEvent * event)
{
    lokigas_paghotrad(ui->Listo->currentText());
    lokigas_frazotrad(linioj.at(NunaPozicio));
    Q_UNUSED(event)
}

void traduko::ListigasLingvojn()
{

    QDir dosierujo(Loko + "tradukoj/");
    dosierujo.setFilter(QDir::Files);

    QStringList filtroj;
    filtroj << "*.trd";

    dosierujo.setNameFilters(filtroj);

    QFileInfoList Dosieroj;

    Dosieroj = dosierujo.entryInfoList();
    QString DosierNomo;


    for (int i = 0; i < Dosieroj.size(); ++i)
    {
        QFileInfo fileInfo = Dosieroj.at(i);
        DosierNomo = fileInfo.fileName();

        QSettings Tradukado(Loko + "tradukoj/" + DosierNomo, QSettings::IniFormat);
        Tradukado.setIniCodec("UTF-8");

        Tradukado.beginGroup("Traduko");
        QStringList lingvo;
        lingvo << Tradukado.value("LingvoID", "??").toString();
        lingvo << Tradukado.value("Lingvo", "?????????").toString();
        lingvo << DosierNomo;
        LingvoListo.append(lingvo);
        ui->lingvoj1->addItem( lingvo.at(1));
        ui->lingvoj2->addItem( lingvo.at(1));
        Tradukado.endGroup();

    }

}

void traduko::SharghasTrad(QString Sekcio)
{
    QSettings Ref1(Loko + "tradukoj/" + Referenca1, QSettings::IniFormat);
    QSettings Ref2(Loko + "tradukoj/" + Referenca2, QSettings::IniFormat);
    QSettings Celo(Dosierujo + ui->Edit_dosiero->text(), QSettings::IniFormat);
    Ref1.setIniCodec("UTF-8");
    Ref2.setIniCodec("UTF-8");
    Celo.setIniCodec("UTF-8");

    Ref1.beginGroup(Sekcio);
    Ref2.beginGroup(Sekcio);
    Celo.beginGroup(Sekcio);

    if (Sekcio.left(3) == "Ekz")
    {
        QStringList chiuj = Ref1.childKeys();
        linioj.clear();
        for (int i=0; i < chiuj.size(); i++)
            linioj << QString::number(i);

    }
    else
        linioj = Ordigas(Sekcio);

    Ref1_itemoj.clear();
    Ref2_itemoj.clear();
    Celo_itemoj.clear();

    for (int i=0; i < linioj.size(); i++)
    {
        Ref1_itemoj << Ref1.value( linioj.at(i), "Ne tradukita.").toString();
        Ref2_itemoj << Ref2.value( linioj.at(i), "Ne tradukita.").toString();
        Celo_itemoj << Celo.value( linioj.at(i), "").toString();
    }

    Ref1.endGroup();
    Ref2.endGroup();
    Celo.endGroup();

    aktualaSekcio = Sekcio;

    lokigas_paghotrad(Sekcio);
}

void traduko::Movighas(QString Direkto)
{

    if (Direkto != "")
        Celo_itemoj.replace(NunaPozicio, ui->Memo1->toPlainText());

    if (Direkto == "posta"  && ( NunaPozicio < linioj.size()-1 ))
        NunaPozicio++;

    if (Direkto == "antaua"  && ( NunaPozicio > 0 ))
        NunaPozicio--;

    if (Direkto == "komenca")
        NunaPozicio = 0;

    if (Direkto == "fina")
        NunaPozicio = linioj.size() -1;

    ui->Memo1->setPlainText( Celo_itemoj.at(NunaPozicio) );
    ui->Memo2->setText(  Ref1_itemoj.at(NunaPozicio) );
    ui->Memo3->setText( Ref2_itemoj.at(NunaPozicio) );

    ui->Button5->setEnabled( NunaPozicio > 0);
    ui->Button1->setEnabled( NunaPozicio > 0);
    ui->Button6->setEnabled( NunaPozicio < linioj.size() - 1);
    ui->Button2->setEnabled( NunaPozicio < linioj.size() - 1);

    ui->pozicio->setText("Pozicio: " + QString::number(NunaPozicio+1) + " / " + QString::number(linioj.size()) + "        (" + linioj.at(NunaPozicio) + ")   "  );

    lokigas_frazotrad(linioj.at(NunaPozicio));

    ui->Memo1->setFocus();


}

void traduko::on_Button5_clicked()
{
    Movighas("komenca");
}

void traduko::on_Button1_clicked()
{
    Movighas("antaua");
}

void traduko::on_Button6_clicked()
{
    Movighas("fina");
}

void traduko::on_Button2_clicked()
{
    Movighas("posta");
}

bool traduko::SavasTrad()
{
    if (ui->Edit_dosiero->text().trimmed() == "" ||
        ui->Edit1->text().trimmed() == ""  ||
        ui->Edit2->text().trimmed() == ""  ||
        ui->dulitera_lingvokodo->text().trimmed() == "" ) {

        QMessageBox msgBox(QApplication::activeWindow());
        msgBox.setText(QString::fromUtf8("Bonvolu plenigi devigajn informojn (en la kampoj kun flava fono).") );
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return false;
    }

    Celo_itemoj.replace(NunaPozicio, ui->Memo1->toPlainText() );

    QSettings Celo(Dosierujo + ui->Edit_dosiero->text(), QSettings::IniFormat);
    Celo.setIniCodec("UTF-8");

    Celo.beginGroup("Traduko");

    Celo.setValue("LingvoID", ui->dulitera_lingvokodo->text());
    Celo.setValue("Lingvo", ui->Edit1->text());
    Celo.setValue("Tradukinto", ui->Edit2->text());
    Celo.setValue("LiterGrando", ui->literGrando->value());

    Celo.endGroup();

    Celo.beginGroup(aktualaSekcio);

    for (int i=0; i < linioj.size(); i++)
        if (Celo_itemoj.at(i) != "")
            Celo.setValue(linioj.at(i), Celo_itemoj.at(i));

    Celo.endGroup();

    Celo.sync();

    // kodo por enlistigi la tradukatan lingvon en la listo de elekteblaj lingvoj en la menuo "konfigurado"

    QFile dosiero(savasLoko + "traduklisto.ini");
    if (dosiero.exists() && ui->Edit_dosiero->text().trimmed() != "") {
        QSettings Tradukoj(dosiero.fileName(), QSettings::IniFormat);
        Tradukoj.setIniCodec("UTF-8");
        int listo_pozicio = -1;
        int i;
        for (i = 0; i < 200; ++i) {
            Tradukoj.beginGroup(QString::number(i));
            QStringList lingvo;
            lingvo << Tradukoj.value("LingvoID", "??").toString();
            lingvo << Tradukoj.value("Lingvo", "?????????").toString();
            lingvo << Tradukoj.value("DosierNomo", "?????????").toString();
            lingvo << Tradukoj.value("Dato", "?????????").toString();
            Tradukoj.endGroup();
            if (lingvo.at(0) == "??")
                break;

            if (lingvo.at(2) == ui->Edit_dosiero->text().trimmed()) {
                listo_pozicio = i;
                break;
            }
        }

        if (listo_pozicio > -1)  Tradukoj.beginGroup(QString::number(listo_pozicio));
        else Tradukoj.beginGroup(QString::number(i));
        Tradukoj.setValue("LingvoID", ui->dulitera_lingvokodo->text().trimmed());
        Tradukoj.setValue("Lingvo", ui->Edit1->text().trimmed());
        Tradukoj.setValue("DosierNomo", ui->Edit_dosiero->text().trimmed());
        Tradukoj.setValue("Dato", QDate::currentDate().toString("dd.MM.yyyy"));
        Tradukoj.endGroup();

    }

    return true;
}

void traduko::on_Listo_activated(const QString &arg1)
{
    if ( !SavasTrad() ) {
        ui->Listo->setCurrentText(aktualaSekcio);
        ui->scrollArea->ensureWidgetVisible(ui->Edit_dosiero);
        ui->Edit_dosiero->setFocus();
        return;
    }

    NunaPozicio = 0;

    SharghasTrad(arg1);

    QApplication::processEvents();

    Movighas("");

    lokigas_paghotrad(arg1);


}

void traduko::on_lingvoj1_activated(int index)
{

    Referenca1 = LingvoListo.at(index).at(2);

    QSettings Ref1(Loko + "tradukoj/" + Referenca1, QSettings::IniFormat);
    Ref1.setIniCodec("UTF-8");

    Ref1.beginGroup(ui->Listo->currentText());

    Ref1_itemoj.clear();

    for (int i=0; i < linioj.size(); i++)
    {
        Ref1_itemoj << Ref1.value( linioj.at(i), "Ne tradukita.").toString();
    }

    Ref1.endGroup();

    Movighas("");

}

void traduko::on_lingvoj2_activated(int index)
{
    Referenca2 = LingvoListo.at(index).at(2);

    QSettings Ref2(Loko + "tradukoj/" + Referenca2, QSettings::IniFormat);
    Ref2.setIniCodec("UTF-8");

    Ref2.beginGroup(ui->Listo->currentText());

    Ref2_itemoj.clear();

    for (int i=0; i < linioj.size(); i++)
    {
        Ref2_itemoj << Ref2.value( linioj.at(i), "Ne tradukita.").toString();
    }

    Ref2.endGroup();

    Movighas("");

}

void traduko::closeEvent(QCloseEvent *event)
{
    SavasTrad();
    QApplication::processEvents();

    QSettings Konfiguro(savasLoko + "kursokape.ini", QSettings::IniFormat);
    Konfiguro.setIniCodec("UTF-8");
    Konfiguro.beginGroup("Tradukilo");

    Konfiguro.setValue("Lingvo" , ui->Edit1->text());
    Konfiguro.setValue("LingvoID" , ui->dulitera_lingvokodo->text());
    Konfiguro.setValue("Dosiero", ui->Edit_dosiero->text());
    Konfiguro.setValue("Tradukinto", ui->Edit2->text());
    Konfiguro.setValue("LiterGrando", ui->literGrando->value());
    Konfiguro.setValue("Tiparo", ui->tiparo->currentText());
    Konfiguro.setValue("Referenca1", LingvoListo.at( ui->lingvoj1->currentIndex() ).at(2) );
    Konfiguro.setValue("Referenca2", LingvoListo.at( ui->lingvoj2->currentIndex() ).at(2) );
    Konfiguro.setValue("LastaLeciono", ui->Listo->currentIndex());
    Konfiguro.setValue("Pozicio", NunaPozicio);
    // Konfiguro.setValue("Dosierujo", Dosierujo);

    Konfiguro.endGroup();

    Konfiguro.sync();


    event->accept();

}

void traduko::on_Button4_clicked()
{
    bool trovita = false;

    Movighas("nenien");

    for (int i=0; i < linioj.size(); i++)
        if ( Celo_itemoj.at(i).trimmed() == "")
        {
            NunaPozicio = i;
            Movighas("");
            trovita = true;
            break;
        }

    if (!trovita)
    {
        QMessageBox msgBox(QApplication::activeWindow());
        msgBox.setText(QString::fromUtf8("En ĉi tiu sekcio, ĉiuj frazoj estas tradukitaj. \nBonvolu kontroli ankaŭ la aliajn sekciojn.") );
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }

}

QStringList traduko::Ordigas(QString Sekcio)
{
    QSettings listo(Loko + "tradukoj/tradukendaj.tdf", QSettings::IniFormat);

    listo.beginGroup(Sekcio);

    QStringList chiuj = listo.childKeys(), revena;

    int i;

    for (i=0; i < chiuj.size(); i++)
        revena << listo.value(chiuj.at(i), "Eraro").toString();

    listo.endGroup();

    return revena;
}

void traduko::lokigas_paghotrad(QString nova)
{
    QApplication::processEvents();

    if (nova.left(3) == "Lec")
        emit novapagho("Pagho" + nova.right(2));

    if (nova == "Konfig")
        emit novapagho("Pagho_Konfigurado");

    if (nova == "Menuo4")
        emit novapagho("Pagho_Kreditoj");

}

void traduko::lokigas_frazotrad(QString frazo)
{
    if (ui->Listo->currentText().left(3) == "Lec")
        emit novafrazo("Pagho" + ui->Listo->currentText().right(2), ui->Listo->currentText() + "_" + frazo);

    if (ui->Listo->currentText() == "Menuo4")
        emit novafrazo("Pagho_Kreditoj", "Kredit_" + frazo);

    if (ui->Listo->currentText() == "Konfig")
        emit novafrazo("Pagho_Konfigurado", "Konfig_" + frazo);
}



void traduko::on_Button7_clicked()
{
    QDesktopServices::openUrl(QUrl("http://kurso.com.br/datumoj/tradukoj/rekomendoj.html" , QUrl::TolerantMode));
}


void traduko::moveScrollBarToBottom(int min, int max)
{
    ui->scrollArea->verticalScrollBar()->setValue(max);
    Q_UNUSED(min)
}


void traduko::on_horizontalSlider_valueChanged(int value)
{
    ui->literGrando->setValue(value);
}

void traduko::on_pushButton_clicked()
{
    this->close();
}

void traduko::on_dosierujo_clicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile( savasLoko ));
}
