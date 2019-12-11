DEFINES += MESH_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)

HEADERS += \
    meshconstants.h \
    mesh_global.h \
    meshplugin.h \
    meshfemm.h

SOURCES += \
    meshplugin.cpp

RESOURCES += \
    res.qrc
