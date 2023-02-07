#!/bin/bash
rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
make -j4
make install DESTDIR=AppDir
cp idlconverter AppDir/usr/bin
cp ../linuxdeploy-* .
chmod +x linuxdeploy-*
PATH=/usr/local/Qt6:$PATH;QMAKE=/usr/local/Qt6/bin/qmake ./linuxdeploy-x86_64.AppImage \
--appdir AppDir --plugin qt --output appimage
rm -rf AppDir/apprun-hooks AppDir/usr/share AppDir/usr/translations
mv AppDir/usr AppDir/idlConverter
cd AppDir/idlConverter/lib
rm `ls *|\
grep -v libQt6Core.so.6 |\
grep -v libQt6Gui.so.6 |\
grep -v libQt6XcbQpa.so.6 |\
grep -v libQt6Widgets.so.6 |\
grep -v libQt6DBus.so.6`

