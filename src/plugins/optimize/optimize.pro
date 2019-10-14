DEFINES += OPTIMIZE_LIBRARY

QT += \
    printsupport \

include(../../feemplugin.pri)

HEADERS += \
    optimizeplugin.h \
    inputparamwidget.h \
    itemdelegate.h \
    multiobjectdialog.h \
    readonlydelegate.h \
    singleobjectdialog.h \
    targetwidget.h \
    multiobjectcore/particle.h \
    multiobjectcore/pso.h \
    singleobjectcore/sparticle.h \
    singleobjectcore/spso.h \
    optimizeconstants.h

SOURCES += \
    optimizeplugin.cpp \
    inputparamwidget.cpp \
    itemdelegate.cpp \
    multiobjectdialog.cpp \
    readonlydelegate.cpp \
    singleobjectdialog.cpp \
    targetwidget.cpp \
    multiobjectcore/particle.cpp \
    multiobjectcore/pso.cpp \
    singleobjectcore/sparticle.cpp \
    singleobjectcore/spso.cpp

RESOURCES += \
    optimize.qrc

