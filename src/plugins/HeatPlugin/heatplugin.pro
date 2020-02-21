DEFINES += HEATPLUGIN_LIBRARY

include(../../feemplugin.pri)

# HeatPlugin files

SOURCES += \
    boundaryprop.cpp \
    boundarytreemodel.cpp \
    heatboundarydialog.cpp \
    heatplugin.cpp \
    heat2dstaticwizard.cpp \
    heat3dstaticwizard.cpp \
    pf_boundarynode.cpp \
    pf_heat2dsproject.cpp \
    pf_heatfemnode.cpp

HEADERS += \
    boundaryprop.h \
    boundarytreemodel.h \
    heatboundarydialog.h \
        heatplugin_global.h \
        heatpluginconstants.h \
    heatplugin.h \
    heat2dstaticwizard.h \
    heat3dstaticwizard.h \
    pf_boundarynode.h \
    pf_heat2dsproject.h \
    pf_heatfemnode.h

RESOURCES += \
    icons.qrc
