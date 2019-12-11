DEFINES += CAD_LIBRARY
DEFINES += PF_GraphicView_COMPILE_LIBRARY
QT += \
    printsupport \

INCLUDEPATH += $$PWD

include(../../feemplugin.pri)

include(./entity/entity.pri)
include(./action/action.pri)

INCLUDEPATH += $$PWD/gmsh

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
    geometry2d.h \
    gmsh/gmsh.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$_PRO_FILE_PWD_/../../../bin/ -lgmsh
else:win32:CONFIG(debug, debug|release): LIBS += -L$$_PRO_FILE_PWD_/../../../bin/ -lgmsh


