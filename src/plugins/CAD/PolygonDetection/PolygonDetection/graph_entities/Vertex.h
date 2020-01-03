/*
+--------------------------------------------------------------------+
| Vertex.h: interface for the Vertex class.                          |
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
#if !defined(AFX_VERTEX_H_INCLUDED)
#define AFX_VERTEX_H_INCLUDED

#include "Edge.h"

#include <wx/dynarray.h>

namespace PolygonDetection {
	// WX_DECLARE_OBJARRAY(Edge *, EdgeList);

	class Vertex
	{
	public:		
		Vertex(int id);
		virtual ~Vertex();

	private:
		int _id;
	// 	EdgeList * _edge_list;
	};
}
#endif // !defined(AFX_Vertex_H_INCLUDED)
