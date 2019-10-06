DEFINES += CAD_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)

include(./entity/entity.pri)
include(./action/action.pri)

msvc: QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250

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
    pf_actionhandler.h

SOURCES += \
    pf_cadwidget.cpp \
    pf_flag.cpp \
    pf_graphicview.cpp \
    pf_plot.cpp \
    cad.cpp \
    pf_actionhandler.cpp

RESOURCES += \
    cad.qrc


