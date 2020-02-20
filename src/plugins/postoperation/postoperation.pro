DEFINES += POSTOPERATION_LIBRARY
DEFINES += QCUSTOMPLOT_COMPILE_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)


HEADERS += \
    postoperation_global.h \
    postoperationconstants.h \
    postoperationplugin.h \
    qcustomplot/qcustomplot.h \
    contourtest/plot.h \
    contourtest/contourtestwidget.h \
    colortables/pf_colortables.h \
    pf_resultnode.h

SOURCES += \
    postoperationplugin.cpp \
    qcustomplot/qcustomplot.cpp \
    contourtest/plot.cpp \
    contourtest/contourtestwidget.cpp \
    colortables/pf_colortables.cpp \
    pf_resultnode.cpp

include(./plot/plotwidget.pri)


