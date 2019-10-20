DEFINES += PROJECT_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)

HEADERS += \
    project_export.h \
    project_global.h \
    pf_projectexplorer.h \
    pf_modelwidget.h \
    pf_node.h \
    pf_nodetreebuilder.h \
    pf_project.h \
    pf_projectmanager.h \
    pf_projectmodel.h \
    pf_projecttree.h \
    pf_projecttreewidget.h \
    pf_projectwelcomepage.h \
    pf_sessionmanager.h \
    projectwelcomepage.h \
    projectexplorerconstants.h

SOURCES += \
    pf_projectexplorer.cpp \
    pf_modelwidget.cpp \
    pf_node.cpp \
    pf_nodetreebuilder.cpp \
    pf_project.cpp \
    pf_projectmanager.cpp \
    pf_projectmodel.cpp \
    pf_projecttree.cpp \
    pf_projecttreewidget.cpp \
    pf_projectwelcomepage.cpp \
    pf_sessionmanager.cpp \
    projectwelcomepage.cpp
