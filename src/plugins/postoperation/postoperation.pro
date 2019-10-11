DEFINES += POSTOPERATION_LIBRARY
DEFINES += QCUSTOMPLOT_COMPILE_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)

HEADERS += \
    postoperation_global.h \
    postoperationconstants.h \
    postoperationplugin.h \
    qcustomplot/qcustomplot.h

SOURCES += \
    postoperationplugin.cpp \
    qcustomplot/qcustomplot.cpp




