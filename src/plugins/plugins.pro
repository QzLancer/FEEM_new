include(../../feem.pri)

TEMPLATE  = subdirs

SUBDIRS   = \
    coreplugin \  
    CAD \
    material \
    mesh \
    solver \
    postoperation \
    project \
    output \
    bounce \
    welcome \
    optimize \
    magfemprojectmanagerplugin \
    heatplugin \

for(p, SUBDIRS) {
    FEEM_PLUGIN_DEPENDS =
    include($$p/$${p}_dependencies.pri)
    pv = $${p}.depends
    $$pv = $$FEEM_PLUGIN_DEPENDS
}

