#if !defined(AFX_CYCLE_H_INCLUDED)
#define AFX_CYCLE_H_INCLUDED

#include <wx/dynarray.h>

namespace PolygonDetection {	

	class Cycle
	{
	public:
        static bool CompareOrder(Cycle * p_c1, Cycle * p_c2);
//		static int CompareOrder(Cycle ***p_c1, Cycle ***p_c2);

        void AddEdge(unsigned int edge_id) { if (_p_edge_list) _p_edge_list->append(edge_id); }

        inline int GetVertex(int number) {
            return (_p_cycle && _p_cycle->size()>number)?_p_cycle->at(number):0;
        }
        inline int GetEdge(int number) {
            return (_p_edge_list && _p_edge_list->size()>number)?_p_edge_list->at(number):0;
        }

        inline int GetVertexCount() { return _p_cycle?_p_cycle->size():0;}
        inline int GetEdgeCount() { return _p_edge_list?_p_edge_list->size():0;}

        inline int GetLength() { return GetVertexCount(); }

		Cycle(wxArrayInt *path_vx, wxArrayInt *path_vy);
		virtual ~Cycle();

	private:
        int _generated_from;
		wxArrayInt * _p_cycle;	
		wxArrayInt * _p_edge_list;
	};
}

#endif // !defined(AFX_CYCLE_H_INCLUDED)
