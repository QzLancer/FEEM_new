/*
+--------------------------------------------------------------------+
| MatrixModuloTwo.h: interface for the MatrixModuloTwo class.        |
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
#if !defined(AFX_MATRIXMODULOTWO_H_INCLUDED)
#define AFX_MATRIXMODULOTWO_H_INCLUDED

namespace PolygonDetection {
	class MatrixModuloTwo
	{
	public:	
#ifdef GRAPH_DEBUG	
		void Log();
#endif

		void GaussianElimination(int rows);	

		inline __int8 Get(int base, int offset) { return _matrix[base+offset];}
		inline void Set(int base, int offset, __int8 value) {
			_matrix[base+offset] = value;
		}

		inline __int8 GetAt(int row, int col) { return _matrix[GetAddress(row,col)]; };
		inline void SetAt(int row, int col, __int8 value) { _matrix[GetAddress(row, col)] = value; };
		
		MatrixModuloTwo(int rows, int cols);
		virtual ~MatrixModuloTwo();

	private:
		void SwapMatrixRows(int row_a, int row_b);
		inline int GetAddress(int row, int col) { return row*_cols+col; };
		int _rows;
		int _cols;

		__int8 * _matrix;
	};
}
#endif // !defined(AFX_MATRIXMODULOTWO_H_INCLUDED)
