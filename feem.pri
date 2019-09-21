!isEmpty(FEEM_PRI_INCLUDED):error("feem.pri already included")
FEEM_PRI_INCLUDED = 1
# 版本信息
FEEM_VERSION = 0.0.1
FEEM_COMPAT_VERSION = 0.0.1
VERSION = $$FEEM_VERSION
FEEM_DISPLAY_VERSION = 0.0.1
FEEM_COPYRIGHT_YEAR = 2019
BINARY_ARTIFACTS_BRANCH = 0.0

isEmpty(IDE_DISPLAY_NAME):           IDE_DISPLAY_NAME = FEEM
isEmpty(IDE_ID):                     IDE_ID = FEEM
isEmpty(IDE_CASED_ID):               IDE_CASED_ID = FEEM

isEmpty(PRODUCT_BUNDLE_IDENTIFIER): PRODUCT_BUNDLE_IDENTIFIER = org.hit.$$IDE_ID

CONFIG += c++14
#ignore warning C4819
QMAKE_CXXFLAGS += /wd"4819"

DEFINES += _CRT_SECURE_NO_WARNINGS

# 生成库文件名称
defineReplace(feemLibraryTargetName) {
   unset(LIBRARY_NAME)
   LIBRARY_NAME = $$1
   CONFIG(debug, debug|release) {
      !debug_and_release|build_pass {
          mac:RET = $$member(LIBRARY_NAME, 0)_debug
              else:win32:RET = $$member(LIBRARY_NAME, 0)d
      }
   }
   isEmpty(RET):RET = $$LIBRARY_NAME
   return($$RET)
}
# 生成带版本号的库文件名称
defineReplace(feemLibraryName) {
   RET = $$feemLibraryTargetName($$1)
   win32 {
      VERSION_LIST = $$split(FEEM_VERSION, .)
      RET = $$RET$$first(VERSION_LIST)
   }
   return($$RET)
}
# 判断Qt的版本号
defineTest(minQtVersion) {
    maj = $$1
    min = $$2
    patch = $$3
    isEqual(QT_MAJOR_VERSION, $$maj) {
        isEqual(QT_MINOR_VERSION, $$min) {
            isEqual(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
            greaterThan(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
        }
        greaterThan(QT_MINOR_VERSION, $$min) {
            return(true)
        }
    }
    greaterThan(QT_MAJOR_VERSION, $$maj) {
        return(true)
    }
    return(false)
}

# For use in custom compilers which just copy files
defineReplace(stripSrcDir) {
    return($$relative_path($$absolute_path($$1, $$OUT_PWD), $$_PRO_FILE_PWD_))
}

isEmpty(IDE_LIBRARY_BASENAME) {
    IDE_LIBRARY_BASENAME = lib
}
# 源代码根目录
IDE_SOURCE_TREE = $$PWD
FEEM_PREFIX = $$IDE_SOURCE_TREE
# build目录
isEmpty(IDE_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    IDE_BUILD_TREE = $$clean_path($$OUT_PWD)
    IDE_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

IDE_APP_PATH = $$IDE_SOURCE_TREE/bin
osx {
    IDE_APP_TARGET   = "$$IDE_DISPLAY_NAME"
} else {
    contains(TEMPLATE, vc.*):vcproj = 1
    IDE_APP_TARGET   = $$IDE_ID

    # target output path if not set manually
    isEmpty(IDE_OUTPUT_PATH): IDE_OUTPUT_PATH = $$IDE_BUILD_TREE

    IDE_LIBRARY_PATH = $$IDE_OUTPUT_PATH/$$IDE_LIBRARY_BASENAME
    IDE_PLUGIN_PATH  = $$IDE_OUTPUT_PATH/bin/plugins
    #IDE_DATA_PATH    = $$IDE_OUTPUT_PATH/share/
    #IDE_DOC_PATH     = $$IDE_OUTPUT_PATH/share/doc/
    IDE_BIN_PATH     = $$IDE_OUTPUT_PATH/bin
    win32: \
        IDE_LIBEXEC_PATH = $$IDE_OUTPUT_PATH/bin
    else: \
        IDE_LIBEXEC_PATH = $$IDE_OUTPUT_PATH/libexec/
    !isEqual(IDE_SOURCE_TREE, $$IDE_OUTPUT_PATH):copydata = 1

    LINK_LIBRARY_PATH = $$IDE_BUILD_TREE/$$IDE_LIBRARY_BASENAME/
    LINK_PLUGIN_PATH  = $$LINK_LIBRARY_PATH/plugins

    INSTALL_LIBRARY_PATH = $$FEEM_PREFIX/$$IDE_LIBRARY_BASENAME
    INSTALL_PLUGIN_PATH  = $$FEEM_PREFIX/bin/plugins
    win32: \
        INSTALL_LIBEXEC_PATH = $$FEEM_PREFIX/bin
    else: \
        INSTALL_LIBEXEC_PATH = $$FEEM_PREFIX/libexec/
    #INSTALL_DATA_PATH    = $$FEEM_PREFIX/share/
    #INSTALL_DOC_PATH     = $$FEEM_PREFIX/share/doc/
    INSTALL_BIN_PATH     = $$FEEM_PREFIX/bin
    INSTALL_APP_PATH     = $$FEEM_PREFIX/bin
}

RELATIVE_PLUGIN_PATH = $$relative_path($$IDE_PLUGIN_PATH, $$IDE_BIN_PATH)
RELATIVE_LIBEXEC_PATH = $$relative_path($$IDE_LIBEXEC_PATH, $$IDE_BIN_PATH)
RELATIVE_DATA_PATH = $$relative_path($$IDE_DATA_PATH, $$IDE_BIN_PATH)
RELATIVE_DOC_PATH = $$relative_path($$IDE_DOC_PATH, $$IDE_BIN_PATH)
DEFINES += $$shell_quote(RELATIVE_PLUGIN_PATH=\"$$RELATIVE_PLUGIN_PATH\")
DEFINES += $$shell_quote(RELATIVE_LIBEXEC_PATH=\"$$RELATIVE_LIBEXEC_PATH\")
DEFINES += $$shell_quote(RELATIVE_DATA_PATH=\"$$RELATIVE_DATA_PATH\")
DEFINES += $$shell_quote(RELATIVE_DOC_PATH=\"$$RELATIVE_DOC_PATH\")

INCLUDEPATH += \
    #$$IDE_BUILD_TREE/src \
    $$IDE_SOURCE_TREE/src \
    $$IDE_SOURCE_TREE/src/libs \

win32:exists($$IDE_SOURCE_TREE/lib/) {
    # for .lib in case of binary package with dev package
    LIBS *= -L$$IDE_SOURCE_TREE/lib/
    LIBS *= -L$$IDE_SOURCE_TREE/lib/plugins
}
# 添加插件的包含路径
FEEM_PLUGIN_DIRS_FROM_ENVIRONMENT = $$(FEEM_PLUGIN_DIRS)
FEEM_PLUGIN_DIRS += $$split(FEEM_PLUGIN_DIRS_FROM_ENVIRONMENT, $$QMAKE_DIRLIST_SEP)
FEEM_PLUGIN_DIRS += $$IDE_SOURCE_TREE/src/plugins
for(dir, FEEM_PLUGIN_DIRS) {
    INCLUDEPATH += $$dir
}
# 添加库文件的包含路径
FEEM_LIB_DIRS_FROM_ENVIRONMENT = $$(FEEM_LIB_DIRS)
FEEM_LIB_DIRS += $$split(FEEM_LIB_DIRS_FROM_ENVIRONMENT, $$QMAKE_DIRLIST_SEP)
FEEM_LIB_DIRS += $$IDE_SOURCE_TREE/src/libs
for(dir, FEEM_LIB_DIRS) {
    INCLUDEPATH += $$dir
}

CONFIG += \
    depend_includepath \
    #no_include_pwd

LIBS *= -L$$LINK_LIBRARY_PATH
exists($$IDE_LIBRARY_PATH): LIBS *= -L$$IDE_LIBRARY_PATH  # library path from output path

!isEmpty(vcproj) {
    DEFINES += IDE_LIBRARY_BASENAME=\"$$IDE_LIBRARY_BASENAME\"
} else {
    DEFINES += IDE_LIBRARY_BASENAME=\\\"$$IDE_LIBRARY_BASENAME\\\"
}


msvc {
    #Don't warn about sprintf, fopen etc being 'unsafe'
    DEFINES += _CRT_SECURE_NO_WARNINGS
    QMAKE_CXXFLAGS_WARN_ON *= -w44996
    # Speed up startup time when debugging with cdb
    QMAKE_LFLAGS_DEBUG += /INCREMENTAL:NO
}

qt {
    QT       += core gui
    contains(QT, core): QT += concurrent
    contains(QT, gui): QT += widgets
    greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
    QT +=  printsupport gui-private
}


!isEmpty(FEEM_PLUGIN_DEPENDS) {
    LIBS *= -L$$IDE_PLUGIN_PATH  # plugin path from output directory
    LIBS *= -L$$LINK_PLUGIN_PATH  # when output path is different from Qt Creator build directory
}

# recursively resolve plugin deps
done_plugins =
for(ever) {
    isEmpty(FEEM_PLUGIN_DEPENDS): \
        break()
    done_plugins += $$FEEM_PLUGIN_DEPENDS
    for(dep, FEEM_PLUGIN_DEPENDS) {
        dependencies_file =
        for(dir, FEEM_PLUGIN_DIRS) {
            exists($$dir/$$dep/$${dep}_dependencies.pri) {
                dependencies_file = $$dir/$$dep/$${dep}_dependencies.pri
                break()
            }
        }
        isEmpty(dependencies_file): \
            error("Plugin dependency $$dep not found")
        include($$dependencies_file)
        LIBS += -l$$feemLibraryName($$FEEM_PLUGIN_NAME)
    }
    FEEM_PLUGIN_DEPENDS = $$unique(FEEM_PLUGIN_DEPENDS)
    FEEM_PLUGIN_DEPENDS -= $$unique(done_plugins)
}

# recursively resolve library deps
done_libs =
for(ever) {
    isEmpty(FEEM_LIB_DEPENDS): \
        break()
    done_libs += $$FEEM_LIB_DEPENDS
    for(dep, FEEM_LIB_DEPENDS) {
        dependencies_file =
        for(dir, FEEM_LIB_DIRS) {
            exists($$dir/$$dep/$${dep}_dependencies.pri) {
                dependencies_file = $$dir/$$dep/$${dep}_dependencies.pri
                break()
            }
        }
        isEmpty(dependencies_file): \
            error("Library dependency $$dep not found")
        include($$dependencies_file)
        LIBS += -l$$feemLibraryName($$FEEM_LIB_NAME)
    }
    FEEM_LIB_DEPENDS = $$unique(FEEM_LIB_DEPENDS)
    FEEM_LIB_DEPENDS -= $$unique(done_libs)
}
