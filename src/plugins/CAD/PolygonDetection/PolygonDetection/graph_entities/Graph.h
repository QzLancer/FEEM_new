#if !defined(AFX_GRAPH_H_INCLUDED)
#define AFX_GRAPH_H_INCLUDED

#define MAX_VERTICES 65535

#include "CycleSet.h"
#include "MatrixModuloTwo.h"

namespace PolygonDetection {

class Graph
{
public:
    Graph(int vertices);
    virtual ~Graph();

    CycleSet * Horton();
    void FloydWarshall();
    void SetAdjacency(int v1, int v2);

    int GetEdgeCount();
    inline int GetVertexCount() { return _vertex_count; }

private:
    bool isAdjacent(int v1, int v2);

    bool IsTiermanCompliant(int v, wxArrayInt * path_vx, wxArrayInt * path_vy);
    bool IsOnlyCommonPointInPaths(int v, wxArrayInt * p1, wxArrayInt * p2);

    void InitializeFloydWarshall();
    int MatrixOffset(int v1, int v2);

    wxArrayInt * GetShortestPath(int i, int j);

    int _vertex_count;
    MatrixModuloTwo * _p_adjacency_matrix;
    int * _d_matrix;
    int * _predecessor_matrix;
};
}

#endif // !defined(AFX_GRAPH_H_INCLUDED)
