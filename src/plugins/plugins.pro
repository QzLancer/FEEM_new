include(../../feem.pri)

TEMPLATE  = subdirs

SUBDIRS   = \
    coreplugin \
    output \
    CAD \
    material \
    mesh \
    solver \
    postoperation \
    project \
    bounce \
    welcome \
    optimize \
    magfemprojectmanagerplugin \

for(p, SUBDIRS) {
    FEEM_PLUGIN_DEPENDS =
    include($$p/$${p}_dependencies.pri)
    pv = $${p}.depends
    $$pv = $$FEEM_PLUGIN_DEPENDS
}

