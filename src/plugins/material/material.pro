DEFINES += MATERIAL_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)  

HEADERS += \
    material_global.h \
    materialconstants.h \
    materialplugin.h

SOURCES += \
    materialplugin.cpp

RESOURCES += \
    material.qrc

