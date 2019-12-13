DEFINES += HEATPLUGIN_LIBRARY

include(../../feemplugin.pri)

# HeatPlugin files

SOURCES += \
    heatplugin.cpp \
    heat2dstaticwizard.cpp \
    heat3dstaticwizard.cpp

HEADERS += \
        heatplugin_global.h \
        heatpluginconstants.h \
    heatplugin.h \
    heat2dstaticwizard.h \
    heat3dstaticwizard.h

RESOURCES += \
    icons.qrc
