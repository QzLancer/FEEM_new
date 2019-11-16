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
    contourtest/contourtestwidget.h

SOURCES += \
    postoperationplugin.cpp \
    qcustomplot/qcustomplot.cpp \
    contourtest/plot.cpp \
    contourtest/contourtestwidget.cpp

include(./plot/plotwidget.pri)


