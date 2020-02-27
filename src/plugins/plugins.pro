include(../../feem.pri)

TEMPLATE  = subdirs

SUBDIRS   = \
    coreplugin \  
    CAD \
    material \
    mesh \
    solver \
    project \
    output \
    bounce \
    welcome \
    optimize \
    commonfem \
    postoperation \
    magnetic \
    heatplugin \

for(p, SUBDIRS) {
    FEEM_PLUGIN_DEPENDS =
    include($$p/$${p}_dependencies.pri)
    pv = $${p}.depends
    $$pv = $$FEEM_PLUGIN_DEPENDS
}

