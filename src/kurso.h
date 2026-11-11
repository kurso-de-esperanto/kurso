#ifndef KURSO_H
#define KURSO_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include <traduko.h>
#include <QLabel>
#include <filedownloader.h>
#include <bildoludo.h>

namespace Ui {
    class kurso;
}

class kurso : public QMainWindow
{
    Q_OBJECT

public:
    explicit kurso(QWidget *parent = nullptr);
    ~kurso();
    QMediaPlayer *ludilo;

public slots:
    void Saluton();
    void montras_koverton(bool, int);

private slots:

    void Centrigas_Fenestron();
    void Ghustigas_fenestron();
    void ReGrandigas_Fenestron();
    void Traduku();
    void ListigasLingvojn();
    void Konfiguru();
    void komencakonfiguro();
    void aktualigasTradukon();
    void SavasKonfig();
    void SavasKonfig2(Qt::ApplicationState state);
    void Stilo();
    void Fenestra_Stilo();
    void Malgrandigas();
    void ShanghasTiparon();
    void ShanghasTiparStilon();

//    void closeEvent(QCloseEvent *event);
    void showEvent ( QShowEvent * event ) ;

    void on_Hejmo_clicked();

    void on_Sendas_clicked();

    void on_printilo_clicked();

    void on_Cxapeligo_toggled(bool checked);

    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_3_clicked(bool checked);

    void on_Lingvo_activated(int index);

    void on_KieButono_clicked();

    void on_Tiparo_currentIndexChanged(const QString &arg1);

    void lokigas_paghotrad(QString novapagho);

    void lokigas_frazotrad(QString novapagho, QString novafrazo);


    /* CHI TIU PARTO ENIROS EN ESTONTA VERSIO
    void on_BildoLudo_clicked();
    */

    void on_Konfigurado_clicked();

    void on_KioEstas_clicked();

    void on_KielUzi_clicked();

    void on_Kreditoj_clicked();

    void on_Parolo_toggled(bool checked);

    void on_Noteto_toggled(bool checked);

    void on_LiterGrando_valueChanged(int arg1);


    void ShanghasPaghon(QString Nomo, QFrame * lecionujo);

    void on_Leciono1_clicked();
    void on_Leciono2_clicked();
    void on_Leciono3_clicked();
    void on_Leciono4_clicked();
    void on_Leciono5_clicked();
    void on_Leciono6_clicked();
    void on_Leciono7_clicked();
    void on_Leciono8_clicked();
    void on_Leciono9_clicked();
    void on_Leciono10_clicked();
    void on_Leciono11_clicked();
    void on_Leciono12_clicked();
    void on_Leciono13_clicked();


    // void on_checkBox_clicked(bool checked);


    //void on_butono_listo_clicked();

    void on_TiparoEo_currentIndexChanged(const QString &arg1);

    void on_LiterGrandoEo_valueChanged(int arg1);

    void listigas_trad();

    void on_shanghasKonfigurojn_clicked();

    void shanghitajKonfiguroj();

    void on_dekstren_clicked();

    void on_maldekstren_clicked();

    void komencas_navigujon();

    void on_butono_androjdo_clicked();


    void on_tradukilo_clicked();

    void on_glitilo_eo_valueChanged(int value);

    void on_glitilo_traduko_valueChanged(int value);

    void on_Eliri_clicked();

    void on_label_Kie_clicked();

    void on_label_Kreditoj_clicked();

    void on_label_Kio_clicked();

    void on_label_Konfiguroj_clicked();

    void on_label_Kiel_clicked();

    void on_label_Eliri_clicked();

private:
    Ui::kurso *ui;

    traduko *tradukilo;

    QList<QStringList> LingvoListo;
    QStringList TradukitajLecionoj;


    FileDownloader *elshutilo ;


    int alteco_originala, largheco_originala, alteco_maksimuma, largheco_maksimuma;
    bool Eta_Fenestro, Malalta_Fenestro, JamMontrita;

    QLabel * antaua;
    QFrame * frame_lec01 = nullptr;
    QFrame * frame_lec02 = nullptr;
    QFrame * frame_lec03 = nullptr;
    QFrame * frame_lec04 = nullptr;
    QFrame * frame_lec05 = nullptr;
    QFrame * frame_lec06 = nullptr;
    QFrame * frame_lec07 = nullptr;
    QFrame * frame_lec08 = nullptr;
    QFrame * frame_lec09 = nullptr;
    QFrame * frame_lec10 = nullptr;
    QFrame * frame_lec11 = nullptr;
    QFrame * frame_lec12 = nullptr;
    QFrame * frame_lec13 = nullptr;

    QFrame * frame_bildoludo = nullptr;



};

#endif // KURSO_H
