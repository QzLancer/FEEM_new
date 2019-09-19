shared {
    DEFINES += UTILS_LIBRARY
} else {
    DEFINES += QTCREATOR_UTILS_STATIC_LIB
}


QT += widgets gui network qml


SOURCES += \
    $$PWD/stringutils.cpp \
    $$PWD/benchmarker.cpp \
    $$PWD/qtcassert.cpp \
    $$PWD/synchronousprocess.cpp

HEADERS += \
    $$PWD/utils_global.h \
    $$PWD/stringutils.h \
    $$PWD/benchmarker.h \
    $$PWD/executeondestruction.h \
    $$PWD/predicates.h \
    $$PWD/qtcassert.h \
    $$PWD/synchronousprocess.h

include(mimetypes/mimetypes.pri)

