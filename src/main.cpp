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

#include <QtCore>
#include <QFontDatabase>
#include <QApplication>
#include "kurso.h"
#include "funkcioj.h"
#include "traduko.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    a.setApplicationName("KursoKape");
    a.setApplicationVersion("5.0 kape");
    a.setApplicationDisplayName("Kurso de Esperanto Kape");
    a.setOrganizationName("Kurso de Esperanto");
    a.setOrganizationDomain("kurso.com.br");

    sSistemo = QSysInfo::productType();

    mrLoko = kiuSistemo("multrimedoj");
    savasLoko = kiuSistemo("skribebla");

    Loko = ":/";

    QScreen * screen = a.primaryScreen();
    qDebug() << "devicePixelRatio = " + QString::number(screen->devicePixelRatio());
    qDebug() << "logicalDotsPerInch = " + QString::number(screen->logicalDotsPerInch());

    qDebug() << "Sistema tiparo: " + a.font().family();
    qDebug() << "Sistema litergrando (px): " + QString::number(a.font().pixelSize());
    qDebug() << "Sistema litergrando (pt): " + QString::number(a.font().pointSize());


    kurso w;

    w.show();

    w.Saluton();

    QObject::connect(&a, SIGNAL(aboutToQuit()), &w, SLOT( SavasKonfig() ));
    QObject::connect(QCoreApplication::instance(), SIGNAL(applicationStateChanged(Qt::ApplicationState)), &w, SLOT( SavasKonfig2(Qt::ApplicationState) ));

    return a.exec();
}
