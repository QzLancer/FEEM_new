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
    pf_resultnode.h \
    pf_postview.h \
    pf_postprocessorwidget.h \
    pf_postfeem.h

SOURCES += \
    postoperationplugin.cpp \
    qcustomplot/qcustomplot.cpp \
    contourtest/plot.cpp \
    contourtest/contourtestwidget.cpp \
    colortables/pf_colortables.cpp \
    pf_resultnode.cpp \
    pf_postview.cpp \
    pf_postprocessorwidget.cpp \
    pf_postfeem.cpp

include(./plot/plotwidget.pri)


