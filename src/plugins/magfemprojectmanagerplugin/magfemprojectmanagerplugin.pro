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
    pf_mag2dsproject.h \
    pf_magfemnode.h \
    pf_magfemfile.h \
    pf_facesettingdialog.h \
    sparsefemm.h \
    pf_commonfemproject.h

SOURCES += \
    magfemprojectmanagerpluginplugin.cpp \
    magfieldwizard.cpp \
    magfield2dtransientwizard.cpp \
    magfield3dstaticwizard.cpp \
    magfield3dtransintwizard.cpp \
    pf_mag2dsproject.cpp \
    pf_magfemnode.cpp \
    pf_magfemfile.cpp \
    pf_facesettingdialog.cpp \
    sparsefemm.cpp \
    pf_commonfemproject.cpp

RESOURCES += \
    res.qrc
