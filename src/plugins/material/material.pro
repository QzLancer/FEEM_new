DEFINES += MATERIAL_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)


msvc: QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250

  

HEADERS += \
    material_global.h \
    materialconstants.h \
    materialplugin.h

SOURCES += \
    materialplugin.cpp

RESOURCES += \
    material.qrc

