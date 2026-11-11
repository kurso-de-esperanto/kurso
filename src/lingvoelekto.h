#ifndef LINGVOELEKTO_H
#define LINGVOELEKTO_H

#include <QDialog>
#include <QtCore>
#include <filedownloader.h>

namespace Ui {
    class lingvoelekto;
}

class lingvoelekto : public QDialog
{
    Q_OBJECT

public:
    explicit lingvoelekto(QWidget *parent = nullptr);
    ~lingvoelekto();

private slots:
    void komencasElDosierujo();

    void elshutas();

    void elektasTradukFonton();

    void on_pushButton_clicked();

    void fermasFenestron();

    void closeEvent(QCloseEvent *event);

    void showEvent ( QShowEvent * event ) ;


private:
    Ui::lingvoelekto *ui;

    QList<QStringList> LingvoListo, ElshutoListo;
    bool ElshutoSukcesa = false;

    FileDownloader *elshutilo ;

    //QList<QString> LingvoNomoj;
    //QList<QString> LingvoDosieroj;
};

#endif // LINGVOELEKTO_H
