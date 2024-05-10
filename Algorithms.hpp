// 325763498//
// michalshasha8@gmail.com

#include "Graph.hpp"
#include <vector>
#include <queue>
#pragma once
namespace ariel{
    enum Color {
    // for DFS
    WHITE,
    GRAY,
    BLACK,
 };

class Algorithms {
    
public:
    static int isConnected(Graph &g);
    static string shortestPath(Graph& g, int start, int end);
    static string isContainsCycle(Graph& g);
    static string isContainsCycleUtil(Graph& g, size_t src, vector<Color>* colors, vector<int>* parents,vector<int>* path);
    static string printCycle(vector<int>& path, vector<int>& parents, int start) ;
    static bool d(int v, Graph &graph, vector<int> &colors, int color); 
    static string isBipartite(Graph& g);
    static string negativeCycle(Graph& g);

    static void dfs(Graph& g, int v, vector<bool>& vec);
    static Graph transposeGraph(Graph& g);
};
}