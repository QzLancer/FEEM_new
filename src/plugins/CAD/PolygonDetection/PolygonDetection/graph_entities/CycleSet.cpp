#include "CycleSet.h"

#include "../PDMacros.h"

#ifdef GRAPH_DEBUG	
#include <wx/log.h>
#endif

#include "IncidenceMatrix.h"

#include <stdlib.h> // for malloc and free
#include <malloc.h> // for malloc and free

#include <QtAlgorithms>

using namespace PolygonDetection;

//WX_DEFINE_OBJARRAY(CyclesArray);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/***
* @desc contructor
*/
CycleSet::CycleSet() : 
_p_cycles_array(nullptr)
{	
}

CycleSet::~CycleSet()
{	
	if (_p_cycles_array)
        WX_CLEAR_ARRAY((*_p_cycles_array));
	DELETE_ARRAY(_p_cycles_array);
}


void CycleSet::AddCycle(Cycle *c)
{
	if (!_p_cycles_array)
		//_p_cycles_array = new CyclesArray(Cycle::CompareOrder);
		_p_cycles_array = new CyclesArray();

	if (c)
        _p_cycles_array->append(c);
}

#ifdef GRAPH_DEBUG	
/***
* @desc log cycles
*/
void CycleSet::Log()
{

	QString s = "\n-------\nCycles:\n--------\n";	
		
	if (_p_cycles_array) 
		for (int j=0; j<_p_cycles_array->size();j++) {
			Cycle * cycle = _p_cycles_array->Item(j);

			for (int i=0; i<cycle->GetVertexCount(); i++) 
				s += QString::Format("->%d", cycle->GetVertex(i));
			
			s += "\n (Edges: ";	

			for (i=0; i<cycle->GetEdgeCount(); i++) 
				s += QString::Format("-%d", cycle->GetEdge(i));
			
			s += ")\n";	
		}

	printf(s);
}
#endif


/***
* @return the number of cycles existing in this cycle set
*/
int CycleSet::size()
{
	return _p_cycles_array?_p_cycles_array->size():0;
}

/***
* @return the cycle at the position indicated, nullptr if does not exists
*/
Cycle * CycleSet::GetCycle(int number)
{
	if (_p_cycles_array && _p_cycles_array->size()>number)
        return _p_cycles_array->at(number);

	return nullptr;
}

/***
* @desc Select independent cycles from cycle set
*/
void CycleSet::SelectCycles()
{
	int c;
	bool independent_cycle;

	// creation of incidence matrix 
	IncidenceMatrix * incidence_matrix = new IncidenceMatrix();

	for (c=0; c<size();c++) 
        incidence_matrix->AddCycleToEdgePool(_p_cycles_array->at(c));

	incidence_matrix->CreateMatrix();

	for (c=0; c<size();)  {		
        independent_cycle = incidence_matrix->IndependentCycle(_p_cycles_array->at(c));
		
		if (!independent_cycle) {
            Cycle * cycle = _p_cycles_array->at(c);
            _p_cycles_array->removeAt(c);
			DELETE_OBJECT(cycle);
		}
		else 
			c++;
	}

#ifdef GRAPH_DEBUG	
	incidence_matrix->Log();
#endif	

	DELETE_OBJECT(incidence_matrix);
}


void CycleSet::Sort()
{
    if (_p_cycles_array){
        qSort(_p_cycles_array->begin(),_p_cycles_array->end(),Cycle::CompareOrder);
    }
//		_p_cycles_array->Sort(Cycle::CompareOrder);
}
