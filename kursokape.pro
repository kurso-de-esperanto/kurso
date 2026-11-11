#-------------------------------------------------
#
# Project created by QtCreator 2013-01-02T00:14:25
#
#-------------------------------------------------

QT       += core gui multimedia printsupport
QT      += widgets network

android { QT += quick quickwidgets }
else { QT += multimediawidgets }

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kursokape
TEMPLATE = app

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/pkg_src

SOURCES += src/main.cpp\
    src/flowlayout_nova.cpp \
    src/frazokonstruo.cpp \
    src/klakbutono_nova.cpp \
    src/korekta.cpp \
    src/korekta_butono.cpp \
    src/kurso.cpp \
    src/ekzerco1.cpp \
    src/funkcioj.cpp \
    src/label_klakebla.cpp \
    src/neklakebla_nova.cpp \
    src/plenigas_spacon.cpp \
    src/sendas_butono.cpp \
    src/sendujo.cpp \
    src/vortoludo.cpp \
    src/ekznumeraloj.cpp \
    src/audkompreno.cpp \
    src/akuzativo.cpp \
    src/mylabel.cpp \
    src/cx_plainedit.cpp \
    src/cx_edit.cpp \
    src/lingvoelekto.cpp \
    src/prononco.cpp \
    src/mp3ludilo.cpp \
    src/titolo.cpp \
    src/lec08.cpp \
    src/lec07.cpp \
    src/lec01.cpp \
    src/lec02.cpp \
    src/lec03.cpp \
    src/lec04.cpp \
    src/lec09.cpp \
    src/lec10.cpp \
    src/lec11.cpp \
    src/kiomahoro.cpp \
    src/lec13.cpp \
    src/lec12.cpp \
    src/lec05.cpp \
    src/lec06.cpp \
    src/label_sago.cpp \
    src/label_sago_reversa.cpp \
    src/traduko.cpp \
    src/filedownloader.cpp

HEADERS  += src/kurso.h \
    src/ekzerco1.h \
    src/flowlayout_nova.h \
    src/frazokonstruo.h \
    src/funkcioj.h \
    src/klakbutono_nova.h \
    src/korekta.h \
    src/korekta_butono.h \
    src/label_klakebla.h \
    src/neklakebla_nova.h \
    src/plenigas_spacon.h \
    src/sendas_butono.h \
    src/sendujo.h \
    src/vortoludo.h \
    src/ekznumeraloj.h \
    src/audkompreno.h \
    src/akuzativo.h \
    src/mylabel.h \
    src/cx_plainedit.h \
    src/cx_edit.h \
    src/lingvoelekto.h \
    src/prononco.h \
    src/mp3ludilo.h \
    src/titolo.h \
    src/lec08.h \
    src/lec07.h \
    src/lec01.h \
    src/lec02.h \
    src/lec03.h \
    src/lec04.h \
    src/lec09.h \
    src/lec10.h \
    src/lec11.h \
    src/kiomahoro.h \
    src/lec13.h \
    src/lec12.h \
    src/lec05.h \
    src/lec06.h \
    src/label_sago.h \
    src/label_sago_reversa.h \
    src/traduko.h \
    src/filedownloader.h

FORMS    += src/kurso.ui \
    src/ekzerco1.ui \
    src/frazokonstruo.ui \
    src/plenigas_spacon.ui \
    src/sendujo.ui \
    src/ekznumeraloj.ui \
    src/audkompreno.ui \
    src/akuzativo.ui \
    src/lingvoelekto.ui \
    src/prononco.ui \
    src/mp3ludilo.ui \
    src/lec08.ui \
    src/lec07.ui \
    src/lec01.ui \
    src/lec02.ui \
    src/lec03.ui \
    src/lec04.ui \
    src/lec09.ui \
    src/lec10.ui \
    src/lec11.ui \
    src/kiomahoro.ui \
    src/lec13.ui \
    src/lec12.ui \
    src/lec05.ui \
    src/lec06.ui \
    src/vortoludo.ui \
    src/traduko.ui

RESOURCES += \
    resources/ikonoj_androjdo.qrc \
    resources/stiloj.qrc \
    resources/ekzercoj.qrc \
    resources/ikonoj.qrc \
    resources/tradukoj.qrc

android {
    RESOURCES += resources/qml.qrc
}
else {
    SOURCES += src/videoludilo.cpp
    HEADERS += src/videoludilo.h
    FORMS += src/videoludilo.ui
}


RC_FILE = resources/ikono.rc

DISTFILES += \
    pkg_src/AndroidManifest.xml \
    pkg_src/build.gradle \
    pkg_src/gradle/wrapper/gradle-wrapper.jar \
    pkg_src/gradle/wrapper/gradle-wrapper.properties \
    pkg_src/gradlew \
    pkg_src/gradlew.bat \
    pkg_src/res/values/libs.xml
