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

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/pkg_src

SOURCES += main.cpp\
    flowlayout_nova.cpp \
    frazokonstruo.cpp \
    klakbutono_nova.cpp \
    korekta.cpp \
    korekta_butono.cpp \
    kurso.cpp \
    ekzerco1.cpp \
    funkcioj.cpp \
    label_klakebla.cpp \
    neklakebla_nova.cpp \
    plenigas_spacon.cpp \
    sendas_butono.cpp \
    sendujo.cpp \
    vortoludo.cpp \
    ekznumeraloj.cpp \
    audkompreno.cpp \
    akuzativo.cpp \
    mylabel.cpp \
    cx_plainedit.cpp \
    cx_edit.cpp \
    lingvoelekto.cpp \
    prononco.cpp \
    mp3ludilo.cpp \
    titolo.cpp \
    lec08.cpp \
    lec07.cpp \
    lec01.cpp \
    lec02.cpp \
    lec03.cpp \
    lec04.cpp \
    lec09.cpp \
    lec10.cpp \
    lec11.cpp \
    kiomahoro.cpp \
    lec13.cpp \
    lec12.cpp \
    lec05.cpp \
    lec06.cpp \
    label_sago.cpp \
    label_sago_reversa.cpp \
    traduko.cpp \
    filedownloader.cpp

HEADERS  += kurso.h \
    ekzerco1.h \
    flowlayout_nova.h \
    frazokonstruo.h \
    funkcioj.h \
    klakbutono_nova.h \
    korekta.h \
    korekta_butono.h \
    label_klakebla.h \
    neklakebla_nova.h \
    plenigas_spacon.h \
    sendas_butono.h \
    sendujo.h \
    vortoludo.h \
    ekznumeraloj.h \
    audkompreno.h \
    akuzativo.h \
    mylabel.h \
    cx_plainedit.h \
    cx_edit.h \
    lingvoelekto.h \
    prononco.h \
    mp3ludilo.h \
    titolo.h \
    lec08.h \
    lec07.h \
    lec01.h \
    lec02.h \
    lec03.h \
    lec04.h \
    lec09.h \
    lec10.h \
    lec11.h \
    kiomahoro.h \
    lec13.h \
    lec12.h \
    lec05.h \
    lec06.h \
    label_sago.h \
    label_sago_reversa.h \
    traduko.h \
    filedownloader.h

FORMS    += kurso.ui \
    ekzerco1.ui \
    frazokonstruo.ui \
    plenigas_spacon.ui \
    sendujo.ui \
    ekznumeraloj.ui \
    audkompreno.ui \
    akuzativo.ui \
    lingvoelekto.ui \
    prononco.ui \
    mp3ludilo.ui \
    lec08.ui \
    lec07.ui \
    lec01.ui \
    lec02.ui \
    lec03.ui \
    lec04.ui \
    lec09.ui \
    lec10.ui \
    lec11.ui \
    kiomahoro.ui \
    lec13.ui \
    lec12.ui \
    lec05.ui \
    lec06.ui \
    vortoludo.ui \
    traduko.ui

RESOURCES += \
    ikonoj_androjdo.qrc \
    stiloj.qrc \
    ekzercoj.qrc \
    ikonoj.qrc \
    tradukoj.qrc

android {
    RESOURCES += qml.qrc
}
else {
    SOURCES += videoludilo.cpp
    HEADERS += videoludilo.h
    FORMS += videoludilo.ui
}


# Desktop Linux: the program looks for its media files (sounds, videos) in an
# "assets" directory next to the executable. Link it to the bundled assets so
# the program can be run straight from the build directory.
unix:!android:!macx {
    QMAKE_POST_LINK += ln -sfn $$shell_quote($$PWD/pkg_src/assets) $$shell_quote($$OUT_PWD/assets)
}

RC_FILE = ikono.rc

DISTFILES += \
    pkg_src/AndroidManifest.xml \
    pkg_src/build.gradle \
    pkg_src/gradle/wrapper/gradle-wrapper.jar \
    pkg_src/gradle/wrapper/gradle-wrapper.properties \
    pkg_src/gradlew \
    pkg_src/gradlew.bat \
    pkg_src/res/values/libs.xml
