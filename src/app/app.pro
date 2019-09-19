include(../../feem.pri)

#include($$PWD/../libs/qtribbon/ribbonsample/qtitanribbon.pri)
#include($$PWD/../libs/qtribbon/ribbonsample/shared/aboutdialog.pri)
#include($$PWD/../libs/qtribbon/ribbonsample/shared/ribbonwindow.pri)

TEMPLATE = app
TARGET = $$IDE_APP_TARGET
DESTDIR = $$IDE_APP_PATH
VERSION = $$FEEM_VERSION

SOURCES += main.cpp

LIBS *= -l$$feemLibraryName(ExtensionSystem) -l$$feemLibraryName(QtRibbon) -l$$feemLibraryName(Utils)

win32 {
    RC_FILE = icon.rc
} else:macx {

}

target.path = $$INSTALL_APP_PATH
INSTALLS += target

DISTFILES += icon.rc \


