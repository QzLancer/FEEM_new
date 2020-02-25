DEFINES += MAGPLUGIN_LIBRARY

include(../../feemplugin.pri)

HEADERS += \
    magfieldwizard.h \
    magfield2dtransientwizard.h \
    magfield3dstaticwizard.h \
    magfield3dtransintwizard.h \
    pf_mag2dsproject.h \
    pf_magfemnode.h \
    pf_magfemfile.h \
    sparsefemm.h \
    magfemplugin.h \
    magfemplugin_global.h \
    magfempluginconstants.h

SOURCES += \
    magfieldwizard.cpp \
    magfield2dtransientwizard.cpp \
    magfield3dstaticwizard.cpp \
    magfield3dtransintwizard.cpp \
    pf_mag2dsproject.cpp \
    pf_magfemnode.cpp \
    pf_magfemfile.cpp \
    sparsefemm.cpp \
    magfemplugin.cpp

RESOURCES += \
    res.qrc
