DEFINES += HEATPLUGIN_LIBRARY

include(../../feemplugin.pri)

# HeatPlugin files

SOURCES += \
    boundaryprop.cpp \
    heatboundarydialog.cpp \
    heatplugin.cpp \
    heat2dstaticwizard.cpp \
    heat3dstaticwizard.cpp \
    pf_heat2dsproject.cpp \
    pf_heatfemnode.cpp

HEADERS += \
    boundaryprop.h \
    heatboundarydialog.h \
        heatplugin_global.h \
        heatpluginconstants.h \
    heatplugin.h \
    heat2dstaticwizard.h \
    heat3dstaticwizard.h \
    pf_heat2dsproject.h \
    pf_heatfemnode.h

RESOURCES += \
    icons.qrc
