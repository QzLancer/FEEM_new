#ifndef PD_CONSTS_H_INCLUDED
#define PD_CONSTS_H_INCLUDED

// set the default value for silent processing
#define SILENT_POLYGON_DETECTION_BY_DEFAULT false

// set the colors for the polygon on the SVG file
#define POLYGON_COLOR_H 359.0f
#define POLYGON_COLOR_S 0.9f
#define POLYGON_COLOR_V 0.9f

// value used for clustering and roudning
#define ROUNDING_PRECISION 500 // originally was 1000
#define ITERATED_SNAP_ROUNDING_PRECISION 200 // (1/200 size of drawing)
#define CLUSTERING_DISTANCE_FACTOR 100 // (1/100 size of the drawing)
#define SMALLER_POLYGON_PERIMETER_FACTOR 20 // (1/20 size of the drawing)
#define SIMPLIFICATION_PRECISION 512 // 1/512 size of drawing

#define MAX_GRAPH_VERTEX_COUNT 3000 /*changed from 1500 by afj @ 2007/10/26 */

#define MAX_PROCESSING_TIME_DEFAULT 240

#ifndef MSECS2SECS_THRESHOLD
#define MSECS2SECS_THRESHOLD 10000
#endif


#endif
