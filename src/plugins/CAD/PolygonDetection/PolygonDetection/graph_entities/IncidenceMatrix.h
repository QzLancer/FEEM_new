/*
+--------------------------------------------------------------------+
| IncidenceMatrix.h: interface for the IncidenceMatrix class.        |
+--------------------------------------------------------------------+
|                                                                    |
| Author : Alfredo Ferreira Jr.                                      |
| E-mail : alfredo.ferreira.jr@inesc-id.pt                           |
| Website: http://immi.inesc-id.pt/~afj                              |
|                                                                    |
| Version: 1.00                                                      |
| Created: Jun 2003                                                  |
|                                                                    |
+--------------------------------------------------------------------+
| Intelligent Multimodal Interfaces Group at INESC-ID                |
| Department of Information Systems and Computer Science             |
| IST/Technical University of Lisbon                                 |
| Rua Alves Redol 9                                                  |
| 100-029 Lisboa, Portugal                                           |
+--------------------------------------------------------------------+
|                                                                    |
| Copyright (c) 2003 INESC-ID                                        |
|                                                                    |
|   The copyright to the computer program(s) herein is the property  |
| of INESC-ID, Portugal. The program(s) may be used and/or copied    |
| only with the written permission of INESC-ID or in accordance with |
| the terms and conditions stipulated in the agreement/contract      |
| under which the program(s) have been supplied.                     |
|                                                                    |
+--------------------------------------------------------------------+
*/
#if !defined(AFX_INCIDENCEMATRIX_H_INCLUDED)
#define AFX_INCIDENCEMATRIX_H_INCLUDED

#include "Cycle.h"
#include "Edge.h"
#include "MatrixModuloTwo.h"

#include <wx/dynarray.h>

namespace PolygonDetection {
typedef QVector<Edge *> EdgeArray;

	class IncidenceMatrix
	{
	public:	
#ifdef GRAPH_DEBUG	
		void Log();
#endif
		void CreateMatrix();
		void AddCycleToEdgePool( Cycle * cycle);
		bool IndependentCycle(Cycle * c);
		IncidenceMatrix();
		virtual ~IncidenceMatrix();

	private:
		int GetEdgeNumber( int vertex_a, int vertex_b);
		int _edge_count;
		int _independent_cycle_count;

		MatrixModuloTwo * _p_incidence_matrix;

		EdgeArray _edge_pool;
	};
}

#endif // !defined(AFX_INCIDENCEMATRIX_H_INCLUDED)
