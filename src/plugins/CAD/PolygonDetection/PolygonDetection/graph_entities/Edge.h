/*
+--------------------------------------------------------------------+
| Edge.h: interface for the Edge class.                              |
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
#if !defined(AFX_EDGE_H_INCLUDED)
#define AFX_EDGE_H_INCLUDED

namespace PolygonDetection {
	class Edge
	{
	public:		
		inline bool Equals(int vertex_a, int vertex_b) {
			return (vertex_a==_vertex_a && vertex_b==_vertex_b) || 
				(vertex_a==_vertex_b && vertex_b==_vertex_a); 
		};
		inline int GetId() { return _id; };
		inline void SetVertices(int vertex_a, int vertex_b) {
			_vertex_a = vertex_a;
			_vertex_b = vertex_b;
		};
		Edge(int id);
		virtual ~Edge();

	private:
		int _id;

		int _vertex_a;
		int _vertex_b;

	};
}

#endif // !defined(AFX_EDGE_H_INCLUDED)
