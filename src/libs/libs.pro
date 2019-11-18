include(../../feem.pri)

TEMPLATE  = subdirs

SUBDIRS   += \
    extensionsystem \
    utils \
    qtribbon \
    QtAdvancedDock \
    qwt \

for(l, SUBDIRS) {
    FEEM_LIB_DEPENDS =
    include($$l/$${l}_dependencies.pri)
    lv = $${l}.depends
    $$lv = $$FEEM_LIB_DEPENDS
}



