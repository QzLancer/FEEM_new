#include ".\LineSet.h"

//#include <wx/arrimpl.cpp>
//#include <wx/datetime.h>
#include <math.h>

#include "../GraphicalPrimitives2D/GPMacros.h"
// #include "../GraphicalPrimitives2D/GPConsts.h"

#include "./PDMacros.h"
#include "./PDConsts.h"

#include "./PolygonDetector.h"

#include <QtAlgorithms>
#include <QDebug>

/************************************************************************/
/* Local Macro to help creating a new line segment between two lines    */
/*       and add it to a lines list                                     */
/* @note this macro is undefined at the end of this file                */
/************************************************************************/
#define ADD_NEW_SEGMENT(lines_list, p1, p2) { \
    if (!((*p1)==(*p2))) lines_list.append(new Line(p1, p2)); \
    }


using namespace PolygonDetection;

//WX_DEFINE_OBJARRAY(LinesArray);

/************************************************************************/
/* Construction/Destruction                                             */
/************************************************************************/
LineSet::LineSet(void)
{
}

LineSet::~LineSet(void)
{
    Clear();
}

void PolygonDetection::LineSet::Clear(void)
{
    WX_CLEAR_ARRAY(_lines_array);
}


/***
* @desc Adds a new line to the line set
* @param line to be added
* @note the line object passed IS DELETED during destruction
*/
void PolygonDetection::LineSet::Add(Line * line)
{
    if (line) _lines_array.append(line);
}


/***
* @desc Removes intersections between lines
* @return true if successfull, false otherwise
* @see Bentley-Ottmann Algorithm
*/
bool PolygonDetection::LineSet::RemoveIntersections(void)
{
    printf("Line intersection removal\n");

    // prior to removing overlapping, one must
    // remove all zero length line, otherwise the results
    // will be unpredictable
    RemoveZeroLengthLines();

    // then we must remove line overlapping in order to run
    // the Bentley-Ottmann Algorithm
    RemoveOverlappings();

    // finally we detect intersections between lines
    int intersection_count = DetectIntersections();
    if (!PolygonDetection::PolygonDetector::Silent())
        printf("Detected %d intersections\n", intersection_count);

    int i, j, count = _lines_array.size();
    Line *line;

    LinesArray created_lines_list;
    GraphicalPrimitives2D::Point2D * point, * intersection;
    GraphicalPrimitives2D::PointArray * intersections_list;

    ITERATE_ALL_ENTITIES(_lines_array,ResetFlag(FLAG_REMOVE));

    // sweep all lines
    for (i=0; i<count; i++) {
        line = _lines_array.at(i);

        if (!line) {
            printf("Major failure (nullptr line) occurred during intersection removal.\n");
            break;
        }

        // check if current line has intersections
        if (line->HaveIntersections()) {

            point = line->GetFirstPoint();
            line->SortIntersectionsList();
            intersections_list = line->GetIntersectionsList();

            for (j=0; j<intersections_list->size(); j++){
                intersection = intersections_list->at(j);

                ADD_NEW_SEGMENT(created_lines_list, point, intersection);
                point = intersection;

            }

            ADD_NEW_SEGMENT(created_lines_list, point, line->GetLastPoint());
            line->SetFlag(FLAG_REMOVE);

        }
    }

    // Now lets remove the flagged lines
    for (i=_lines_array.size(); i>0; ) {
        line = _lines_array[--i];

        // check if line is flagged for removal
        if (!line || line->GetFlag(FLAG_REMOVE)) {
            // in that case, remove it from the array and delete it from memory
            _lines_array.removeAt(i);
            wxDELETE(line);
        }
    }

//    WX_APPEND_ARRAY(_lines_array, created_lines_list);
    for(auto l : created_lines_list)
        _lines_array.append(l);
    WX_CLEAR_ARRAY(created_lines_list);

    //ENDING_PROCESS_MESSAGE();
    return true;
}

/***
* @desc removes all lines with zero length 
*/
void PolygonDetection::LineSet::RemoveZeroLengthLines(void)
{
    // sweep all lines
    for (int i=_lines_array.size(); i>0; i--) {
        Line * line = _lines_array[i-1];
        // find a zero length line
        if ((*line->GetStartPoint())==(*line->GetEndPoint())) {
            _lines_array.removeAt(i-1);
            wxDELETE(line);
        }
    }
}

/***
* @descr removes line overlappings
* @note must be called before applying Bentley-Ottmann algorithm
*/
void PolygonDetection::LineSet::RemoveOverlappings(void)
{
    int i, j, count = _lines_array.size();
    Line *line, *line_i, *line_j;

    // lets find overlapping lines
    for (i=0; i<count; i++) {
        line_i = _lines_array[i];

        for(j=i+1;j<count;j++) {
            line_j =  _lines_array[j];
            if (Line::Overlapping(line_i, line_j)) {
                line = Line::SimplifiedLine(line_i, line_j);

                if (line == line_i) {
                    // must remove line_j
                    _lines_array.removeAt(j);
                    wxDELETE(line_j);
                    j--;
                    count--;
                } else {
                    if (line != line_j) {
                        // must remove both line_i and line_j and add a new one
                        _lines_array.removeAt(j);
                        wxDELETE(line_j);
                        _lines_array.append(line);
                    }

                    // must remove line_i
                    _lines_array.removeAt(i);
                    wxDELETE(line_i);

                    // update counters
                    i--;
                    count --;

                    // skip inner loop an go to next step of outer loop
                    break;
                }
            }

        }
    }
}

// Detect intersection between lines
unsigned int PolygonDetection::LineSet::DetectIntersections(void)
{
    // first we sort the line array
    Sort();

    // then declare the Active Line Segments Array (ALST)
    LinesArray * active_line_segments_array = new LinesArray();

    int j, counter = _lines_array.size();
    double current_y = 0, next_y;
    Line * current_line, * other_line;
    bool move_sweep_line = false;

    GraphicalPrimitives2D::Point2D * intersection = nullptr;

    int result = 0;

    // now we sweep over the Lines Array, in this case is '_entity_array'
    for(int n=0; n<counter;n++) {
        current_line = _lines_array[n];
        next_y = current_line->GetFirstPoint()->GetY();

        // see if current line belongs to next sweep line
        move_sweep_line = (next_y > current_y);

        // for each line in ALST
        for (j=active_line_segments_array->size(); j>0;) {
            other_line = active_line_segments_array->at(--j);

            // in case the current segment move the sweep line forward
            if (move_sweep_line) {
                // we must see if other line ends before next 'y', and in that case
                // it should be removed from Active Line Segments Array
                if (other_line->GetLastPoint()->GetY() < next_y) {
                    active_line_segments_array->removeAt(j);
                    continue;
                }
            }

            // if the current line intersects with other line
            if (current_line->Intersects(other_line)) {
                intersection = current_line->IntersectionPoint(other_line);

                if (intersection) {
                    current_line->AddIntersectionPoint(intersection);
                    other_line->AddIntersectionPoint(new GraphicalPrimitives2D::Point2D(intersection));
                    result++;
                }
            }
        }

        // in case the current segment move the sweep line forward
        if (move_sweep_line) {
            // we must move the sweep line
            current_y = next_y;
        }

        // now we add the current line to the Active Line Segments Array
        active_line_segments_array->append(current_line);

    }

    // at the end we remove the remaining lines in ALST
    // and delete the array
    DELETE_ARRAY(active_line_segments_array);

    return result;
}

/***
* @descr sort the lines
*/
void PolygonDetection::LineSet::Sort(void)
{
    CalculateLinesFirstAndLastPoint();
//    _lines_array.Sort(Line::CompareOrder);
    qSort(_lines_array.begin(),_lines_array.end(),Line::CompareOrder);
}

/***
* @descr calculates the bottom left point of all entities and its opposite point
*/
void PolygonDetection::LineSet::CalculateLinesFirstAndLastPoint(void)
{
    for (int i=0; i< _lines_array.size(); i++)
        _lines_array[i]->CalculateFirstAndLastPoint();

}

/***
* @descr Performs a scale transformation on lines of this set
*/
void PolygonDetection::LineSet::Scale(double sx, double sy)
{
    for (int i=0; i<_lines_array.size();i++)
        _lines_array[i]->Scale(sx,sy);
}

/***
* @descr Performs a scale transformation on lines of this set
*/
void PolygonDetection::LineSet::Translate(double dx, double dy)
{
    for (int i=0; i<_lines_array.size();i++)
        _lines_array[i]->Translate(dx,dy);

}

bool PolygonDetection::LineSet::Normalize(void)
{
    // compute the axis aligned bounding box
    GraphicalPrimitives2D::Point2D top_right;
    GraphicalPrimitives2D::Point2D bottom_left;
    bool first = true;
    for (int i=0; i<size(); i++) {
        Line * line = Item(i);
        if (line) {
            GraphicalPrimitives2D::Point2D * a = line->GetStartPoint();
            GraphicalPrimitives2D::Point2D * b = line->GetEndPoint();

            if (a && b) {
                if (first) {
                    top_right = *(a);
                    bottom_left = *(b);
                    first = false;
                } else {
                    double max_x = line->GetMaxX();
                    double min_x = line->GetMinX();
                    double max_y = line->GetMaxY();
                    double min_y = line->GetMinY();

                    top_right.SetX(MAX(top_right.GetX(), max_x));
                    top_right.SetY(MAX(top_right.GetY(), max_y));

                    bottom_left.SetX(MIN(bottom_left.GetX(), min_x));
                    bottom_left.SetY(MIN(bottom_left.GetY(), min_y));

                }
            } // if (a && b)...
        }
    }

    if (first) {
        printf("Unable to perform line set normalization.\n");
        return false;
    }

    // determine the scale factor
    double bb_width = fabs(top_right.GetX()-bottom_left.GetX());
    double bb_height = fabs(top_right.GetY()-bottom_left.GetY());


    if (bb_width==0.0 && bb_height==0.0 ) {
        printf("Empty bounding box. Could not normalize the line set.\n");
        return false;
    }

    double scale_factor= (1.0f)/MAX(bb_width,bb_height);

    Translate(-bottom_left.GetX(), -bottom_left.GetY());
    Scale(scale_factor,scale_factor);

    return true;
}

#undef ADD_NEW_SEGMENT

