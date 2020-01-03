#include "Edge.h"

#include "../PDMacros.h"

#include <stdlib.h> // for malloc and free
#include <malloc.h> // for malloc and free

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

using namespace PolygonDetection;

/***
* @desc contructor
*/

Edge::Edge(int id)
{	
	_id = id;	
}


Edge::~Edge()
{		
}
