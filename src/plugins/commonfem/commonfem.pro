DEFINES += COMMONFEMPLUGIN_LIBRARY

include(../../feemplugin.pri)

HEADERS += \
    commonfem_global.h \
    commonfemconstants.h \
    commonfemplugin.h \
    pf_commonfemproject.h \
    pf_facesettingdialog.h

SOURCES += \
    commonfemplugin.cpp \
    pf_commonfemproject.cpp \
    pf_facesettingdialog.cpp

RESOURCES += \
