# Xpam installer

## Build static StormLib
```
git clone git@github.com:ladislav-zezula/StormLib.git
cd StormLib
"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvarsall.bat" amd64
cmake -B ./build_static -DBUILD_SHARED_LIBS=OFF -DUNICODE=ON
cd build_static
cmake --build . --config Release
```

## Build static Qt

First install python.

We need static Qt so we can ship a single binary as installer. Unfortunately Visual Redistributable x64 2022 is still needed first, we will try to fix that.

```
git clone git://code.qt.io/qt/qt5.git qt6
cd qt6
git checkout v6.5.3
perl init-repository
mkdir qt6-build
"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvarsall.bat" amd64
cd qt6-build
..\configure.bat -opensource -nomake examples -nomake tests -opengl desktop -static -static-runtime -debug-and-release -platform win32-msvc -qt-zlib -no-sql-sqlite -no-sql-mysql -no-sql-psql -skip qtwebengine -skip qt3d -skip qtactiveqt -skip qtcanvas3d -skip qtcharts -skip qtcoap -skip qtconnectivity -skip qtdatavis3d -skip qtdeclarative -skip qtdoc -skip qtfeedback -skip qtgamepad -skip qtgrpc -skip qthttpserver -skip qtlanguageserver -skip qtlocation -skip qtlottie -skip qtmultimedia -skip qtnetworkauth -skip qtlottie -skip qtopcua -skip qtpim -skip qtqa -skip qtquick3d -skip qtquick3dphysics -skip qtremoteobjects -skip qtquicktimeline -skip qtquickeffectmaker -skip qtrepotools -skip qtscxml -skip qtsensors -skip qtserialport -skip qtspeech -skip qtwebsockets -skip qttranslations -skip qtvirtualkeyboard -skip qtscxml -skip qtsensors -skip qtserialbus -skip qtwebview -skip qtxmlpatterns -skip qtwebglplugin -skip qtwebchannel -skip qtmqtt -prefix C:/Qt/Qt-6.5.3-static
cmake --build . --parallel
cmake --install . --config Debug
cmake --install . --config Release 
```