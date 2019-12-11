DEFINES += SOLVER_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)

HEADERS += \
    solver_global.h \
    solverconstants.h \
    solverplugin.h \
    magsolver.h \
    sparsefemm.h

SOURCES += \
    solverplugin.cpp \
    magsolver.cpp \
    sparsefemm.cpp

RESOURCES += \
    res.qrc



