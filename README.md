# Kurso de Esperanto 5

Fontkodo de **Kurso de Esperanto**, senpaga plurmedia programo por lerni
Esperanton. La programo enhavas 13 lecionojn kun sonoj, bildoj, video kaj
interagaj ekzercoj, kaj estas tradukita al pli ol 30 lingvoj.

Ĝi estas verkita en C++ per [Qt 5](https://www.qt.io/) kaj funkcias en
Vindozo, macOS, Linukso kaj Androido.

## Strukturo de la deponejo

```
kursokape.pro     Qt-projekto (qmake)
src/              C++-fontkodo (.cpp, .h) kaj fenestroj (.ui)
resources/        Qt-rimedoj (.qrc): bildoj, stiloj, tradukoj, ekzercoj, QML
pkg_src/          Androida pakaĵo; pkg_src/assets/ enhavas la sonojn kaj videon
packaging/        Instalilaj skriptoj (Inno Setup por Vindozo, PAD-dosieroj)
tools/            Helpaj programoj (ekz. KONV_TRD por konverti tradukojn)
docs/             Notoj por programistoj
```

## Kompilado

### Postuloj

- Qt 5.15 (moduloj: `core`, `gui`, `widgets`, `network`, `multimedia`,
  `multimediawidgets`, `printsupport`; por Androido ankaŭ `quick` kaj
  `quickwidgets`)
- C++-kompililo (GCC, Clang aŭ MinGW)

La programo ankoraŭ **ne** kompiliĝas per Qt 6.

### Linukso (Debian / Ubuntu)

Instalu la dependaĵojn:

```sh
sudo apt install build-essential qtbase5-dev qt5-qmake \
    qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins
```

Kompilu ekster la fontdosierujo kaj lanĉu la programon:

```sh
mkdir build && cd build
qmake ../kursokape.pro
make -j"$(nproc)"
./kursokape
```

Post la kompilado, dosierujo `assets` (ligilo al `pkg_src/assets`) aperas
apud la programo, por ke ĝi trovu la sonojn kaj la videon.

Por ludi sonojn kaj videon, Qt uzas GStreamer. Se vi ne aŭdas sonon,
instalu ankaŭ `gstreamer1.0-plugins-good` kaj `gstreamer1.0-libav`.

### Vindozo kaj macOS

1. Instalu Qt 5.15 kaj Qt Creator per la
   [oficiala instalilo](https://www.qt.io/download-qt-installer).
2. Malfermu `kursokape.pro` en Qt Creator.
3. Elektu ilaron (*kit*) Qt 5.15 kaj alklaku *Build*.

En Vindozo, la sonoj kaj la video estu en la sama dosierujo kiel la
programo. En macOS, ili estu en `Contents/Resources/` de la pakaĵo `.app`.

### Androido

1. En Qt Creator, instalu Qt 5.15 por Androido kaj agordu la Android SDK
   kaj NDK (*Preferences → Devices → Android*).
2. Malfermu `kursokape.pro` kaj elektu Androidan ilaron.
3. La pakaĵo uzas la dosierojn de `pkg_src/` (manifesto, Gradle, sonoj).

Por subskribi eldonon, uzu vian propran ŝlosilon. Neniam aldonu
ŝlosilojn (`.keystore`, `.jks`) al la deponejo.

## Kontribui

Kontribuoj estas bonvenaj!

1. Forku la deponejon kaj kreu novan branĉon de `main`.
2. Faru viajn ŝanĝojn kaj kontrolu, ke la programo kompiliĝas.
3. Malfermu *pull request* kun klara priskribo de la ŝanĝoj.

Laŭ la reguloj de la projekto (vidu [`AGENTS.md`](AGENTS.md)), komentoj en
la kodo, mesaĝoj de *commit*, *pull requests* kaj *issues* estu verkitaj
**angle**. La nomoj de variabloj kaj funkcioj en la ekzistanta kodo estas
esperantaj; bonvolu sekvi la saman stilon.

Por raporti cimon aŭ proponi plibonigon, malfermu *issue* en GitHub.
