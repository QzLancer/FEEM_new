	// 
/*
+--------------------------------------------------------------------+
| Macros.h: header file for macros                                   |
+--------------------------------------------------------------------+
|                                                                    |
| Author : Alfredo Ferreira (Jr.)                                    |
| E-mail : alfredo.ferreira@inesc-id.pt                              |
| Website: http://immi.inesc-id.pt/~afj                              |
|                                                                    |
| Version: 1.00                                                      |
| Created: May 2004                                                  |
|                                                                    |
+--------------------------------------------------------------------+
| Visualization and Intelligent Multimodal Interfaces Group          |
| Department of Information Systems and Computer Science             |
| INESC-ID/IST/Technical University of Lisbon                        |
| Taguspark, Edificio IST, Nucleo 9, Piso 2                          |
| 2780-990 Porto Salvo                                               |
| Portugal                                                           |
+--------------------------------------------------------------------+
|                                                                    |
| Copyright (c) 2004-2008 INESC-ID                                   |
|                                                                    |
|   The copyright to the computer program(s) herein is the property  |
| of INESC-ID, Portugal. The program(s) may be used and/or copied    |
| only with the written permission of INESC-ID or in accordance with |
| the terms and conditions stipulated in the agreement/contract      |
| under which the program(s) have been supplied.                     |
|                                                                    |
+--------------------------------------------------------------------+
*/

#ifndef MACROS_H_INCLUDED
#define MACROS_H_INCLUDED

//////////////////////////////////////////////////////////////////////////
// NOTE: to use with other application, change the include below
//       if do not want to specify an application, set DISABLE_YIELD
//
//#define MAIN_APP_HEADER_FILE "QiQA/include/QiQAApp.h"
#define DISABLE_YIELD
//
/////////////////////////////////////////////////////////////////////////

#ifndef NULL
#define NULL 0
#endif


template <typename T>
T MIN(const T& a, const T& b)
{
	return ((a)<(b)?(a):(b));
}

template <typename T>
T MAX(const T& a, const T& b)
{
	return ((b)<(a)?(a):(b));
}


template <typename T>
T ORERED(const T& a, const T& b, const T& c)
{
	return ((a)<=(b) && (b)<=(c));
}

#define CALL_MEMBER_FUNCTION(object,ptrToMember) ((object).*(ptrToMember)) 

#define ALLOCATE_MEMORY(t, s)  static_cast<t*>( malloc(s * sizeof(t)) )

#define FREE(ptr) { if (ptr) { free(ptr); ptr = nullptr; }}
#define DELETE_OBJECT(obj) { if (obj!=nullptr) { delete(obj); obj = nullptr; }}
#define wxDELETE(obj) { if (obj!=nullptr) { delete(obj); obj = nullptr; }}
#define DELETE_ARRAY(p_array) { if (p_array) p_array->clear(); DELETE_OBJECT(p_array); }
#define DELETE_ARRAY_AND_OBJECTS(p_array) { if (p_array) {\
		for (size_t _array_index=0; _array_index<p_array->GetCount();_array_index++) DELETE_OBJECT((*p_array)[_array_index]); \
		DELETE_OBJECT(p_array); }}
#define WX_CLEAR_ARRAY(p_array) {  {\
        for (int _array_index=0; _array_index<p_array.size();_array_index++) {}/*delete(p_array.at(_array_index));*/ \
         }}


#ifndef PI
#define PI 3.1415926535897932384626433832795f
#endif

#define RAD360DEG	6.283185307179586476925286766559f 
#define RAD270DEG	4.7123889803846898576939650749193f
#define RAD180DEG	3.1415926535897932384626433832795f
#define RAD90DEG	1.5707963267948966192313216916398f
#define RAD45DEG	0.78539816339744830961566084581988f

#define DEG2RAD(ang) (ang*PI/180)

template <typename T>
T SQR(const T& value)
{
	return value * value;
}

#define LN2INV 1.442695041      /* 1 over natural log of 2 :                    
                                 * * log2(x) = (1/log(2)) * log(x) */ 


#define ABS(a) (((a) >= 0) ? (a): -(a))  /* integer absolute value */
#define ABSF(a) (((a) >= 0.0) ? (a): -(a))  /* floating absolute value */

#define CHECK_FLAG(flag, mask) ((flag & mask)!=0)


/************************************************************************/
/* Macro that computes the min/max of two points                        */
/************************************************************************/
#define COMPUTE_MINMAX_POINT(dest, p1, p2, op) { \
	(dest).x = op((p1).x, (p2).x); \
	(dest).y = op((p1).y, (p2).y); \
	(dest).z = op((p1).z, (p2).z); \
}

/************************************************************************/
/* Macro that extends an bounding box (if needed) to include point p1   */
/************************************************************************/
#define RECALC_BOUNDING_BOX(bb_bl,bb_tr,p) { \
	COMPUTE_MINMAX_POINT(bb_bl, bb_bl, p, MIN); \
	COMPUTE_MINMAX_POINT(bb_tr, bb_tr, p, MAX); \
}


// Basic structure for a 3D point
typedef struct generic_point_3d
{
	double	x;
	double	y;
	double	z;
} REALPOINT, *PREALPOINT;

typedef struct generic_line_2d
{
	PREALPOINT a;
	PREALPOINT b;
} REALLINE, *PREALLINE;

#define TRIM_LONG_STRING(s) ((s).Len()<64?s:wxString::Format("...%s",(s).Mid((s).Len()-64)))

// Yields control to pending messages in the windowing system
#ifdef DISABLE_YIELD
#define YIELD_CONTROL() {::wxSafeYield();};
#else 
#include MAIN_APP_HEADER_FILE 
#define YIELD_CONTROL() {wxLog::FlushActive();	wxGetApp().Yield();}
#endif

#endif
