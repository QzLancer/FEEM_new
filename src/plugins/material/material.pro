DEFINES += MATERIAL_LIBRARY
QT += \
    printsupport \

include(../../feemplugin.pri)  

HEADERS += \
    material_global.h \
    materialconstants.h \
    materialplugin.h \
    pf_magmaterialdialog.h \
    pf_material.h \
    pf_materiallibrary.h \
    pf_materialmanager.h \
    pf_materialtreemodel.h \
    pf_bhcurvedialog.h \
    pf_materialnode.h

SOURCES += \
    materialplugin.cpp \
    pf_magmaterialdialog.cpp \
    pf_material.cpp \
    pf_materiallibrary.cpp \
    pf_materialmanager.cpp \
    pf_materialtreemodel.cpp \
    pf_bhcurvedialog.cpp \
    pf_materialnode.cpp

RESOURCES += \
    material.qrc

