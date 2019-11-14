DEFINES += MAGPLUGIN_LIBRARY

include(../../feemplugin.pri)

HEADERS += \
    magfemprojectmanagerplugin_global.h \
    magfemprojectmanagerpluginconstants.h \
    magfemprojectmanagerpluginplugin.h \
    magfieldwizard.h \
    magfield2dtransientwizard.h \
    magfield3dstaticwizard.h \
    magfield3dtransintwizard.h \
    pf_mag2dsproject.h

SOURCES += \
    magfemprojectmanagerpluginplugin.cpp \
    magfieldwizard.cpp \
    magfield2dtransientwizard.cpp \
    magfield3dstaticwizard.cpp \
    magfield3dtransintwizard.cpp \
    pf_mag2dsproject.cpp

RESOURCES += \
    res.qrc
