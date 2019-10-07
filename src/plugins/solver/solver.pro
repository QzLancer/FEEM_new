DEFINES += MESH_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)


msvc: QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250

HEADERS += \
    solver_global.h \
    solverconstants.h \
    solverplugin.h

SOURCES += \
    solverplugin.cpp


