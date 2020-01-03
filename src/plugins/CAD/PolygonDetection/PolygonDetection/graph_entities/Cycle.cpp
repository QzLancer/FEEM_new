#include "Cycle.h"

using namespace PolygonDetection;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/***
* @desc contructor
*/
Cycle::Cycle(wxArrayInt *path_vx, wxArrayInt *path_vy) : 
    _generated_from(0),
    _p_cycle(nullptr),
    _p_edge_list(nullptr)
{		
    int i;
    int item_vx = path_vx->at(0);
    int item_vy = path_vy->at(0);


    // checks if both path start at 'v'
    if (item_vx == item_vy ) {

        _generated_from = item_vx;

        // creates a new array
        _p_cycle = new wxArrayInt(/*path_vx->size()+path_vy->size()*/);

        for (i=0; i< path_vx->size(); i++) {
            item_vx = path_vx->at(i);
            _p_cycle->append(item_vx);
        }


        for (i=1; i<= path_vy->size(); i++) {
            item_vy = path_vy->at(path_vy->size()-i);
            _p_cycle->append(item_vy);
        }

        _p_edge_list = new wxArrayInt();
    }
}

Cycle::~Cycle()
{	
    DELETE_ARRAY(_p_cycle);
    DELETE_ARRAY(_p_edge_list);
}

/**
* @desc compares two cycles in term of order
* @return negative, zero or positive value 
*         according to whether the first element 
*         passed to it is less than, equal to or 
*         greater than the second one. 
*/
bool Cycle::CompareOrder(Cycle *p_c1, Cycle *p_c2)
{
    if (p_c1->GetLength()==p_c2->GetLength()) {
        return p_c1->_generated_from - p_c2->_generated_from;
    }

    return p_c1->GetLength() - p_c2->GetLength();
}

/***
* @return the vertex at position number
*/
//int Cycle::GetVertex(int number)
//{
//	return (_p_cycle && _p_cycle->size()>number)?_p_cycle->Item(number):0;
//}

//int Cycle::CompareOrder(Cycle ***p_c1, Cycle ***p_c2)
//{
//    return CompareOrder(**p_c1, **p_c2);
//}
