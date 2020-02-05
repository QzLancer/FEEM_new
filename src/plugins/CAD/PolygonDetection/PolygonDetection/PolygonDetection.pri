INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/tinyxml
INCLUDEPATH += $$PWD/graph_entities

HEADERS += \
    $$PWD/Line.h \
    $$PWD/LineSet.h \
    $$PWD/PDConsts.h \
    $$PWD/PDMacros.h \
    $$PWD/polygon.h \
    $$PWD/PolygonDetector.h \
    $$PWD/PolygonSet.h \
    $$PWD/tinyxml/tinystr.h \
    $$PWD/tinyxml/tinyxml.h \
    $$PWD/graph_entities/Cycle.h \
    $$PWD/graph_entities/CycleSet.h \
    $$PWD/graph_entities/Edge.h \
    $$PWD/graph_entities/Graph.h \
    $$PWD/graph_entities/IncidenceMatrix.h \
    $$PWD/graph_entities/MatrixModuloTwo.h \
    $$PWD/graph_entities/Vertex.h

SOURCES += \
    $$PWD/Line.cpp \
    $$PWD/LineSet.cpp \
    $$PWD/Polygon.cpp \
    $$PWD/PolygonDetector.cpp \
    $$PWD/PolygonSet.cpp \
    $$PWD/tinyxml/tinystr.cpp \
    $$PWD/tinyxml/tinyxml.cpp \
    $$PWD/tinyxml/tinyxmlerror.cpp \
    $$PWD/tinyxml/tinyxmlparser.cpp \
    $$PWD/graph_entities/Cycle.cpp \
    $$PWD/graph_entities/CycleSet.cpp \
    $$PWD/graph_entities/Edge.cpp \
    $$PWD/graph_entities/Graph.cpp \
    $$PWD/graph_entities/IncidenceMatrix.cpp \
    $$PWD/graph_entities/MatrixModuloTwo.cpp \
    $$PWD/graph_entities/Vertex.cpp
