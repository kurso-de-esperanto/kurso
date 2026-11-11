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

#include "cx_plainedit.h"
#include <QPlainTextEdit>


cx_plainedit::cx_plainedit(QWidget *parent) :
    QPlainTextEdit(parent)
{
    this->setInputMethodHints(Qt::ImhSensitiveData | Qt::ImhPreferLatin | Qt::ImhMultiLine);
}


void cx_plainedit::keyPressEvent(QKeyEvent *event)
{
#ifdef Q_OS_ANDROID
    if (lCxapeligo) {
        if (event->key() == Qt::Key_Backspace){
            //qDebug() << "klavo: " + QString::number(event->key());
            QTextCursor  cursor = this->textCursor();
            QString teksto = this->toPlainText();
            this->setPlainText(teksto.left(teksto.size() - 1));
            cursor.movePosition(QTextCursor::End);
            this->setTextCursor( cursor );
        }
        else if (event->key() == Qt::Key_Return){
            //qDebug() << this->toPlainText();
            //qDebug() << "Premita klavo: " + QString::number(event->key());
            this->setPlainText(cxteksto(this->toPlainText())+ event->text());
            QTextCursor  cursor = this->textCursor();
            cursor.movePosition(QTextCursor::End);
            this->setTextCursor( cursor );
        }
        else QPlainTextEdit::keyPressEvent(event);
    }
    else  { //qDebug() << "Ne chapelo: " + QString::number(event->key());
        QPlainTextEdit::keyPressEvent(event);}
#else
    if ( (event->key() == Qt::Key_X) && (lCxapeligo))
    {
        int arg1 = this->textCursor().position()-1;
        QChar antaualitero = this->document()->characterAt(arg1);

        //int arg1 = this->cursorPosition()-1;
        //QByteArray antaualitero = (this->text().mid(arg1,1)).toAscii();
        QString novalitero;
        switch (antaualitero.toLatin1()) {
        case 'c':
            novalitero = QString::fromUtf8("ĉ");
            break;
        case 'C':
            novalitero = QString::fromUtf8("Ĉ");
            break;
        case 'g':
            novalitero = QString::fromUtf8("ĝ");
            break;
        case 'G':
            novalitero = QString::fromUtf8("Ĝ");
            break;
        case 'h':
            novalitero = QString::fromUtf8("ĥ");
            break;
        case 'H':
            novalitero = QString::fromUtf8("Ĥ");
            break;
        case 'j':
            novalitero = QString::fromUtf8("ĵ");
            break;
        case 'J':
            novalitero = QString::fromUtf8("Ĵ");
            break;
        case 's':
            novalitero = QString::fromUtf8("ŝ");
            break;
        case 'S':
            novalitero = QString::fromUtf8("Ŝ");
            break;
        case 'u':
            novalitero = QString::fromUtf8("ŭ");
            break;
        case 'U':
            novalitero = QString::fromUtf8("Ŭ");
            break;
        default:
            novalitero = "";

        }
        if (novalitero != ""){
            this->textCursor().deletePreviousChar();
            //this->textCursor().deletePreviousChar();
            this->textCursor().insertText(novalitero);

        }
        else
            QPlainTextEdit::keyPressEvent(event);


    }
    else
        QPlainTextEdit::keyPressEvent(event);
#endif
}

QString cx_plainedit::cxteksto(QString teksto)
{
    // c kun cxapelo
    teksto.replace("Cx",  QString::fromUtf8("Ĉ"));
    teksto.replace("CX",  QString::fromUtf8("Ĉ"));
    teksto.replace("cx",  QString::fromUtf8("ĉ"));
    teksto.replace("cX",  QString::fromUtf8("ĉ"));
    // g kun cxapelo
    teksto.replace("Gx",  QString::fromUtf8("Ĝ"));
    teksto.replace("GX",  QString::fromUtf8("Ĝ"));
    teksto.replace("gx",  QString::fromUtf8("ĝ"));
    teksto.replace("gX",  QString::fromUtf8("ĝ"));
    // h kun cxapelo
    teksto.replace("Hx",  QString::fromUtf8("Ĥ"));
    teksto.replace("HX",  QString::fromUtf8("Ĥ"));
    teksto.replace("hx",  QString::fromUtf8("ĥ"));
    teksto.replace("hX",  QString::fromUtf8("ĥ"));
    // j kun cxapelo
    teksto.replace("Jx",  QString::fromUtf8("Ĵ"));
    teksto.replace("JX",  QString::fromUtf8("Ĵ"));
    teksto.replace("jx",  QString::fromUtf8("ĵ"));
    teksto.replace("jX",  QString::fromUtf8("ĵ"));
    // s kun cxapelo
    teksto.replace("Sx",  QString::fromUtf8("Ŝ"));
    teksto.replace("SX",  QString::fromUtf8("Ŝ"));
    teksto.replace("sx",  QString::fromUtf8("ŝ"));
    teksto.replace("SX",  QString::fromUtf8("ŝ"));
    // u kun brakio
    teksto.replace("Ux",  QString::fromUtf8("Ŭ"));
    teksto.replace("UX",  QString::fromUtf8("Ŭ"));
    teksto.replace("ux",  QString::fromUtf8("ŭ"));
    teksto.replace("uX",  QString::fromUtf8("ŭ"));

    //qDebug() << "El la funkcio: " + teksto;

    return(teksto);
}
