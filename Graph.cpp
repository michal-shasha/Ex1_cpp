
// 325763498//
// michalshasha8@gmail.com
#include "Graph.hpp"
using namespace std;

namespace ariel{
 
 void Graph:: printGraph()
 {
    if(!this->directed)
      this->numEdges=this->numEdges/2;
    std::cout << "Graph with " << this->numVertices << " vertices and " << this->numEdges << " edges." << std::endl;
 }

 bool Graph::isSymmetricMatrix(vector<vector<int>>& matrix) {

    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = i+1; j < matrix.size(); ++j) {
            if (matrix[i][j] != matrix[j][i]) {
                return false; 
            }
        }
    }
    return true;
}

bool Graph::isSquareMatrix(vector<vector<int>>& matrix) {
    size_t n = matrix.size();
    for (size_t i = 0; i < n; ++i) {
        if (matrix[i].size() != n) {
            return false;
        }
        if (matrix[i][i] != 0) {
            return false;
        }
    }
    return true;
}


 void Graph:: loadGraph(vector<vector<int>> &g)  
 {
    this->setLoaded();
    this->numEdges=0;
    this->numVertices=0;
    this->edge = false;
    this->weight =false;
    this->adjMatrix=g;

    // Check if the matrix is square and its diagonal contains NO_EDGE
    if (!isSquareMatrix(g)) {
        throw invalid_argument("Invalid graph: The graph is not a square matrix.");
    }

    for(size_t i=0 ; i<g.size(); i++)
    {
      vector<int> v= g[i];
      for(size_t j=0 ; j<g.size(); j++)
      {
         if(this->adjMatrix[i][j]<0)
            this->edge = true;    //negative
         if(this->adjMatrix[i][j]!=0 && this->adjMatrix[i][j]!=1) 
            this->weight = true; 
         if(this->adjMatrix[i][j]!=0)     
            this->numEdges++;

      }  
    }

    this->numVertices=g.size();
    if(isSymmetricMatrix(g))
      this->directed = false; 
   else
       this->directed = true; 
 }

 void Graph:: setMatrix(vector<vector<int>>&mat)
 {
   this->adjMatrix=mat;
 }


 size_t Graph:: getSize()
 {
   return this->numVertices;
 }

 const vector<vector<int>> Graph::getMatrix()
 {
   return this->adjMatrix;
 }

 bool Graph:: getEdge()
 {
   return this->edge;
 }

 bool Graph:: getDirected()
 {
   return this->directed;
 }

 vector<int> Graph:: getNeighbors(int u)
 {
  return this->adjMatrix[size_t(u)];
 }

 int Graph:: getWeight(int u, int v)
 {
       return this->adjMatrix[static_cast<std::size_t>(u)][static_cast<std::size_t>(v)];
 }






 

}




