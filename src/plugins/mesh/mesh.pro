DEFINES += MESH_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)


msvc: QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250

HEADERS += \
    meshconstants.h \
    mesh_global.h \
    meshplugin.h

SOURCES += \
    meshplugin.cpp
