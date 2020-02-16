DEFINES += MESH_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)

HEADERS += \
    meshconstants.h \
    mesh_global.h \
    meshplugin.h \
    meshfemm.h \
    pf_meshnode.h

SOURCES += \
    meshplugin.cpp \
    meshfemm.cpp \
    pf_meshnode.cpp

RESOURCES += \
    res.qrc
