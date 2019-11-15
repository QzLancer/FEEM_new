DEFINES += OUTPUTPLUGIN_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)

SOURCES += \
    outputpluginplugin.cpp \
    messagemanager.cpp \
    messageoutputwindow.cpp \
    outputpanemanager.cpp \
    outputwindow.cpp \
    messageoutputpane.cpp

HEADERS += \
    outputpluginplugin.h \
    outputplugin_global.h \
    outputpluginconstants.h \
    ioutputpane.h \
    messagemanager.h \
    messageoutputwindow.h \
    outputpanemanager.h \
    outputwindow.h \
    messageoutputpane.h

RESOURCES += \
    res.qrc
