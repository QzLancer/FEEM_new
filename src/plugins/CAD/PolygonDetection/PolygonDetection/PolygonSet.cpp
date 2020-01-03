#include "./PolygonDetection/PolygonSet.h"

//#include "./PDMacros.h"
#include "./PDConsts.h"

//#include <wx/arrimpl.cpp>
//#include <wx/datetime.h>
#include "./PolygonDetector.h"

#include "../GraphicalPrimitives2D/Color.h"

#include <QtAlgorithms>
#include <QDebug>
#include <algorithm>

using namespace PolygonDetection;

//WX_DEFINE_OBJARRAY(PolygonsArray);

PolygonSet::PolygonSet(void)
{
}

PolygonSet::~PolygonSet(void)
{
    //    Clear();
}

void PolygonSet::Clear(void)
{
    WX_CLEAR_ARRAY(_polygons_array);
}

/***
* @desc simplifies the polygons in this set
* @note removes inclusions and disposes small polygons
*/
void PolygonSet::Simplify(double smaller_polygon_length)
{
    printf("Polygon set simplification\n");

    Polygon * p1, * p2;
    int i,j;
    bool changes = false;

    // remove small polygons
    j=0;
    for (i=_polygons_array.size(); i>0;) {
        p1 = _polygons_array[--i];

        if (p1->GetLength()< smaller_polygon_length )  {
            _polygons_array.removeAt(i);
            wxDELETE(p1);
            j++;
        }
    }

    if(!PolygonDetector::Silent())
        printf("Removed %d small polygons\n", j);

    // check adjacencies
    for (i=0; i<_polygons_array.size();i++) {
        p1 = _polygons_array[i];
        for (j=i+1; j<_polygons_array.size();j++) {
            p2 =  _polygons_array[j];

            // see if p1 and p2 are strictly adjacent
            if (p1->IsAdjacent(p2)) {
                // check if p1 contains p2
                if (p1->Contains(p2)) {
                    changes |= p1->Minus(p2);
                } else {
                    // just when p1 does not contains p2
                    // we need to check if p2 contains p1
                    if (p2->Contains(p1)) {
                        changes |= p2->Minus(p1);
                    }
                }
            }else{
                /** 不相邻的情况，孔 **/
            }
        }
    }
}


// Constructs a polygon set from given line set
bool PolygonDetection::PolygonSet::Construct(LineSet * line_set)
{
    printf("Polygon set construction\n");

    if (!line_set) return false;

    // first we clear the polygons array
    WX_CLEAR_ARRAY(_polygons_array);

    // then we create the graph
    Graph * G = LinesToGraph(line_set);

    if (!PolygonDetection::PolygonDetector::Silent())
        printf("Created graph with %d vertices and %d edges.\n",
               G->GetVertexCount(),
               G->GetEdgeCount());

    if (G->GetVertexCount()>MAX_GRAPH_VERTEX_COUNT) {
        printf("Number of vertices exceeds the maximum allowed. Polygon detection interrupted.\n");
    } else {
        // run the Floyd-Warshall Algorithm
        G->FloydWarshall();
        // run the Horton's Algorithm
        CycleSet * cycle_set = G->Horton();

        if (!cycle_set) {
            printf("Could not find the cycle set produced by Horton algorithm.\n");
        } else {
            printf("Detected %d cycles.\n", cycle_set->size());
            // Convert cycles to polygons
            CyclesToPolygons(cycle_set);

            DELETE_OBJECT(cycle_set);
        }

    }

    wxDELETE(G);

    return true;
}


/***
* @desc fill the points array with all points existing in entities 
*/
void PolygonDetection::PolygonSet::CreatePointsArray(LineSet * line_set)
{

    if (line_set) {
        WX_CLEAR_ARRAY(_all_points_array);
        for (int i=0; i< line_set->size(); i++) {
            Line * line = line_set->Item(i);
            line->CalculateFirstAndLastPoint();

            GraphicalPrimitives2D::Point2D *p = line->GetStartPoint();
            if (p) {
                p->SetOwnerEntity(line);
                p->SetIndex(i);
                _all_points_array.append(p);
            }

            p = line->GetEndPoint();
            if (p) {
                p->SetOwnerEntity(line);
                p->SetIndex(i);
                _all_points_array.append(p);
            }
        }

        // the points are sorted in order to allow fast
        // identification of coincident points
        qSort(_all_points_array.begin(),_all_points_array.end(),GraphicalPrimitives2D::Point2D::CompareOrder);

        // at the end we update the index on all points
        for(int i=0; i<_all_points_array.size();i++)
            (_all_points_array[i])->SetIndex(i);
    }
}

/***
* @desc creates a graph representing the lines of this table
* @return a pointer to a new graph object
* @note IMPORTANT: don't forget to delete the Graph elsewhere
*/
Graph * PolygonSet::LinesToGraph(LineSet * line_set)
{
    printf("Graph construction\n");

    if (!line_set) {
        printf("Unable to compute graph from line set.\n");
        return nullptr;
    }
    // first, create the points array from the current line set
    CreatePointsArray(line_set);

    // then create the graph
    Graph * G = new Graph(GetPointCount());

    // because of using GetPointCount we are sure that all points
    // already have an ID, so we can add lines to the graph

    Line * line;

    for (int i=0; i<line_set->size(); i++ ) {
        line = line_set->Item(i);
        if (line)
            G->SetAdjacency(line->GetStartPoint()->GetID(), line->GetEndPoint()->GetID());
    }

    //ENDING_PROCESS_MESSAGE();
    return G;
}

/***
* @desc determine the number of existing points.
*       this method also sets a non-unique id for each point.
*       this id is shared by all coincident points 
*/
int PolygonSet::GetPointCount()
{
    int id = 0;
    GraphicalPrimitives2D::Point2D * current, * previous = nullptr;

    for (int i=0; i<_all_points_array.size(); i++) {
        current = _all_points_array[i];

        if ((previous && (*current)!=(*previous)) || !previous) {
            id++;
            previous = current;
        }
        current->SetID(id-1);
    }

    return id;
}

/***
* @desc creates polygons from cycles
* @para cycle set
*/
void PolygonSet::CyclesToPolygons(CycleSet *cycle_set)
{
    printf("Cycle to polygon conversion\n");

    if (cycle_set) {
        // then create polygons
        for (int i=0; i<cycle_set->size();i++){
            Cycle * cycle = cycle_set->GetCycle(i);

            if (cycle->GetVertexCount()>2) {
                Polygon * plg = new Polygon();

                for (int j=0; j<cycle->GetVertexCount();j++){
                    GraphicalPrimitives2D::Point2D * p = PointByID(cycle->GetVertex(j));
                    if (p)
                        plg->AddVertex(new GraphicalPrimitives2D::Point2D(p));
                }

                // adds new polygon to polygons array
                _polygons_array.append(plg);

                // update polygon first and last point, plus closed status
                plg->CalculateFirstAndLastPoint();
                // simplify the polygon, removing unnecessary vertices
                // IMPORTANT NOTICE: This should not be called here,
                // because we need all vertices for remove contained polygons
                // with single adjacencies. This simplification is done
                // later, within the polygon set simplification
                // plg->Simplify();
            }
        }
    }
}

/***
* @returns the point with id indicated
*/
GraphicalPrimitives2D::Point2D * PolygonSet::PointByID(int id)
{
    GraphicalPrimitives2D::Point2D *p;

    // note: the position is at least equal to id
    for (int i=id; i<_all_points_array.size();i++) {
        p = _all_points_array[i];
        if (p->GetID()==id)
            return p;
    }

    return nullptr;
}


/***
* @return a string with the SVG containing the polygon set
*/
QString PolygonDetection::PolygonSet::AsSVG(bool colorized)
{
    QString result = "";

    // Add SVG Header
    result+="<?xml version=\"1.0\" standalone=\"no\"?>\n";
    result+="<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n";
    result+="\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";

    result+="<svg width=\"100%%\" height=\"100%%\" viewBox=\"0 0 1.0 1.0\"\n";
    result+="xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n";

    float factor = 1.0f;
    float delta = 0;

    if (_polygons_array.size()>0)
        delta=1.0f/(_polygons_array.size()+1);

    float r, g, b;
    Color::HSVtoRGB(&r,&g,&b, POLYGON_COLOR_H, POLYGON_COLOR_S, POLYGON_COLOR_V);

    // draw polygons
    for (int i=0;i<_polygons_array.size();i++) {
        Polygon * p = Item(i);
        if (colorized)
            Color::HSVtoRGB(&r,&g,&b, (float) factor*POLYGON_COLOR_H, POLYGON_COLOR_S, POLYGON_COLOR_V);
        if (p)
            result += p->AsString(true,"#000000",Color::RGBtoHEX(r,g,b).c_str()) +"\n";
        factor-=delta;
    }

    // draw polylines
    for (int i=0;i<_polygons_array.size();i++) {
        Polygon * p = Item(i);
        if (p)
            result += p->AsString(true,"#000000") +"\n";
        factor-=delta;
    }

    result += "</svg>";
    return result;
}

