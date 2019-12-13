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
    multiobjectcore/particle.h \
    multiobjectcore/pso.h \
    singleobjectcore/sparticle.h \
    singleobjectcore/spso.h \
    optimizeconstants.h \
    singleobjectcore/singleobjwizard.h \
    typepage.h \
    singleobjectcore/singleobjectpage.h \
    singleobjectcore/singlepsopage.h \
    multiobjectcore/multiobjwizard.h \
    multiobjectcore/multiobjectpage.h \
    multiobjectcore/multipsopage.h \
    objectwidget.h

SOURCES += \
    optimizeplugin.cpp \
    inputparamwidget.cpp \
    itemdelegate.cpp \
    multiobjectdialog.cpp \
    readonlydelegate.cpp \
    singleobjectdialog.cpp \
    multiobjectcore/particle.cpp \
    multiobjectcore/pso.cpp \
    singleobjectcore/sparticle.cpp \
    singleobjectcore/spso.cpp \
    singleobjectcore/singleobjwizard.cpp \
    typepage.cpp \
    singleobjectcore/singleobjectpage.cpp \
    singleobjectcore/singlepsopage.cpp \
    multiobjectcore/multiobjwizard.cpp \
    multiobjectcore/multiobjectpage.cpp \
    multiobjectcore/multipsopage.cpp \
    objectwidget.cpp

RESOURCES += \
    optimize.qrc

