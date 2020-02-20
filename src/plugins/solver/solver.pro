DEFINES += SOLVER_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)

HEADERS += \
    solver_global.h \
    solverconstants.h \
    solverplugin.h \
    pf_solvernode.h

SOURCES += \
    solverplugin.cpp \
    pf_solvernode.cpp

RESOURCES += \
    res.qrc



