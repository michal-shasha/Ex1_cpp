// 325763498//
// michalshasha8@gmail.com

#include <iostream>
#include <vector>
#pragma once
using namespace std;
namespace ariel{

class Graph {

public:
   Graph(){
    Loaded = false;
   }
    void printGraph(); 
    void loadGraph(vector<vector<int>>&);
    void setMatrix(vector<vector<int>>&);
    size_t getSize();
    const vector<vector<int>> getMatrix();
    bool getEdge();
    bool getDirected();
    bool isSymmetricMatrix(std::vector<std::vector<int>>&);
    bool isSquareMatrix(vector<vector<int>>& matrix);
    vector<int> getNeighbors(int u);
    int getWeight(int, int);
    bool isLoaded() {return this->Loaded;}
    void setLoaded() {this->Loaded = true;}

private:
    vector<vector<int>> adjMatrix; 
    size_t numVertices; 
    int numEdges;
    bool edge;
    bool weight;
    bool directed;
    bool Loaded;

};
}

