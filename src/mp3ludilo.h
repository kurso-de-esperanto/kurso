#ifndef MP3LUDILO_H
#define MP3LUDILO_H

#include <QFrame>
//#include <phonon/mediaobject.h>
#include <QtMultimedia/QMediaPlayer>


namespace Ui {
    class mp3ludilo;
}

class mp3ludilo : public QFrame
{
    Q_OBJECT

public:
    explicit mp3ludilo(QWidget *parent = nullptr);
    ~mp3ludilo();

private slots:
    void on_Ludu_clicked();
    void on_Chesu_clicked();
    void on_Pauzu_clicked();
    void PaghoShanghita(int);
    void PaghoFragoj(int);
    void finite();

private:
    Ui::mp3ludilo *ui;
//    Phonon::MediaObject *ludilo;
    QMediaPlayer *ludilo;
    int MiaPagho;

};

#endif // MP3LUDILO_H
