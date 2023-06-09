DEFINES += CORE_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)

include($$PWD/../../libs/qtribbon/ribbonsample/qtitanribbon.pri)
include($$PWD/../../libs/qtribbon/ribbonsample/shared/aboutdialog.pri)
include($$PWD/../../libs/qtribbon/ribbonsample/shared/ribbonwindow.pri)

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
    actionmanager/proxyaction.cpp \
    inavigationwidgetfactory.cpp \
    ipage.cpp \
    pagemanager.cpp \
    pf_pagewidget.cpp \
    workpage.cpp \
    iwelcomepage.cpp \
    geometrymanager/geometrymanager.cpp \
    geometrymanager/geometryview.cpp \
    dialogs/newdialog.cpp \
    iwizardfactory.cpp \
    basefilewizardfactory.cpp \
    generatedfile.cpp \
    basefilewizard.cpp \
    geometrymanager/igeometry.cpp
    

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
    actionmanager/proxyaction.h \
    inavigationwidgetfactory.h \
    ipage.h \
    pagemanager.h \
    pf_pagewidget.h \
    workpage.h \
    iwelcomepage.h \
    geometrymanager/geometrymanager.h \
    geometrymanager/geometrymanager_p.h \
    geometrymanager/geometryview.h \
    dialogs/newdialog.h \
    iwizardfactory.h \
    basefilewizardfactory.h \
    generatedfile.h \
    basefilewizard.h \
    ifilewizardextension.h \
    geometrymanager/igeometry.h
  

FORMS += \
    dialogs/newdialog.ui

