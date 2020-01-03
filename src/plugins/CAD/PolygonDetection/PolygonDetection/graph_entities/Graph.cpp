#include <stdlib.h> // because of malloc
#include <malloc.h> // because of malloc
#include <memory.h> // because of memcpy and memset
#include <stdio.h>

//#include <wx/utils.h> // to allow use of SafeYield

//#ifdef GRAPH_DEBUG
//#include <wx/log.h>
//#endif

#include "Graph.h"
#include "Cycle.h"

#include "../PDMacros.h"
#include "../PDConsts.h"
#include "../PolygonDetector.h"

using namespace PolygonDetection;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/***
* @desc contructor
* @param number of vertices (max. 65535)
* @note limit of 65535 vertices (requires aprox. 4GB of memory)
* @todo this can be optimized by using just half of the entries
*       and using a bit matrix instead of a byte matrix, but the 
*       computing overhead created does not justify it.
*/
Graph::Graph(int vertices) : 
    _vertex_count(vertices),
    _p_adjacency_matrix(new MatrixModuloTwo(vertices, vertices)),
    _d_matrix(nullptr),
    _predecessor_matrix(nullptr)

{

}

/***
* @desc destructor
*/ 
Graph::~Graph()
{		
    DELETE_OBJECT(_p_adjacency_matrix);

    FREE(_predecessor_matrix);
    FREE(_d_matrix);

}

/***
* @desc indicates that two vertices (v1 and v2) are adjacent
* @param v1, v2 vertex numbers
*/
void Graph::SetAdjacency(int v1, int v2)
{
    _p_adjacency_matrix->SetAt(v1,v2, 1);
    _p_adjacency_matrix->SetAt(v2,v1,1);
}


/***
* @desc tells if two vertices (v1 and v2) are adjacent
* @param v1, v2 vertex numbers
* @return boolean true if they are adjacent, false otherwise
*/
bool Graph::isAdjacent(int v1, int v2)
{
    return (_p_adjacency_matrix->GetAt(v1,v2)==1) || (_p_adjacency_matrix->GetAt(v2,v1)==1);
}

/***
* @desc count the edges of the graph
*/
int Graph::GetEdgeCount()
{
    int i, j, result = 0;


    for(i=0; i<GetVertexCount(); i++) {
        for(j=i+1;j<GetVertexCount(); j++)
            if (isAdjacent(i,j))
                result++;
    }

    return result;
}

/***
* @desc calculates the matrix offset of the pair v1, v2
* @return the offset at the adjacency matrix
* @note this calculation does not use the prperty of Symmetry
*       along the main diagonal of the adjacency matrix,
* @see Corman, T, Leiserson, C, Rivest, R, "Introduction to Algorithms", pp.467
*/
int Graph::MatrixOffset(int v1, int v2)
{
    return (v1*_vertex_count+v2);
}

/***
* @desc implements the Floyd-Warshall algorithm
* @see Corman, T, Leiserson, C, Rivest, R, "Introduction to Algorithms", pp.560
*/
void Graph::FloydWarshall()
{
    printf("Floyd-Warshall algorithm\n");

    int k, i, j, offset;
    int n = GetVertexCount();

    InitializeFloydWarshall();

    // 'd' matrices
    int * previous_d_matrix = _d_matrix;
    int * current_d_matrix = ALLOCATE_MEMORY(int, _vertex_count*_vertex_count);

    // 'pi' matrices
    int * previous_pi_matrix = _predecessor_matrix;
    int * current_pi_matrix = ALLOCATE_MEMORY(int, _vertex_count*_vertex_count);

    // initialize current matrix
    for (i=0;i<n;i++)
        for (j=0;j<n;j++) {
            current_d_matrix[i*n+j]=MAX_VERTICES;
            current_pi_matrix[i*n+j]=MAX_VERTICES;
        }

    // apply floyd warshall algorithm
    for (k=0; k<n ; k++){
        for (i=0; i<n ; i++) {
            for (j=0; j<n ; j++){
                if (i!=j) {
                    offset = MatrixOffset(i,j);

                    int previous_d_ij= previous_d_matrix[offset];
                    int previous_d_ik= previous_d_matrix[MatrixOffset(i,k)];
                    int previous_d_kj = previous_d_matrix[MatrixOffset(k,j)];

                    // start of 'd' calculation
                    if (previous_d_ik==MAX_VERTICES || previous_d_kj==MAX_VERTICES)
                        current_d_matrix[offset]=previous_d_ij;
                    else
                        current_d_matrix[offset]=MIN(previous_d_ij, previous_d_ik+previous_d_kj);
                    // end of 'd' calculation

                    // start of 'PI' calculation
                    if (previous_d_ij <= (previous_d_ik+previous_d_kj))
                        current_pi_matrix[offset] = previous_pi_matrix[offset];
                    else
                        current_pi_matrix[offset] = previous_pi_matrix[MatrixOffset(k,j)];
                    // end of 'PI' calculation
                }

            }
        }
        previous_d_matrix = current_d_matrix;
        previous_pi_matrix = current_pi_matrix;
    }

    FREE(_d_matrix);
    FREE(_predecessor_matrix);

    _d_matrix = current_d_matrix;
    _predecessor_matrix = current_pi_matrix;
}


/***
* @desc initializes the matrices needed for Floyd-Warshal Algorithm
*/
void Graph::InitializeFloydWarshall()
{

    _predecessor_matrix = ALLOCATE_MEMORY(int, _vertex_count*_vertex_count);
    _d_matrix = ALLOCATE_MEMORY(int, _vertex_count*_vertex_count);

    int i, j, offset;


    for (i=0; i<_vertex_count; i++)
        for (j=0;j<_vertex_count; j++){
            offset = i*_vertex_count+j;
            _d_matrix[offset] = _p_adjacency_matrix->Get(offset,0)==1?1:MAX_VERTICES;
            _predecessor_matrix[offset] =  (_p_adjacency_matrix->Get(offset,0)==1 && (i!=j))?i:MAX_VERTICES;
        }

}

/***
* @desc implements the Horton's algorithm for minimum cycle base
* @return pointer to a miminum cycle base
* @note DELETE the cycle base returned. It wont be deleted by the graph class
*       when it were destroyed
* @see Horton, J.D., "A polynomial-time algorithm to find the shortest cycle basis of a graph", 
*      SIAm J. Comput. 16(2):pp.358-366, 1987
* @see Vismara, P., "Union if all minimum cycle bases of a graph", Electronic Journal of 
*      Combinatronics 4:73--87, 1997 (Paper No. #R9 )
*/
CycleSet * Graph::Horton()
{
    printf("Horton algorithm\n");

    // creates a new cycles set
    CycleSet * p_cycle_set = new CycleSet();

    wxArrayInt * path_vx, * path_vy;

    Cycle * cycle;

    int v, x, y;

    // visit all vertices on the graph
    for(v=0; v<GetVertexCount();v++) {
        for(x=v+1; x<GetVertexCount();x++) {
            path_vx = GetShortestPath(v,x);
            for (y=x+1; y<GetVertexCount(); y++){
                path_vy = GetShortestPath(v,y);
                // if paths exists and points x and y are adjacent
                if (path_vx && path_vy && isAdjacent(x,y))
                    if (IsOnlyCommonPointInPaths(v, path_vx, path_vy) &&
                            IsTiermanCompliant(v, path_vx, path_vy)){

                        cycle = new Cycle(path_vx, path_vy);
                        if (cycle->GetLength()>0)
                            p_cycle_set->AddCycle(cycle);
                        else
                            DELETE_OBJECT(cycle);
                    }

                DELETE_ARRAY(path_vy);
            }
            DELETE_ARRAY(path_vx);
        }
    }

    // sort the cycles
    p_cycle_set->Sort();

    // lets apply the gaussian elimination
    if (p_cycle_set) {
        p_cycle_set->SelectCycles();
    }

    return p_cycle_set;
}

/***
* @desc returns the shortest path between 'i' and 'j'
*       this method is based on the PrintAllPairsShorthestPath algorithm
* @see Corman, T, Leiserson, C, Rivest, R, "Introduction to Algorithms", pp.551
*/
wxArrayInt * Graph::GetShortestPath(int i, int j)
{

    wxArrayInt * path = nullptr;

    // in case we end reach the end of the path
    if (i==j) {
        path = new wxArrayInt();
        path->append(i);
    }
    else {
        int offset_ij = MatrixOffset(i,j);
        if (_predecessor_matrix[offset_ij]==MAX_VERTICES)
            return nullptr;

        path = GetShortestPath(i, _predecessor_matrix[offset_ij]);

        if (path)
            path->append(j);

        return  path;
    }

    return path;
}

/***
* @desc detect if  istersection between 'p1' and 'p2' is only 'v'
* @return true if v is only common point between p1 and p2, false otherwise
*/
bool Graph::IsOnlyCommonPointInPaths(int v, wxArrayInt * p1,  wxArrayInt * p2)
{
    int i, j;
    int item_p1;
    int item_p2;
    bool v_exists_in_p1 = false;
    bool v_exists_in_p2 = false;

    for (i=0; i<p1->size(); i++) {
        item_p1 = p1->at(i);

        // checks if v exists in p1
        v_exists_in_p1 |= (item_p1 == v);

        for (j=0; j<p2->size();j++) {
            item_p2 = p2->at(j);

            if (item_p1 == item_p2 && item_p1 != v)
                return false;

            // checks if v exists in p2
            v_exists_in_p2 |= (item_p2 == v);
        }
    }

    return v_exists_in_p2 && v_exists_in_p1;
}


/***
* @desc detects of the cycle generated from initial point v using paths vx and vy is
*       compliant eith the condition suggested  by Tierman
* @see Tierman J., "An efficient search algorithm to find the elementary circuits of
*       a Graph", Comm. ACM 13: 722-726, 1970
*/
bool Graph::IsTiermanCompliant(int v, wxArrayInt * path_vx, wxArrayInt * path_vy)
{
    int i;
    int item_vx = path_vx->at(0);
    int item_vy = path_vy->at(0);

    // checks if both path start at 'v'
    if (item_vx != v || item_vy != v)
        return false;

    // checks if a cycle only contains vertices that precede v
    for (i=1; i< path_vx->size(); i++) {
        item_vx = path_vx->at(i);
        if (item_vx<=v)
            return false;
    }
    for (i=1; i< path_vy->size(); i++) {
        item_vy = path_vy->at(i);
        if (item_vy<=v)
            return false;
    }

    return true;
}


#ifdef GRAPH_DEBUG

/***
* @desc writes the graph in the log
*/
void Graph::Log()
{
    printf("Graph:\n\tVertices: %d\n\tEdges: %d", GetVertexCount(), GetEdgeCount());

    int i,j, n;
    QString d, p;
    for (i=0; i<GetVertexCount();i++) {
        for (j=0; j<GetVertexCount();j++) {
            d += QString::Format("%u\t", _d_matrix[i*GetVertexCount()+j]);
            p += QString::Format("%u\t", _predecessor_matrix[i*GetVertexCount()+j]);
        }
        p += "\n";
        d += "\n";
    }

    printf("\n----------\n");
    printf(d);
    printf("\n----------\n");
    printf(p);
    printf("\n----------\n");

    p = "";
    for (i=0; i<GetVertexCount();i++)
        for (j=i+1; j<GetVertexCount();j++){
            wxArrayInt * path = GetShortestPath(i,j);

            if (path) {
                for (n=0; n<path->size(); n++)
                    p += QString::Format("-%u", path->Item(n));

                DELETE_ARRAY(path);
            } else
                p += QString::Format("no path from %d to %d exists.",i,j);
            p += _("\n");
        }

    printf(p);
    printf("\n----------\n");

}
#endif
