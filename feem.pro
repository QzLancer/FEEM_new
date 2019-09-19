include(feem.pri)

#version check qt
!minQtVersion(5, 0, 0) {
    message("Cannot build $$IDE_DISPLAY_NAME with Qt version $${QT_VERSION}.")
    error("Use at least Qt 5.0.0.")
}

TEMPLATE = subdirs
CONFIG   += ordered

SUBDIRS += src

TRANSLATIONS = $$PWD/feem/res/translations/feem_en.ts \
                $$PWD/feem/res/translations/feem_zh.ts \

