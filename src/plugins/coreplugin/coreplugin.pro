DEFINES += CORE_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)

include($$PWD/../../libs/qtribbon/ribbonsample/qtitanribbon.pri)
include($$PWD/../../libs/qtribbon/ribbonsample/shared/aboutdialog.pri)
include($$PWD/../../libs/qtribbon/ribbonsample/shared/ribbonwindow.pri)

msvc: QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250
SOURCES +=  \
    coreplugin.cpp \
    mainwindow.cpp \
    context.cpp \
    icore.cpp \
    id.cpp \
    idocument.cpp \
    actionmanager/actioncontainer.cpp \
    actionmanager/actionmanager.cpp \
    actionmanager/command.cpp \
    actionmanager/proxyaction.cpp
    

HEADERS +=  \
    core_global.h \
    coreplugin.h \
    mainwindow.h \
    context.h \
    icore.h \
    id.h \
    idocument.h \
    constants.h \
    actionmanager/actioncontainer.h \
    actionmanager/actioncontainer_p.h \
    actionmanager/actionmanager.h \
    actionmanager/actionmanager_p.h \
    actionmanager/command.h \
    actionmanager/command_p.h \
    actionmanager/proxyaction.h
  

