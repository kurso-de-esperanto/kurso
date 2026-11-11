#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QString>
#include <QFile>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_4_clicked()
{
    QDir myDir("R:/tradukoj");
    QStringList filters;
    filters << "*.trd";
    myDir.setNameFilters(filters);
    QStringList lista = myDir.entryList();
    ui->listWidget_3->addItems(lista);
}

void MainWindow::on_pushButton_5_clicked()
{
    QString linha, texto, grupo, chave;
    for (int arquivos=0; (arquivos < ui->listWidget_3->count() ); arquivos++) {
        ui->listWidget->clear();
        QFile file("R:/tradukoj/" + ui->listWidget_3->item(arquivos)->text());
        if (file.open(QFile::ReadOnly)) {
            char buf[1024];
            do {
                qint64 lineLength = file.readLine(buf, sizeof(buf));
                if (lineLength > 0){
                    if (buf[lineLength-1] == 10) {
                        buf[lineLength-1] = char(0);
                        buf[lineLength-2] = char(0);
                    }

                    ui->listWidget->addItem(QString::fromUtf8(buf));
                }
            } while (!file.atEnd());
        }
        /*
        linha = ui->listWidget->item(0)->text();
        if (linha.mid(0,1) == "[") {
            grupo = linha.mid(1, linha.indexOf("]")-1);
        }
        */
        QString nome_arq ("R:/tradukoj_qt/" + ui->listWidget_3->item(arquivos)->text());
        QSettings traduko(nome_arq, QSettings::IniFormat);
        traduko.setIniCodec("UTF-8");
        int i;
        bool novogrupo = false;
        int qitens = ui->listWidget->count();

        for (i=0; (i < qitens) ; i++) {
            linha = ui->listWidget->item(i)->text().trimmed();
            if (linha.left(1) == "[") {
                if (novogrupo) {
                    traduko.endGroup();
                }
                grupo = linha.mid(1, linha.indexOf("]")-1);

                if (grupo.left(10) == "Ekzerco-11")
                    grupo.replace( "Ekzerco-11",  "Ekzerco-12");

                if (grupo.left(10) == "Ekzerco-10")
                    grupo.replace( "Ekzerco-10",  "Ekzerco-11");

                if (grupo.left(10) == "Ekzerco-09")
                    grupo.replace( "Ekzerco-09",  "Ekzerco-10");

                if (grupo.left(10) == "Ekzerco-08")
                    grupo.replace( "Ekzerco-08",  "Ekzerco-09");

                if (grupo.left(10) == "Ekzerco-07")
                    grupo.replace( "Ekzerco-07",  "Ekzerco-08");

                if (grupo.left(10) == "Ekzerco-06")
                    grupo.replace( "Ekzerco-06",  "Ekzerco-07");

                if (grupo.left(10) == "Ekzerco-5A")
                    grupo.replace( "Ekzerco-5A",  "Ekzerco-06");

                if (grupo == "Lec12")
                    grupo =  "Lec13";

                if (grupo == "Lec11")
                    grupo =  "Lec12";

                if (grupo == "Lec10")
                    grupo =  "Lec11";

                if (grupo == "Lec09")
                    grupo =  "Lec10";

                if (grupo == "Lec08")
                    grupo = "Lec09";

                if (grupo == "Lec07")
                    grupo =  "Lec08";

                if (grupo == "Lec06")
                    grupo =  "Lec07";

                if (grupo == "Lec05A")
                    grupo = "Lec06";





                traduko.beginGroup(grupo);
                novogrupo = true;
            }
            else {
                if ( linha != "") 
                {
                    chave = linha.mid(0,linha.indexOf("="));
                    if (chave == "Tiparo" || chave == "Kodaro")
                        chave = "";

                    texto = linha.mid(linha.indexOf("=")+1);
                    texto.replace("'#10'", "\n");
                    texto.replace("'#'10'", "\n");

                    if (chave == "KioDosiero" || chave == "KielDosiero")
                        texto.replace(".rtf", ".htm");
                    if (chave == "LingvoID")
                        texto = texto.left(2).toLower();
                    if (chave != "" && valida(chave))
                        traduko.setValue(chave, texto);
                }
            }

        }
        traduko.endGroup();
        traduko.sync();

    }
}

bool MainWindow::valida(QString teksto)
{
    int i;
    char  litero;
    for (i = 0; i < teksto.size(); i++)
    {
        litero = teksto.at(i).toAscii();
        if ( !( QChar(litero).isLetterOrNumber() || teksto.mid(i,1) == "_") )
            return false;
    }
    return true;
}
