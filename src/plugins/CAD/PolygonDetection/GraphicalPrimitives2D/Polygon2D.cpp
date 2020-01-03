#include "Polygon2D.h"
#include "Line2D.h"

#include "./GPMacros.h"
//#include <wx/log.h>

using namespace GraphicalPrimitives2D;

/***
* @desc constructor 
*/
Polygon2D::Polygon2D() : Polyline2D( Entity2D::et_polygon)
{
    Initialize();
}

/***
* @desc constructor 
* @note creates a polygon object based on given polygon
*/
Polygon2D::Polygon2D(Polygon2D *polygon) : 	Polyline2D(Entity2D::et_polygon)
{
	Initialize();
	
	if (polygon) {
        for (int i=0;i<polygon->GetVertexCount();i++) {
			AddVertex(new Point2D(polygon->GetVertexAt(i)));
		}
	}
}

/***
* @desc destructor
*/
Polygon2D::~Polygon2D()
{
}



/***
* @desc initializes the class members
*/
void Polygon2D::Initialize()
{
	_closed=true; 
    _area=0;
	
// 
// 	_is_convex = false;
}


/***
* @desc macro to detect if a ray from <ray_origin> along a test axis,
*     in this case we use a +X axis, crosses the edge defined by the
*     two endpoints <endpoint_1> and <endpoint_2>
*
* @see O'Rourke, Joseph, "Computational Geometry in C, 2nd Ed.", 
*    pp.243, figure 7.8
*
*/
#define RAY_IS_CROSSING_EDGE(ray_origin, endpoint_1, endpoint_2) ( \
	( \
		( \
			endpoint_1->GetY() > ray_origin->GetY() && \
			endpoint_2->GetY() <= ray_origin->GetY() \
		) \
		|| \
		( \
			endpoint_2->GetY() > ray_origin->GetY() && \
			endpoint_1->GetY() <= ray_origin->GetY() \
		) \
	) && \
	(endpoint_1->GetX()+(ray_origin->GetY()-endpoint_1->GetY())/ \
		(endpoint_2->GetY()-endpoint_1->GetY())*(endpoint_2->GetX()-endpoint_1->GetX()) < ray_origin->GetX()) \
)

/***
* @returns true if this is a polygon (closed polyline) and <entity> lays inside 
*/
bool Polygon2D::Contains(Entity2D *entity, bool strict)
{
	if (!entity) return false;
	
	switch(entity->GetType()) {
	case et_polygon:
	case et_polyline:
		return Contains((Polyline2D*)entity, strict);
	case et_line:
		return Contains((Line2D *) entity, strict);
	case et_point:
		return Contains((Point2D *) entity, strict);
	default:
		return false;
	}
}


/***
* @returns true if this is a polygoon (closed polyline) and <point> lays inside 
*
* @see Haines, Eric, "Point in Polygon Strategies", Graphic Gems IV, ed Paul Heckbert,
*    Academic Press, pp.24-46, 1994
*
* @see O'Rourke, Joseph, "Computational Geometry in C, 2nd Ed.", pp.239-245
*/
bool Polygon2D::Contains(Point2D *point, bool strict)
{
	// in case of an open polyline the point cannot be inside
	if (!IsClosed()) return false;

	// first lets see if point is inside the polygon bounding box
    Box2D * bb = GetBoundingBox();
    
    if (!bb) {
//        printf(wxT("Unable to determine bounding box for \'Point in Polygon\' check."));
        return false;
    }
    
	if (!bb->Contains(point)) 
		// if point not inside of bounding box, then we can be sure
		// that point are not inside the polygon
		return false;

	bool inside = false;
    //int vertex_count = _vertex_array.size();
    int vertex_count = VERTEX_COUNT_IN_POLYLINE(this);

	if (vertex_count>0) {
		
		Point2D * current_vertex;
		Point2D * previous_vertex = _vertex_array[VERTEX_COUNT_IN_POLYLINE(this)-1];
		
        for (int i=0; i<vertex_count;i++) {
			current_vertex = _vertex_array[i];
			
			// let's see if point is lays on the edge
			if (point->Between(current_vertex, previous_vertex)) {
				// in this case point is considered INSIDE the polygon
                // or not, depending on strict value
				return !strict;
			}

			if (RAY_IS_CROSSING_EDGE(point, previous_vertex, current_vertex))
				inside = !inside;

			previous_vertex = current_vertex;
		}
	}

	return inside;
}

/***
* @returns true if this is a polygoon (closed polyline) and <polyline> lay inside 
* @note this algorithm runs in O(n*m) where n is the number of vertices of this
*     polygon and m is the number of vertices of the compared polyline
*/
bool Polygon2D::Contains(Polyline2D *polyline, bool strict)
{
	Point2D * current_inner_vertex = nullptr;
	Point2D * previous_inner_vertex = nullptr;
	Point2D * current_outter_vertex = nullptr;
	Point2D * previous_outter_vertex = nullptr;
	Point2D * p;
    int i, outter_vertex_index;
	
	// first lets see if all vertices in polyline lay inside or in the border of the polygon
	for (i=0; i<VERTEX_COUNT_IN_POLYLINE(polyline);i++) {
		current_inner_vertex = polyline->GetVertexAt(i);

		// if any vertex are outside the polygon the the polyline 
		// ar not inside the polygon
		if (!Contains(current_inner_vertex))
			return false;
	}

    // now lets see if all vertices of polyline are conicident with vertices in this polygon
	for (i=0; i<VERTEX_COUNT_IN_POLYLINE(polyline)+1;i++) {
		current_inner_vertex = polyline->GetVertexAt(i%VERTEX_COUNT_IN_POLYLINE(polyline));
        
		// in case any vertex not coincident then it lays inside
		// because we have already tested this before
		if (!HaveVertex(current_inner_vertex, &outter_vertex_index))
            return true;

		current_outter_vertex= GetVertexAt(outter_vertex_index);

        //in case not in first point
        if (previous_outter_vertex && previous_inner_vertex) {
            // if coincident vertices not consecutive in this polygon
			if (!ConsecutiveVertices(current_outter_vertex,previous_outter_vertex))
			{	
				// lets see if middle point of this vertex lays inside polygon
				// start by calculating the middle point of the line segment 
				// with endpoints coincident with the vertices

				// first calculate the displacement of middle 
                double x = (current_inner_vertex->GetX()-previous_inner_vertex->GetX())/2;
                double y = (current_inner_vertex->GetY()-previous_inner_vertex->GetY())/2;                
				
				x+=previous_inner_vertex->GetX();
				y+=previous_inner_vertex->GetY();

                p = new Point2D(x,y);

				// and then test if such point is contained inside the polygon
                if (!Contains(p, strict)) {
                    DELETE_OBJECT(p);
                    return false;
                }
                DELETE_OBJECT(p);
            }
        }
        
        previous_outter_vertex = current_outter_vertex;
		previous_inner_vertex = current_inner_vertex;
    }
	 
	return true;
}

/***
* @returns true if <line> lays inside this polygon
*/
bool Polygon2D::Contains(Line2D *line, bool strict)
{
	if (!line) return false;

	Point2D * p1 = line->GetStartPoint();
	Point2D * p2 = line->GetEndPoint();

	if (Contains(p1, strict) && Contains(p2, strict)){
        int i;
		Line2D * edge;
		bool intersects = false;
		Point2D * current_vertex, * previous_vertex = GetFirstVertex();

		for(i=1;i<VERTEX_COUNT_IN_POLYLINE(this) && !intersects;i++){
			current_vertex = GetVertexAt(i);
			edge = new Line2D(previous_vertex, current_vertex);
			
			intersects |= line->Intersects(edge);

			DELETE_OBJECT(edge);
			previous_vertex = current_vertex;
		}	

		return !intersects;
	}

	return false;
}

/***
* @return true if <polygon> is disjoint of this polygon
* @note this method only works weel if no line segment 
*     intersection exists, i.e.,  if intersection removal 
*     have already been made
*/
bool Polygon2D::Disjoint(Polygon2D *polygon)
{
	// checks if any point of given polygon lays inside (or in 
	// the border) of this polygon
    for (int i=0; i<VERTEX_COUNT_IN_POLYLINE(polygon); i++)
		if (Contains(polygon->GetVertexAt(i)))
			return false;

	// if all points of given polygon are outside this polygon
	// then they are disjoint.
	// Note that no line segment intersection exists.
	return true;
}

/****
* @return true if <p1> is adjacent to <p2>, false otherwise 
* @param p1, p2 pointers to polylines
* @param strict true quest for strictly adjacent polygons, if false
*      considers adjacent two polygons that share only one vertice
* @note two polygons are strictly adjacent if they share at least an edge
*/

bool Polygon2D::IsAdjacent(Polygon2D *p1, Polygon2D *p2, bool strict)
{

    int i, j;
	Point2D *v1, *v2;
	Point2D *previous_v1 = p1->GetLastVertex();
	Point2D *previous_v2 = p2->GetLastVertex();
	Line2D *line1, *line2;

	for (i=0; i<VERTEX_COUNT_IN_POLYLINE(p1);i++) {
		v1 = p1->GetVertexAt(i);

		line1 = new Line2D(previous_v1, v1);
		
		for (j=0; j<VERTEX_COUNT_IN_POLYLINE(p2);j++) {
			v2 = p2->GetVertexAt(j);
			line2 = new Line2D(previous_v2, v2);

			if ((strict?Line2D::StrictOverlapping(line1, line2):Line2D::Overlapping(line1, line2))) {
				DELETE_OBJECT(line1);
				DELETE_OBJECT(line2);
				return true;
            }
            DELETE_OBJECT(line2);
			previous_v2 = v2;
		}
		DELETE_OBJECT(line1);
		previous_v1 = v1;
	}

	return false;

	
}

/****
* @return true if <p1> have single adjacency with <p2>, false otherwise 
* @param p1, p2 pointers to polygons
* @param i, j pointers to the indices of first overlapped edges
* @param length pointer to the number of overlapped edges. Signal represents
*        the order of adjacent edges in p2 (+/-)
* @note two polylines have single adjacency if they share at least one edge 
*       and all edges they share are consecutive in both polygons
*/
bool Polygon2D::SingleAdjacency(Polygon2D *p1, Polygon2D *p2, int *i, int* j, long *length)
{
    int n1, n2;
	(*length) = 0;

	// in case p1 and p2 have not common vertices then they cannot have single adjacency	
	if (!HaveCommonVertex(p1,p2, &n1, &n2))
		return false;

	(*i)=n1;
	(*j)=n2;
	(*length)++;

	// in case n1 is the last vertex in p1 it is not a simple adjacency
	if (n1==VERTEX_COUNT_IN_POLYLINE(p1))
		return false;

	enum {
		adjacency,
		no_adjacency
	} status = adjacency;

    int index, triggering_counter = 0;
	short increment = 0;
	Point2D *v1, *v2;

	// lets calculate the increment
	// note that the order of this conditions is relevant,
	// because we need to check first the cases on which 
	// n1 is increasing
	if ((*p1->GetVertexAt(n1,1))==(*p2->GetVertexAt(n2,1))) {
		increment = 1;
	} else {
		if ((*p1->GetVertexAt(n1,1))==(*p2->GetVertexAt(n2,-1))) {
			increment = -1;
		} else {
			if ((*p1->GetVertexAt(n1,-1))==(*p2->GetVertexAt(n2,-1))) {
				increment = 1;
			} else {
				if ((*p1->GetVertexAt(n1,-1))==(*p2->GetVertexAt(n2,1))) {
					increment = -1;
				} else 
					// if none of the above happens, then this is not a simple adjacency
					return false;
			}
		}
	}
	
	// sweep remaining vertices of p1 (note that last vertex equals the first)
	for (n1++;n1<p1->GetVertexCount()-1;n1++) {
		v1 = p1->GetVertexAt(n1);

		// in an adjacency status
		if (status==adjacency)
			// lets increment iterator for <p2> (forward or backward)
			// note that last vertex is the same than the first, so we have to 
			// jump from first vertex to the one before the last
			STEP_ITERATOR(n2,increment, VERTEX_COUNT_IN_POLYLINE(p2));		
		// otherwise keep n2 unchanged
		
		// lets update vertex <v2> 
		v2 = p2->GetVertexAt(n2);
		
		// check if vertices are common
		if ((*v1)==(*v2)) {
			// in case of coincident vertices
			if (status==no_adjacency) 
				// lets trigger status
				TRIGGER(status, adjacency, triggering_counter);
			(*length)++;
		} else {
			// in case of different vertices
			if (status==adjacency) 
				TRIGGER(status, no_adjacency, triggering_counter);
			
			// lets see if this vertex of <p1> is a vertex of <p2>
			if (p2->HaveVertex(v1, &index)){
				// in this case status must change and trigger counter must advance
				TRIGGER(status, adjacency, triggering_counter);
				
				// and <n2> must jump to index of common vertex in <p2>
				n2 = index;

				// now the first common vertices must change
				(*i) = n1;
				(*j) = n2;

				// increment the counter of common vertices
				(*length)++;
			}
		}		
	}

	// gives a sign to length, to know the order of adjacent edges in p2
	(*length) *= increment;

	// returns true if status has only been triggered at os two times
	return (triggering_counter<=2);
}



/***
* @desc simplifies current polygon, subtracting <p>, in case there are
*       an single relationship between them
* @return true if polygon were changed, false otherwise
*/
bool Polygon2D::Minus(Polygon2D *p)
{
    int i, j;
	long l;
	
	// in cases different than single adjacency, do nothing
	// other reason for this call is to determine 
	// first overlapping vertices, with indices i and j
	// and the length of the adjacency
	if (!SingleAdjacency(this, p, &i, &j, &l))
		return false;

	long n;
    int m=i;
	Point2D *v;	
	bool changes = false;
	
    // in case the first or last vertices are coincident, we need to
	// remove one of them now (in this case we remove the last vertex)
    if ((*GetFirstVertex())==(*GetLastVertex())) {
		v = GetLastVertex();
		DELETE_OBJECT(v);
        _vertex_array.removeAt(_vertex_array.size()-1);
	}

	// now lets reset remove flag from all vertices
    for (n=0;n<GetVertexCount();n++)
		_vertex_array[n]->ResetFlag(FLAG_REMOVE);
	
	// then lets flag vertices for removal from polygon
	for (n=0;n<abs(l)-2;n++) {	
		// advance index to next position
		STEP_ITERATOR(m, 1, GetVertexCount());

        // flag the vertex for removal
		v = _vertex_array[m];		
		v->SetFlag(FLAG_REMOVE);
        
        // in case of removal of vertices before <i> one must update <i>
        if (m<=i) i--;

		// if we are here than something changed in polygon
		changes |= true;
	}

	// and remove the vertices from the list and delete the points
	DELETE_FLAGGED_ENTITIES(_vertex_array, FLAG_REMOVE);
		
	// and now lets add the new ones
    m = i;    
    for (n=0;n< VERTEX_COUNT_IN_POLYLINE(p)-abs(l);n++) {
        STEP_ITERATOR(j, (l>0?-1:1), VERTEX_COUNT_IN_POLYLINE(p));
		v = p->GetVertexAt(j);
        
        
        STEP_ITERATOR(m, 1, GetVertexCount());
        _vertex_array.insert(m,new Point2D(v));
        
		// if we are here than something changed in polygon
		changes |= true;
	}

	// now we need to reconstruct the polygon
	if (((*GetFirstVertex())!=(*GetLastVertex())))		
        _vertex_array.append(new Point2D(GetFirstVertex()));

	// in case there were changes, lets recalculate the axis aligned bounding box
	if (changes) {		
		RecalculateBoundingBox();
	}

	return changes;
}


/***
* @return true if vertices <v1> and <v2> belongs to this polygon and are consecutive
*/
bool Polygon2D::ConsecutiveVertices(Point2D *v1, Point2D *v2, short * index_increment )
{
	// if any vertex are undefined, then they cannot be consecutive
	if (!v1 || !v2)
		return false;

    int index_v1, index_v2;

	// if any vertex does not exist in this polygonm then
	// they cannot be consecutive
	if (!HaveVertex(v1,&index_v1) || 
		!HaveVertex(v2,&index_v2))
		return false;

	// see if <v2> is next vertex
	if (((index_v1+1)%(VERTEX_COUNT_IN_POLYLINE(this)))==index_v2) {
		if (index_increment)
			(*index_increment)=1;
		return true;
	}

	// see if <v2> is previous vertex
	if (((index_v1-1)%(VERTEX_COUNT_IN_POLYLINE(this)))==index_v2) {
		if (index_increment)
			(*index_increment)=-1;
		return true;
	}

	return false;	
}

