DEFINES += BOUNCE_LIBRARY

QT += \
    printsupport \

include(../../feemplugin.pri)

HEADERS += \
    bounce_global.h \
    bounceconstants.h \
    bounceplugin.h \
    bouncecore.h \
    bouncedialog.h \
    bouncetab.h

SOURCES += \
    bounceplugin.cpp \
    bouncecore.cpp \
    bouncedialog.cpp \
    bouncetab.cpp

RESOURCES += \
    bounce.qrc

QT += axcontainer

