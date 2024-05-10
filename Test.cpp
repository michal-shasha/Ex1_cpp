// 325763498//
// michalshasha8@gmail.com

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <vector>
#include <sstream>

using namespace std;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> emptyGraph={};
    g.loadGraph(emptyGraph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph3 = {
            {0, 1, 0},
            {1, 0, 0},
            {0, 0, 0}
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");

    vector<vector<int>> emptyGraph = {};
    g.loadGraph(emptyGraph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "-1");

    vector<vector<int>> graph3 = {
        {0, 1, 0, 0},
        {1, 0, 1, 1},
        {0, 1, 0, 0},
        {0, 1, 0, 0}
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->1->3");
}

TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");


    vector<vector<int>> emptyGraph={};
    g.loadGraph(emptyGraph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph is empty"); // An empty matrix does not have cycles
}
TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph4 = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 1, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> emptyGraph={};
    g.loadGraph(emptyGraph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={}, B={}"); // An empty matrix is considered bipartite
}
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 1, 0},
        {0, 1, 0}};
    CHECK_THROWS(g.loadGraph(graph2));    

}

TEST_CASE("Test negativeCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, -1, 0},
        {0, 0, -1},
        {-1, 0, 0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative Cycle: 1 -> 2 -> 0 -> 1");

    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}
    };
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");


    vector<vector<int>> emptyGraph={};
    g.loadGraph(emptyGraph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Graph is empty");

}
   








