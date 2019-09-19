DEFINES += QTITAN_LIBRARY
include(../../feemlibrary.pri)

include($$PWD/src/shared/platform.pri)

#VERSION = 3.2.5

include($$PWD/src/ribbon/ribbon.pri)
include($$PWD/src/styles/styles.pri)

!lessThan(QT_VER_MAJ, 5) {
  QT += widgets core-private widgets-private gui-private
} else {
  #DLLDESTDIR = $$PWD/../../../bin
  #DLLDESTDIR = $$member(DLLDESTDIR, 0)$$QTITAN_LIB_PREFIX
}




