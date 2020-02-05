/*
+--------------------------------------------------------------------+
| GPConsts.h: header file for constants                              |
+--------------------------------------------------------------------+
|                                                                    |
| Author : Alfredo Ferreira (Jr.)                                    |
| E-mail : alfredo.ferreira@inesc-id.pt                              |
| Website: http://immi.inesc-id.pt/~afj                              |
|                                                                    |
| Version: 2.0 (converted from KernelConsts)                         |
| Created: May 2003                                                  |
| Updated: Jun-Aug 2003                                              |
| Updated: Jan 2008                                                  |
|                                                                    |
+--------------------------------------------------------------------+
| Intelligent Multimodal Interfaces Group at INESC-ID                |
| Department of Information Systems and Computer Science             |
| IST/Technical University of Lisbon                                 |
| Rua Alves Redol 9                                                  |
| 100-029 Lisboa, Portugal                                           |
+--------------------------------------------------------------------+
|                                                                    |
| Copyright (c) 2003-2008 INESC-ID                                   |
|                                                                    |
|   The copyright to the computer program(s) herein is the property  |
| of INESC-ID, Portugal. The program(s) may be used and/or copied    |
| only with the written permission of INESC-ID or in accordance with |
| the terms and conditions stipulated in the agreement/contract      |
| under which the program(s) have been supplied.                     |
|                                                                    |
+--------------------------------------------------------------------+
*/
/*********************************************************************
 * NOTE: 
 * To disable message display during processing define the variables:
 *     SILENT_SIMPLIFICATION,SILENT_SBR_QUERY
 * 
 * in the "PolygonDetection" project
 *                                                                  
 *********************************************************************/

#pragma once

#ifndef GP_CONSTS_H_INCLUDED
#define GP_CONSTS_H_INCLUDED

#define DEFAULT_POLYLINE_COLOR "#001020"
#define DEFAULT_POLYLINE_FILL "none"

// // value used for clustering and roudning
// #define ROUNDING_PRECISION 500 // originally was 1000
// #define ITERATED_SNAP_ROUNDING_PRECISION 200 // (1/200 size of drawing)
// #define CLUSTERING_DISTANCE_FACTOR 100 // (1/100 size of the drawing)
// #define SMALLER_POLYGON_PERIMETER_FACTOR 20 // (1/20 size of the drawing)
// #define SIMPLIFICATION_PRECISION 512 // 1/512 size of drawing
// 
// 

// flags
#define FLAG_RESET		0x00
#define FLAG_VISITED	0x01
#define FLAG_REMOVE		0x02
#define FLAG_IGNORE		0x04
#define FLAG_IN_POLYGON	0x08
#define FLAG_KEEP		0x10

#define NORMAL_ORDER    0x00
#define INVERSE_ORDER   0x01
#define AT_END          0x02
#define AT_BEGIN        0x04
#define AT_MIDDLE       0x08
// 
// #define MAX_GRAPH_VERTEX_COUNT 3000 /*changed from 1500 by afj @ 2007/10/26 */
// 
// #define MAX_PROCESSING_TIME_QUERY_SEC 30
// #define MAX_PROCESSING_TIME_BUILD_SEC 14400 
// 
// #ifndef MSECS2SECS_THRESHOLD
// #define MSECS2SECS_THRESHOLD 10000
// #endif

#endif
