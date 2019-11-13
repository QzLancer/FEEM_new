DEFINES += MAGPLUGIN_LIBRARY

include(../../feemplugin.pri)

HEADERS += \
    magfemprojectmanagerplugin_global.h \
    magfemprojectmanagerpluginconstants.h \
    magfemprojectmanagerpluginplugin.h \
    magfieldwizard.h \
    magfield2dtransientwizard.h \
    magfield3dstaticwizard.h \
    magfield3dtransintwizard.h

SOURCES += \
    magfemprojectmanagerpluginplugin.cpp \
    magfieldwizard.cpp \
    magfield2dtransientwizard.cpp \
    magfield3dstaticwizard.cpp \
    magfield3dtransintwizard.cpp
