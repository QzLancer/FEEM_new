DEFINES += CAD_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)

include(./entity/entity.pri)
include(./action/action.pri)

HEADERS += \
    CAD_global.h \
    pf_cadwidget.h \
    pf_flag.h \
    pf_graphicview.h \
    pf_plot.h \
    pf_setting.h \
    cad.h \
    pf.h \
    cadconstants.h \
    pf_actionhandler.h \
    geometry2d.h

SOURCES += \
    pf_cadwidget.cpp \
    pf_flag.cpp \
    pf_graphicview.cpp \
    pf_plot.cpp \
    cad.cpp \
    pf_actionhandler.cpp \
    geometry2d.cpp

RESOURCES += \
    cad.qrc


