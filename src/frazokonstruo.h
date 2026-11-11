#ifndef FRAZOKONSTRUO_H
#define FRAZOKONSTRUO_H

#include <QFrame>
#include <QPushButton>
#include <QTimer>

namespace Ui {
    class frazokonstruo;
}

class frazokonstruo : public QFrame
{
    Q_OBJECT

public:
    explicit frazokonstruo(QWidget *parent = nullptr);
    ~frazokonstruo();

public slots:
    void vortoklako();
    void vortoforigo();

private slots:
    void on_BitBtn1_clicked();
    void novafrazo();

    void tekstoblinko();

    void on_BitBtn3_clicked();

    void on_BitBtn2_clicked();


    void on_Antauen_clicked();

private:
    Ui::frazokonstruo *ui;

    int iAleat2, iKorektaj, iEraraj;

    QStringList aEk02D;
    QList<QStringList> aEk02R;
    QStringList aEk02K;
    QList<bool> aEk02A;
    QStringList aEk02T;
    QStringList Klarigoj;

    QStringList vortoj;

    QString sVorto, sTraduko;

    QString aFrazoElek[11];
    int     iEk02D;
    QList<QPushButton *> chiuj_vortoj;
    QList<QPushButton *> chiuj_disponeblaj;
    QWidget * ujo;

    bool Atendu;
};

#endif // FRAZOKONSTRUO_H
