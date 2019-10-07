DEFINES += POSTOPERATION_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)


msvc: QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250

HEADERS += \
    postoperation_global.h \
    postoperationconstants.h \
    postoperationplugin.h

SOURCES += \
    postoperationplugin.cpp




