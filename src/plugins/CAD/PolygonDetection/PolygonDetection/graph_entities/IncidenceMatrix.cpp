#include <stdlib.h> // for malloc and free
#include <malloc.h> // for malloc and free

#ifdef GRAPH_DEBUG	
#include <wx/log.h>
#endif

#include "IncidenceMatrix.h"
#include "Edge.h"
#include "../PDMacros.h"

//#include <wx/arrimpl.cpp>

using namespace PolygonDetection;

//WX_DEFINE_OBJARRAY(EdgeArray);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/***
* @desc contructor
*/
IncidenceMatrix::IncidenceMatrix() : 
_p_incidence_matrix(nullptr)
{
	_edge_count = 0;
	_independent_cycle_count = 0;
}


IncidenceMatrix::~IncidenceMatrix()
{	
	DELETE_OBJECT(_p_incidence_matrix);
	WX_CLEAR_ARRAY(_edge_pool);
}


/***	
* @return true if cycle c is independent from previous, false otherwise
*/
bool IncidenceMatrix::IndependentCycle(Cycle *c)
{

	bool independent_cycle = true;
	int offset = _independent_cycle_count*_edge_count;
	int edge;

	// add cycle to matrix
	for (int i=0; i<c->GetEdgeCount();i++){
		edge = c->GetEdge(i);

		_p_incidence_matrix->Set(offset,edge, 0x1);		
	}
	_independent_cycle_count++;
	
	if (_independent_cycle_count>1) {
		// check independency

		// first perform gaussian elimination
		_p_incidence_matrix->GaussianElimination(_independent_cycle_count);

		// then see if added row is all zeros		
		independent_cycle = false;
        for (int i=0; i<_edge_count && !independent_cycle; i++)
			independent_cycle = (_p_incidence_matrix->Get(offset,i) != 0x00);
	}
	
	// if this is an independent cycle, increment the row counter
	if (!independent_cycle)
		_independent_cycle_count--;
	
	return independent_cycle;
}

/***
* @desc add a cycle in order to construct the edge pool, 
* @note this must be done before creating the matrix
* @note IMPORTANT: creates an edge list in cycle
*/
void IncidenceMatrix::AddCycleToEdgePool(Cycle *cycle)
{
	int current_vertex, first_vertex, previous_vertex=0;
	bool first = true;
	int edge_number;

	for (int i=0; i<cycle->GetVertexCount();i++) {		
		current_vertex = cycle->GetVertex(i);

		// in case this is not the frst vertex, finds the edge number
		// and adds it to the edge list in cycle
		if (!first) {
			edge_number = GetEdgeNumber(previous_vertex, current_vertex);
			cycle->AddEdge(edge_number);
		} else {
			first = false;
			first_vertex = current_vertex;
		}

		previous_vertex = current_vertex;		
	}

// the vertex list in cycle already contains the first vertex at the end of the list,
// so we do not need the ollowing lines
//	if (i>0) {
//		edge_number = GetEdgeNumber(current_vertex, first_vertex);
//		cycle->AddEdge(edge_number);
//	}
//
}

/***
* @return the edge number of given pair of vertices
*/
int IncidenceMatrix::GetEdgeNumber(int vertex_a, int vertex_b)
{
	Edge * e;

    for (int i=0; i< _edge_pool.size();i++){
		e = _edge_pool[i];
		if (e->Equals(vertex_a, vertex_b))
			return e->GetId();
	}

	// if arrives here, there are no such edge in edge pool
	// so we must create a new edge
	e = new Edge(_edge_count++);	
	e->SetVertices(vertex_a, vertex_b);

	// and add it to the edge pool
    _edge_pool.append(e);

	return e->GetId();
}

/***
* @desc creates the incidence matrix
* @note this must be done after all cycles have been added, in order
*      to create the edge pool
*/
void IncidenceMatrix::CreateMatrix()
{
	_p_incidence_matrix = new MatrixModuloTwo(_edge_pool.size(), _edge_count);
}

#ifdef GRAPH_DEBUG	
void IncidenceMatrix::Log()
{
	printf("Incidence Matrix\n----------------\n");
	
	if (_p_incidence_matrix)
		_p_incidence_matrix->Log();
	
}
#endif

/***
* @return number of first column with non-zero value in row r
*/
//DEL int IncidenceMatrix::FirstNonZeroColumn(int row)
//DEL {
//DEL 	for (int c=0; c<_edge_count; c++) {
//DEL 		if (_incidence_matrix[row*_edge_count+c]==1)
//DEL 			return c;
//DEL 	}
//DEL 
//DEL 	return _edge_count;
//DEL }



//DEL void IncidenceMatrix::GaussianElimination()
//DEL {
//DEL 	int c, r, k, max;
//DEL 
//DEL 	int columns = _edge_count;
//DEL 	int rows = _row_count;
//DEL 	__int8 * matrix = _incidence_matrix;
//DEL 
//DEL 	int pivot_row=0;
//DEL 
//DEL 	for(c=0;c<columns;c++) {		
//DEL 		max = pivot_row;
//DEL 
//DEL 		// in this case no substitution is needed
//DEL 		if (matrix[pivot_row*columns+c]!=0x01) {
//DEL 		
//DEL 			// otherwise, lets found if its needed any substitution
//DEL 			for (r=pivot_row+1;r<rows;r++) {
//DEL 				if (matrix[r*columns+c]==1) {
//DEL 					max = r;
//DEL 					break;
//DEL 				}
//DEL 			}
//DEL 
//DEL 			// if pivot row is zero and other column is one
//DEL 			// then they must change			
//DEL 			if (max!=pivot_row)
//DEL 				SwapMatrixRows(max,pivot_row);
//DEL 		}
//DEL 
//DEL 		// now lets make the elimination
//DEL 		if (matrix[pivot_row*columns+c]==0x01) {
//DEL 			for (r=pivot_row+1; r<rows; r++)
//DEL 				if (matrix[r*columns+c]==0x01)
//DEL 					for (k=c;k<columns;k++)
//DEL 						matrix[r*columns+k] ^= matrix[pivot_row*columns+k];
//DEL 
//DEL 			pivot_row++;
//DEL 		}
//DEL 	}
//DEL }

/***
* @desc swaps the matrix row <row_a> with row <row_b>
* @param int row_a indicates the number of one row  
* @param int row_b indicates the number of other row  
*/
//DEL void IncidenceMatrix::SwapMatrixRows(int row_a, int row_b)
//DEL {
//DEL 	int columns = _edge_count;
//DEL 	__int8 * matrix = _incidence_matrix;
//DEL 	__int8 t;
//DEL 
//DEL 	int row_a_offset = row_a*columns;
//DEL 	int row_b_offset = row_b*columns;
//DEL 
//DEL 	
//DEL 	for (int k=0; k<columns; k++) {
//DEL 		t = matrix[row_a_offset+k];
//DEL 		matrix[row_a_offset+k] = matrix[row_b_offset+k];
//DEL 		matrix[row_b_offset+k] = t;
//DEL 	}
//DEL }
