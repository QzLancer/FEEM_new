#pragma once

#ifndef GP_MACROS_H_INCLUDED
#define GP_MACROS_H_INCLUDED

#include "../macros.h"


// //
// Following macro is used in line and polygon set implementation
// to sweep across the arrays
//
#define ITERATE_ALL_ENTITIES(entities_array, method) { \
	for (int k=(entities_array).size(); k>0; ) \
		(entities_array)[--k]->method; \
}


//
// Following macros are use in Polygon2D and Polyline2D implementation
//
#define TRIGGER(var, val, counter) { var=val; counter++; }

#define STEP_ITERATOR( iter, incr, max_val) { \
	if (incr<0) { \
		if (iter==0) \
			iter=max_val; \
	} \
	iter=(iter+incr)%(max_val); \
}

#define VERTEX_COUNT_IN_POLYLINE(p) (p->GetVertexCount() - (p->GetVertexCount()>1?((*(p->GetLastVertex())) == (*(p->GetFirstVertex()))?1:0):0))

#define DELETE_FLAGGED_ENTITIES(entity_array, flag) { \
	Entity2D *e; \
	for (int i=entity_array.size(); i>0; ) \
		if (entity_array[--i]->GetFlag(flag)) { \
			e = entity_array[i]; \
			DELETE_OBJECT(e); \
			entity_array.removeAt(i); \
		} \
}

#endif
