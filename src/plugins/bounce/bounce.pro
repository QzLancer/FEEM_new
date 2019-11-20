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
    bouncetab.h \
    bouncestack.h \
    subwidget/inputwidget.h \
    subwidget/solverwidget.h \
    subwidget/paramwidget.h

SOURCES += \
    bounceplugin.cpp \
    bouncecore.cpp \
    bouncedialog.cpp \
    bouncetab.cpp \
    bouncestack.cpp \
    subwidget/inputwidget.cpp \
    subwidget/solverwidget.cpp \
    subwidget/paramwidget.cpp

RESOURCES += \
    bounce.qrc

QT += axcontainer

