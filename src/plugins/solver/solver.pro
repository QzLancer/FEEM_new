DEFINES += SOLVER_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)

HEADERS += \
    solver_global.h \
    solverconstants.h \
    solverplugin.h \

SOURCES += \
    solverplugin.cpp \

RESOURCES += \
    res.qrc



