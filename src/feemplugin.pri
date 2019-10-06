depfile = $$replace(_PRO_FILE_PWD_, ([^/]+$), \\1/\\1_dependencies.pri)
exists($$depfile) {
    include($$depfile)
    isEmpty(FEEM_PLUGIN_NAME): \
        error("$$basename(depfile) does not define FEEM_PLUGIN_NAME.")
} else {
    isEmpty(FEEM_PLUGIN_NAME): \
        error("FEEM_PLUGIN_NAME is empty. Maybe you meant to create $$basename(depfile)?")
}
TARGET = $$FEEM_PLUGIN_NAME

plugin_deps = $$FEEM_PLUGIN_DEPENDS
plugin_test_deps = $$FEEM_TEST_DEPENDS
plugin_recmds = $$FEEM_PLUGIN_RECOMMENDS

include(../feem.pri)

defineReplace(dependencyName) {
    dependencies_file =
    for(dir, FEEM_PLUGIN_DIRS) {
        exists($$dir/$$1/$${1}_dependencies.pri) {
            dependencies_file = $$dir/$$1/$${1}_dependencies.pri
            break()
        }
    }
    isEmpty(dependencies_file): \
        error("Plugin dependency $$dep not found")
    include($$dependencies_file)
    return($$FEEM_PLUGIN_NAME)
}

# for substitution in the .json
dependencyList =
for(dep, plugin_deps) {
    dependencyList += "        { \"Name\" : \"$$dependencyName($$dep)\", \"Version\" : \"$$FEEM_VERSION\" }"
}
for(dep, plugin_recmds) {
    dependencyList += "        { \"Name\" : \"$$dependencyName($$dep)\", \"Version\" : \"$$FEEM_VERSION\", \"Type\" : \"optional\" }"
}
for(dep, plugin_test_deps) {
    dependencyList += "        { \"Name\" : \"$$dependencyName($$dep)\", \"Version\" : \"$$FEEM_VERSION\", \"Type\" : \"test\" }"
}
dependencyList = $$join(dependencyList, ",$$escape_expand(\\n)")

dependencyList = "\"Dependencies\" : [$$escape_expand(\\n)$$dependencyList$$escape_expand(\\n)    ]"

isEmpty(USE_USER_DESTDIR) {
    DESTDIR = $$IDE_PLUGIN_PATH
} else {
    win32 {
        DESTDIRAPPNAME = "feem"
        DESTDIRBASE = "$$(LOCALAPPDATA)"
        isEmpty(DESTDIRBASE):DESTDIRBASE="$$(USERPROFILE)\Local Settings\Application Data"
    }
    DESTDIR = "$$DESTDIRBASE/$$DESTDIRAPPNAME/plugins/$$FEEM_VERSION"
}

LIBS += -L$$DESTDIR
INCLUDEPATH += $$OUT_PWD

# copy the plugin spec
isEmpty(TARGET) {
    error("feemplugin.pri: You must provide a TARGET")
}

PLUGINJSON = $$_PRO_FILE_PWD_/$${TARGET}.json
PLUGINJSON_IN = $${PLUGINJSON}.in
exists($$PLUGINJSON_IN) {
    DISTFILES += $$PLUGINJSON_IN
    QMAKE_SUBSTITUTES += $$PLUGINJSON_IN
    PLUGINJSON = $$OUT_PWD/$${TARGET}.json
} else {
    # need to support that for external plugins
    DISTFILES += $$PLUGINJSON
}


contains(QT_CONFIG, reduce_exports):CONFIG += hide_symbols

TEMPLATE = lib
CONFIG += plugin plugin_with_soname
# 安装的目录，只有在安装的时候才会用到
target.path = $$INSTALL_PLUGIN_PATH
INSTALLS += target
# 定义将dll拷贝的位置
win32 {
    DLLDESTDIR = $$INSTALL_PLUGIN_PATH
}
TARGET = $$feemLibraryTargetName($$TARGET)

