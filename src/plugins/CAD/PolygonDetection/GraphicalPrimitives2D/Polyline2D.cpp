#include "Polyline2D.h"
#include "Polygon2D.h"
#include "Line2D.h"
#include "Point2D.h"
#include "./GPMacros.h"

#include <math.h> // because of sqrt

using namespace GraphicalPrimitives2D;

/***
* @desc constructor 
*/
Polyline2D::Polyline2D() : Entity2D(Entity2D::et_polyline)
{
    _closed=false;
    _length=0;
    _p_bounding_box = nullptr;
    CalculateFirstAndLastPoint();

}

/***
* @desc constructor 
*/
Polyline2D::Polyline2D(entity_type type ) : 
    Entity2D(type)
{
    _length = 0;
    _p_bounding_box = nullptr;
    CalculateFirstAndLastPoint();
}

/***
* @desc constructor 
*/
Polyline2D::Polyline2D(Line2D * line ) : 
    Entity2D(Entity2D::et_polyline)
{
    _closed = false;
    _length = 0;
    _p_bounding_box = nullptr;

    if (line) {
        AddVertex(new Point2D(line->GetStartPoint()));
        AddVertex(new Point2D(line->GetEndPoint()));
    }

    CalculateFirstAndLastPoint();
}

/***
* @desc constructor 
* @note duplicates the polylines (including all verteices)
*/
Polyline2D::Polyline2D(Polyline2D * polyline ) : 
    Entity2D(Entity2D::et_polyline)
{
    _closed = false;
    _length = 0;
    _p_bounding_box = nullptr;

    if (polyline)
        for (int i=0; i<polyline->GetVertexCount();i++)
            AddVertex(new Point2D(polyline->GetVertexAt(i)));

    CalculateFirstAndLastPoint();
}



/***
* @desc destructor
*/
Polyline2D::~Polyline2D()
{	
    DELETE_OBJECT(_p_bounding_box);
    WX_CLEAR_ARRAY(_vertex_array);
    _vertex_array.clear();
}

/***
* @desc adds a vertex to the polyline
* @param point representing a vertex
* @note will be stored a pointer to the point passed on
*       a vertex list, but this class DELETES the point
*/
bool Polyline2D::AddVertex(Point2D *vertex, short flag, int pos)
{
    if (vertex) {

        // check if in case of middle insertion the position given is
        // at the begin or at the end of the polyline
        if CHECK_FLAG(flag, AT_MIDDLE)  {
            if (pos>=_vertex_array.size())
                flag = AT_END;

            if (pos==0u)
                flag = AT_BEGIN;
        }

        if (_vertex_array.size() >0) {

            // calculates the length of the line if vertex added at begin or end
            if (CHECK_FLAG(flag,AT_END)||CHECK_FLAG(flag,AT_BEGIN)) {
                Point2D * previous = CHECK_FLAG(flag,AT_END)?_vertex_array.last():_vertex_array[0];

                if (previous)
                    _length += previous->DistanceTo(vertex);
            }

            if (CHECK_FLAG(flag,AT_MIDDLE)) {
                Point2D * previous = _vertex_array[pos-1];
                Point2D * next = _vertex_array[pos];

                if (previous && next) {
                    _length -= previous->DistanceTo(next);
                    _length += vertex->DistanceTo(previous);
                    _length += vertex->DistanceTo(next);
                }
            }

        }
        vertex->SetOwnerEntity(this);

        if CHECK_FLAG(flag, AT_END)
                _vertex_array.append(vertex);

        if CHECK_FLAG(flag, AT_BEGIN)
                _vertex_array.insert(0,vertex);

        if CHECK_FLAG(flag, AT_MIDDLE)
                _vertex_array.insert(pos,vertex);

        // when a vertex is added it will be needed to recalculate the
        // bounding box
        DELETE_OBJECT( _p_bounding_box );
        return true;
    }

    return false;
}

/***
* @desc calculate the bounding box of this polyline
*/
void Polyline2D::CalculateBoundingBox()
{

    // if bounding box already exists it will not calculate
    if (_p_bounding_box)
        return;

    // a bounding box must have more than two vertices
    if (_vertex_array.size()<2)
        return;

    double min_x=0, max_x=0, x;
    double min_y=0, max_y=0, y;
    Point2D *vertex;
    bool first=true;

    for (int i=0; i<_vertex_array.size(); i++)
    {
        vertex = _vertex_array[i];

        x=vertex->GetX();
        y=vertex->GetY();

        if (first) {
            first = false;
            min_x=max_x=x;
            min_y=max_y=y;
        } else {
            min_x=MIN(min_x,x);
            min_y=MIN(min_y,y);

            max_x=MAX(max_x,x);
            max_y=MAX(max_y,y);
        }
    }

    DELETE_OBJECT(_p_bounding_box)

            Point2D start_point(min_x, min_y);

    _p_bounding_box = new Box2D(
                start_point,
                Vector2D(start_point, max_x-min_x, 0),
                Vector2D(start_point, 0, max_y-min_y)
                );
}



/***
* @desc calculate the first and last point of this polyline
*/
void Polyline2D::CalculateFirstAndLastPoint()
{
    // if there are only one vertex it is not a polyline
    if (_vertex_array.size()<2){
        if (_vertex_array.size()>0){
            SetFirstPoint(_vertex_array[0]);
            SetLastPoint(_vertex_array[0]);
        }
        return;
    }

    // let's see first if the polyline is closed, ie. is a polygon
    _closed |= (((Point2D) (*_vertex_array[0])) == ((Point2D)(*_vertex_array.last())));

    if (_closed) {
        // the case of the closed polyline
        // here we're going to find the first point by seeing them all
        Point2D *vertex=nullptr, *first_vertex=_vertex_array[0];


        for (int i=1; i<_vertex_array.size(); i++)
        {
            vertex = _vertex_array[i];

            if (!Point2D::Ordered(first_vertex,vertex))
                first_vertex = vertex;

        }

        if (first_vertex) {
            SetFirstPoint(first_vertex);
            // in a closed polyline the first and last point coincide
            SetLastPoint(vertex);
        }

    } else {
        // case the polyline is not closed, just consider the
        // extremities
        SetFirstPoint(_vertex_array[0]);
        SetLastPoint(_vertex_array.last());
    }
}

/***
* @return true if extremities of polylines are coincident, false otherwise
*/
// bool Polyline2D::CoincidentExtremities(Polyline2D *polyline1, Polyline2D *polyline2)
// {
// 	Point2D *p1f = polyline1->GetFirstVertex();
// 	Point2D *p2f = polyline2->GetFirstVertex();
// 	Point2D *p1l = polyline1->GetLastVertex();
// 	Point2D *p2l = polyline2->GetLastVertex();
// 	
// 	return (((*p1f)==(*p2f) && (*p1l)==(p2l)) || ((*p1f)==(*p2l) && (*p1l)==(p2f)));
// }

/***
* @param pointer to point
* @return pointer to the opposite point of the one passed 
*         or nullptr if point passed don't belong to polyline
*/
Point2D * Polyline2D::GetOtherPoint(Point2D *p)
{
    if (_vertex_array.size()<2)
        return nullptr;

    if ((*p)==(*GetFirstVertex()))
        return GetLastVertex();

    if ((*p)==(*GetLastVertex()))
        return GetFirstVertex();

    return nullptr;
}

Point2D * Polyline2D::PointAt(double x, double y)
{
    if (x == GetFirstVertex()->GetX() && y == GetFirstVertex()->GetY()) {
        return GetFirstVertex();
    }

    if (x == GetLastVertex()->GetX() && y == GetLastVertex()->GetY()) {
        return GetLastVertex();
    }

    return nullptr;
}

/***
* @desc this method adds a polyline to this one
* @param polyline to add
*/
void Polyline2D::AddPolyline(Polyline2D *pl)
{
    // if pl is not defined does nothing
    if (!pl)
        return;

    // forces first and last point calculations
    pl->CalculateFirstAndLastPoint();
    CalculateFirstAndLastPoint();

    // simple cases
    if (_vertex_array.size()==0) {
        ExecuteJoin(pl);
        return;
    }

    if (pl->_vertex_array.size()==0)
        return;

    Point2D * this_polyline_first_vertex = GetFirstVertex();
    Point2D * other_polyline_first_vertex = pl->GetFirstVertex();

    Point2D * this_polyline_last_vertex = GetLastVertex();
    Point2D * other_polyline_last_vertex = pl->GetLastVertex();

    // NOTE: the case of coincident extremities is treated by 'ExecuteJoin()'

    if ( (*this_polyline_last_vertex)==(*other_polyline_first_vertex)){
        ExecuteJoin(pl, NORMAL_ORDER | AT_END);
        return;
    }
    
    if ( (*this_polyline_first_vertex)== (*other_polyline_last_vertex)){
        ExecuteJoin(pl, NORMAL_ORDER | AT_BEGIN);
        return;
    }

    if ( (*this_polyline_last_vertex)==(*other_polyline_last_vertex) ){
        ExecuteJoin(pl, INVERSE_ORDER | AT_END);
        return;
    }

    if ( (*this_polyline_first_vertex)==(*other_polyline_first_vertex)){
        ExecuteJoin(pl, INVERSE_ORDER | AT_BEGIN);
        return;
    }
}


/***
* @return a pointer to a newly created polyline representing the join of the
*         polylines passed in teh argment
*/
Polyline2D * Polyline2D::Join(Polyline2D *polyline1, Polyline2D *polyline2)
{
    if (!polyline1 || !polyline2)
        return nullptr;

    Polyline2D * pl = new Polyline2D();

    pl->AddPolyline(polyline1);
    pl->AddPolyline(polyline2);

    return pl;
}


void Polyline2D::ExecuteJoin(Polyline2D *pl, short flags)
{
    Point2D * p;
    int i = 0, count = pl->GetVertexCount();

    
    // skips the first vertex, if necessary
    if (pl->GetVertexCount()>0 && GetVertexCount()>0) {
        if (CHECK_FLAG(flags, INVERSE_ORDER)) {
            if ( ((*(pl->GetLastVertex())) == (*GetLastVertex())) || ((*(pl->GetFirstVertex())) == (*GetFirstVertex())))
                i++;
        } else {
            if (((*(pl->GetFirstVertex())) == (*GetLastVertex())) || ((*(pl->GetLastVertex())) == (*GetFirstVertex())))
                i++;
        }
    }

    for( ; i<count; i++)
        if (CHECK_FLAG(flags, AT_END)) {
            p = new Point2D(pl->_vertex_array[CHECK_FLAG(flags, INVERSE_ORDER)?count-i-1:i]);
            AddVertex(p, AT_END);
        } else
            if (CHECK_FLAG(flags, AT_BEGIN)){
                p = new Point2D(pl->_vertex_array[CHECK_FLAG(flags, INVERSE_ORDER)?i:count-i-1]);
                AddVertex(p, AT_BEGIN);
            }

    // recalculates the first and last point
    CalculateFirstAndLastPoint();

}

/***
* @desc perform rounding in polyline vertices coordinates
*/
void Polyline2D::PerformRounding(double gamma)
{
    Point2D * p;

    for (int i=0; i<_vertex_array.size();i++) {
        p = _vertex_array[i];
        p->PerformRounding(gamma);
    }
}

/***
* @desc removes unnecessary vertices from polyline, e.g. any number of collinear vertices
*/
void Polyline2D::Simplify()
{
    int vertex_count = _vertex_array.size();

    // simplify just makes sense when the polyline have more than two vertices
    if (vertex_count>2) {

        int p1_index = IsClosed()?vertex_count-2:0;
        int p2_index = p1_index+1;

        Point2D * point;

        for (int p3_index=IsClosed()?0:2;p3_index<vertex_count; p3_index++) {

            // see if three points are collinear
            if (_vertex_array[p3_index]->Collinear(_vertex_array[p1_index],_vertex_array[p2_index])) {

                // in case they were, remove the middle one
                point = _vertex_array[p2_index];
                _vertex_array.removeAt(p2_index);
                DELETE_OBJECT(point);
                vertex_count--;

                if (p2_index<p3_index) p3_index--;
                if (p2_index<p1_index) p1_index--;
                
            } else {
                p1_index = p2_index;
            }
            p2_index = p3_index;
        }
    }
}

/***
* @desc performs vertext reduction, according to a given tolerance
* @note executes in O(n) time
*/
void Polyline2D::VertexReduction(double tolerance)
{

    double squared_tolerance = SQR(tolerance);

    Point2D * current_vertex;
    Point2D * previous_vertex=nullptr;
    int n, count = _vertex_array.size();

    // checks if polyline is not empty
    if (count>0) {
        previous_vertex = _vertex_array[count-1];

        // starts from second vertex
        for (int i=1; i<count-1; i++) {
            n = count-i-1;
            current_vertex = _vertex_array[n];

            // see if consecutive points are clustered too closely
            if (previous_vertex->SquareDistanceTo(current_vertex)<squared_tolerance) {
                // remove unnecessary vertices
                _vertex_array.removeAt(n);
                DELETE_OBJECT(current_vertex);
            } else
                previous_vertex = current_vertex;
        }
    }
}

/***
* @desc performs a polyline simplification, using the Douglas-Peucker algorithm
* @see David Douglas and Thomas Peucker "Algorithms for the reduction of the number 
*    of points required to represent a digitized line or its caricature", The 
*    Canadian Cartographer 10(2), pp. 112-122 (1973)
*/
void Polyline2D::DouglasPeucker(double tolerance, int start_index, int end_index)
{
    // see if there are vertices in between that can be used in simplification
    if (start_index>=end_index)
        // nothing else to simplify: stop recursion
        return;

    if (end_index>=_vertex_array.size())
        // wrong indices
        return;

    // lets start by finding the farthest point from line segment
    double maximum_distance=0;
    double current_distance=0;
    int maximum_index = start_index+1;

    // sweep all points...
    for (int i=start_index+1; i<end_index; i++) {
        current_distance = Line2D::Distance(
                    GetVertexAt(start_index),
                    GetVertexAt(end_index),
                    GetVertexAt(i));

        if (current_distance>maximum_distance) {
            maximum_distance = current_distance;
            maximum_index = i;
        }
    }

    // and here we have the index of the farthest point and its distance to
    // selected line segment

    // now lets see if the distance is bigger than tolerance
    if (maximum_distance>tolerance) {

        // in this case lets split the polyline at the farthest vertex
        DouglasPeucker(tolerance, start_index, maximum_index);
        DouglasPeucker(tolerance, maximum_index, end_index);

        // flag the vertex to avoid later removal
        GetVertexAt(maximum_index)->SetFlag(FLAG_KEEP);

    }

}

/***
* @desc performs the polyline simplification, with <tolerance>
*/
void Polyline2D::Simplify(double tolerance)
{	

    DouglasPeucker(tolerance, 0, _vertex_array.size()-1);

    Point2D * vertex;

    // flags first and last vertex
    //vertex = GetFirstVertex();
    //if (vertex) vertex->SetFlag(FLAG_KEEP);

    //vertex = GetLastVertex();
    //if (vertex) vertex->SetFlag(FLAG_KEEP);

    // if the vertex array have more than two vertices
    if (_vertex_array.size()>2)
        // removes unflagged vertices
        for (int i=_vertex_array.size()-2; i>0;i--)
            //--i;
            if (!_vertex_array[i]->GetFlag(FLAG_KEEP)) {
                vertex = _vertex_array[i];
                _vertex_array.removeAt(i);
                DELETE_OBJECT(vertex);
            }
}

/***
* @return true if polylines have a common vertex, false otherwise
* @param p1, p2 pointers to polylines
* @param i, j pointers to the indices of first common vertices found
*/
bool Polyline2D::HaveCommonVertex(Polyline2D *p1, Polyline2D *p2, int *i, int *j)
{
    // check if indices are defined
    if (!i || !j)
        return false;

    Point2D *v;

    // sweeps all vertices in p1
    for ((*i)=0; (*i)<VERTEX_COUNT_IN_POLYLINE(p1);(*i)++) {
        v = p1->GetVertexAt(*i);
        // see if current vertex of p1 is a vertex in p2
        if (p2->HaveVertex(v, j))
            // if it is we have a common vertex
            return true;
    }

    return false;
}


/***
* @param p pointer to a point
* @param index index of point if it is a vertex of this polyline
* @return true if p is a vertex of this polyline, false otherwise
*/
bool Polyline2D::HaveVertex(Point2D *p, int *index)
{
    Point2D * v;
    // sweeps all vertices of polyline
    for (int i=0; i<VERTEX_COUNT_IN_POLYLINE(this);i++) {
        v = GetVertexAt(i);
        // see if point <p> is coincident with current vertex
        if ((*p)==(*(v))) {
            // in case index have been passed, updates its value
            if (index)
                (*index)=i;
            return true;
        }
    }

    return false;
}


/***
* @return pointer to vertex in position <index>+<offset> 
* @note this works as a circular buffer of vertices, when reached 
*       the end it jumps to the beggining and vice-versa
*/
Point2D * Polyline2D::GetVertexAt(int index, short offset)
{
    if (GetVertexCount()<1)
        return nullptr;

    STEP_ITERATOR(index, offset,VERTEX_COUNT_IN_POLYLINE(this));

    return GetVertexAt(index);
}


/***
* @desc performs a scale transformation on this polyline
* @param x component of the scale
* @param y component of the scale
*/
void Polyline2D::Scale(double sx, double sy)
{
    for (int i=0; i<_vertex_array.size();i++)
        _vertex_array[i]->Scale(sx,sy);

    // in case of unioform scale
    if (sx==sy)
        _length *= sx;
    else {
        // lets re-calculate length
        RecalculateLength();
    }
}

/***
* @desc performs a translation transformation on this polyline
* @param x component of the translation
* @param y component of the translation
*/
void Polyline2D::Translate(double dx, double dy)
{
    for (int i=0; i<_vertex_array.size();i++)
        _vertex_array[i]->Translate(dx,dy);
}

/***
* @desc performs a rotation transformation on this polyline
* @param theta component of the translation
*/
void Polyline2D::Rotate(double theta)
{
    for (int i=0; i<_vertex_array.size();i++)
        _vertex_array[i]->Rotate(theta);
}

/***
* @desc recalculates the length of the polyline
*/
void Polyline2D::RecalculateLength()
{
    _length = 0;
    Point2D *current, *previous=nullptr;

    // sweeps all points of polyline
    for (int i=0;i<_vertex_array.size();i++){
        current = _vertex_array[i];
        if (previous)
            _length+=current->DistanceTo(previous);
        previous = current;
    }
}

/***
* @return string containing polylines coordinates
*/
QString Polyline2D::AsString(bool svg_format, const QString & stroke_color, const QString & fill_color)
{
    Point2D * vertex;
    QString result;

    // checks format
    if (svg_format) {
        // adds svg polyline entity tag
        result+=("<polyline fill=\""+fill_color+"\" stroke=\""+stroke_color+"\" stroke-width=\"0.002\"\n");
        result+=("points=\"");
    }

    for (int i=0; i<GetVertexCount(); i++){
        vertex = GetVertexAt(i);
        QString format;
        if(svg_format)
            format=QString("%1,%2 ").arg(vertex->GetX()).arg(vertex->GetY()) ;
        else
            format=QString("%1\t%2\t").arg(vertex->GetX()).arg(vertex->GetY());
        result += format;
    }

    // checks format
    if (svg_format) {
        // adds svg polyline entity tag end symbol
        result+=("\"/>");
    }

    // adds the new line indicating the end of the polyline
    result += ("\n");

    return result;
}

/***
* @return number of time polyline intersects itself
*/
int Polyline2D::Intersections()
{
    int i, j;
    int counter=0;
    Line2D * line_i, * line_j;

    for (i=0; i<GetVertexCount()-2;i++){
        line_i = new Line2D(GetVertexAt(i), GetVertexAt(i+1));
        for (j=i+1; j<GetVertexCount()-1;j++) {
            line_j = new Line2D(GetVertexAt(j), GetVertexAt(j+1));

            if (line_i->IntersectsProper(line_j))
                counter++;

            DELETE_OBJECT(line_j);
        }
        DELETE_OBJECT(line_i);
    }

    return counter;
}

/***
* @returns the shorter distance between given point and this polyline
*/
double Polyline2D::DistanceTo(Point2D *point, Point2D *nearest_point, int * pred, int * succ)
{
    if (!point)
        return false;

    double shorter_distance = -1.0;
    double distance;

    Point2D * previous_vertex = GetFirstVertex();
    Point2D * current_vertex;
    Point2D auxiliar_point;

    for (int i=1; i<GetVertexCount(); i++) {
        current_vertex = GetVertexAt(i);
        distance = Line2D::Distance(previous_vertex, current_vertex, point, nearest_point?&auxiliar_point:nullptr);
        if (distance<=shorter_distance || shorter_distance<0){
            if (nearest_point) (*nearest_point)=auxiliar_point;
            if (pred) (*pred) = i-1;
            if (succ) (*succ) = i;
            shorter_distance = distance;
        }

        previous_vertex = current_vertex;
    }

    return shorter_distance;
}

/***
* @return a point at a distance of <lenght> in the extension of one of the extremities
* @see file ../../Documentation/line_extension.tif
*
* @note do not forget to delete returned point elsewhere
*/
Point2D * Polyline2D::Extension(double length, short flag)
{
    Point2D * u, * v;

    // if no valid flag given
    if (!CHECK_FLAG(flag, AT_END) && !CHECK_FLAG(flag,AT_BEGIN))
        return nullptr;

    // if don't exist more than two vertices
    if (GetVertexCount()<2)
        return nullptr;

    if (CHECK_FLAG(flag, AT_END)) {
        u = GetLastVertex();
        v = GetVertexAt(GetVertexCount()-2);
    } else {
        u = GetFirstVertex();
        v = GetVertexAt(1);
    }

    double x = u->GetX()-v->GetX();
    double y = u->GetY()-v->GetY();

    double l = sqrt(SQR(x)+SQR(y));

    /* to avoid div/0 */
    if (l==0)
        return nullptr;

    double ext_x = x*length/l;
    double ext_y = y*length/l;

    return new Point2D(u->GetX()+ext_x, u->GetY()+ext_y);
}

/***
* @desc indicates if polyline intersects line
* @param proper indicates if is a proper intersection or not
* @note a proper intersection occurs when two segments intersects at a point 
*      interior to both
*/
bool Polyline2D::Intersects(Line2D *line, bool proper)
{
    Point2D * previous_vertex = nullptr;
    Point2D * current_vertex = nullptr;

    bool intersects;

    //	bool (*fn) (Line2D*);
    //
    //	if (proper)
    //		fn = &Line2D::IntersectsProper;
    //	else
    //		fn = &Line2D::Intersects;

    // sweeps all vertices in polyline
    for (int i=0; i<VERTEX_COUNT_IN_POLYLINE(this);i++) {
        current_vertex = GetVertexAt(i);
        if (previous_vertex) {
            Line2D aux_line(previous_vertex, current_vertex);

            //			if (fn(&line))
            //				return true;

            if (proper)
                intersects = aux_line.IntersectsProper(line);
            else
                intersects = aux_line.Intersects(line);

            if (intersects)
                return true;
        }
        previous_vertex = current_vertex;
    }

    return false;
}


/***
* @desc indicates if <polyline> intersects this polyline
*/
bool Polyline2D::Intersects(Polyline2D *polyline)
{
    if (!polyline) return false;



    bool intersects=false;
    Line2D * edge;

    Point2D * current_vertex = nullptr;
    Point2D * previous_vertex = polyline->GetFirstVertex();

    for (int i=1; i<polyline->GetVertexCount() && !intersects;i++) {
        current_vertex = polyline->GetVertexAt(i);
        edge = new Line2D(previous_vertex, current_vertex);

        intersects |= Intersects(edge);

        previous_vertex = current_vertex;
        DELETE_OBJECT(edge);
    }

    return intersects;
}


/***
* @returns true if <entity> intersects this polyline
*/
bool Polyline2D::Intersects(Entity2D *entity)
{	
    if (!entity) return false;

    switch(entity->GetType()) {
    case et_polygon:
    case et_polyline:
        return Intersects((Polyline2D*) entity);
    case et_line:
        return Intersects((Line2D *) entity);
    default:
        return false;
    }
}


/***
* @return list of intersection points between <line> and this polyline
* @note do not forget to delete the array and the intersection points elsewhere
*/
PointArray * Polyline2D::IntersectionPoints(Line2D *line, wxArrayInt * indexes)
{
    PointArray * intersections = new PointArray();

    Point2D * previous_vertex = nullptr;
    Point2D * current_vertex = nullptr;

    // sweeps all vertices in polyline
    for (int i=0; i<VERTEX_COUNT_IN_POLYLINE(this);i++) {
        current_vertex = GetVertexAt(i);

        if (previous_vertex) {
            Line2D aux_line(previous_vertex, current_vertex);
            if (aux_line.Intersects(line)){
                Point2D * intersection = aux_line.IntersectionPoint(line);

                if (intersection) {
                    intersections->append(intersection);
                    if (indexes)
                        indexes->append(i);
                }
            }
        }

        previous_vertex = current_vertex;
    }

    return intersections;
}

/***
* @return a string with the text entry of this polygon on the output file
*/
// QString Polyline2D::GetGeometricFeatures()
// {
// 	QString result="";
// 	int i;
// 
// 	float * fvector = GetGeometricFeaturesVector();
// 	
// 	// writes the dimension of the vector and the id of the polygon
// 	result += QString::Format("%d\n%d", (int) fvector[0], GetID());
// 
// 	// writes the vector on the string
// 	for (i=1;i<=fvector	[0];i++) 
// 		result+=QString::Format(" %f", fvector[i]);
// 
// 	FREE(fvector);
// 
// 	return result;
// }
// 
/***
* @return a vector with the features of this polyline
* @note do not forget to delete returned pointer
*/
// float * Polyline2D::GetGeometricFeaturesVector()
// {
// 	int i, vector_length;
// 	Point2D * vertex;	
// 	float *fvector, *fresult;
// 	Geometry g;
// 
// 	// creates a scribble with the polyline
// 	g.newScribble();
// 	g.newStroke();
// 	for (i=0; i<VERTEX_COUNT_IN_POLYLINE(this);i++) {
// 		vertex = GetVertexAt(i);
// 		g.addPoint(vertex->GetX(), vertex->GetY());
// 	}
// 
// 	// Add the first vertex at the end of the scribble
// 	vertex = GetVertexAt(0);
// 	g.addPoint(vertex->GetX(), vertex->GetY());
// 
// 	// retrieves the geometric features of thatt scribble
// 	// parameter must be true in order to be according SBR
// 	fvector = g.geometricFeatures(true);
// 	vector_length = fvector[0]+1;
// 	fresult= (float *)malloc(vector_length*sizeof(float));	
// 	memcpy(fresult, fvector, (fvector[0]+1)*sizeof(float));
// 
// 	return fresult;
// }

/***
* @return polyline representing the convex-hull of this polyline
*/
// Polygon2D * Polyline2D::GetConvexHull()
// {
// 	CIScribble * scribble = new CIScribble();
// 	CIStroke * stroke = new CIStroke();
// 	Point2D *vertex;
// 	int i;
// 
// 	for (i=0; i<VERTEX_COUNT_IN_POLYLINE(this);i++) {
// 		vertex = GetVertexAt(i);
// 		stroke->addPoint(vertex->GetX(), vertex->GetY());
// 	}
// 
// 	scribble->addStroke(stroke);
// 
// 	CIPolygon * polygon = scribble->convexHull();
// 	
// 	Polygon2D * polygon2D = new Polygon2D(polygon);
// 	polygon2D->SetConvex(true);
// 
// 	DELETE_OBJECT(scribble);
// 
// 	return polygon2D;
// }
