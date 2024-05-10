// 325763498//
// michalshasha8@gmail.com

#include "Algorithms.hpp"
#include <limits>
#include <climits>
#include <sstream>
#include <algorithm>
#include <stack>
#include <set>

using namespace std;
namespace ariel{

Graph Algorithms::transposeGraph(Graph& graph) {
    const vector<vector<int>>& adjMat=graph.getMatrix();
    size_t size = graph.getSize();
    vector<vector<int>> transposed( size, vector<int>(size, 0));

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            transposed[j][i] = adjMat[i][j];
        }
    }
    graph.setMatrix(transposed);
    return graph;
}  

void Algorithms:: dfs( Graph& graph, int vertex, vector<bool>& visited) {
    // סימון הצומת הנוכחי כביקר
    visited[size_t(vertex)] = true;
    const vector<vector<int>>& adjMat=graph.getMatrix();

    // מעבר על כל הצמתים השכנים של הצומת הנוכחי
    for (size_t neighbor = 0; neighbor < adjMat.size(); ++neighbor) {
        // בדיקה האם יש קשת מהצומת הנוכחי לשכן זה
        if (adjMat[size_t(vertex)][size_t(neighbor)] && !visited[size_t(neighbor)]) {
            // נקרא לעצמנו רקורסיבית עבור השכן הנוכחי
            dfs(graph, neighbor, visited);
        }
    }
}

int Algorithms::isConnected(Graph &g) 
{
if(g.getSize()==0)   
    return 1;

vector<bool> visited(g.getSize(), false);
dfs(g, 0, visited);

// בדיקה האם כל הצמתים נגישים
bool allVisited = true;
for (bool isVisited : visited) {
    if (!isVisited) {
        allVisited = false;
        break;
    }
}

if (!allVisited) {
    return false; // לא כל הצמתים נגישים, הגרף אינו קשיר
}

// אם הגרף הוא קשיר, נבדוק את הגרף ההפוך
Graph gg= transposeGraph(g);
visited.assign(g.getSize(), false); // איפוס רשימת הביקור
dfs(gg, 0, visited);

// בדיקה האם כל הצמתים נגישים בגרף ההפוך
allVisited = true;
for (bool isVisited : visited) {
    if (!isVisited) {
        allVisited = false;
        break;
    }
}

if (!allVisited) {
    return false; // לא כל הצמתים נגישים בגרף ההפוך, הגרף אינו קשיר
}

// אם הגרף הוא קשיר וגם הגרף ההפוך הוא קשיר, הגרף כולו קשיר
return true;
}


   
string Algorithms::shortestPath(Graph& g, int start, int end) {
    int V = g.getSize();
    if(V==0)
       return "-1";
    if( start < 0 || end < 0 || start > V || end > V){return "invalid vertices";}
    vector<int> dist(size_t(V), numeric_limits<int>::max());
    vector<int> parent(size_t(V), -1);
    dist[size_t(start)] = 0;

    // Relax all edges V-1 times
    for (size_t  i = 0; i < V - 1; ++i) {
        for (size_t  u = 0; u < V; ++u) {
            for (size_t  v = 0; v < V; ++v) {
                int weight;
                try{
                    weight = g.getWeight(u, v);
                }
                catch(invalid_argument){
                    throw invalid_argument("invalid vertices");
                }
                if (weight != 0 && dist[u] + weight < dist[v]) {
                    dist[v] = dist[size_t(u)] + weight;
                    parent[v] = u;
                    }
                }
            }
        }


    // Check for negative cycle
    for (size_t u = 0; u < V; ++u) {
        for (size_t v = 0; v < V; ++v) {
            int weight = g.getWeight(u, v);
            if (weight != 0 && dist[u] + weight < dist[v]) {
                // Negative cycle found
                return "-1";
            }
        }
    }


    // check for no path
    if( parent[(size_t)end] == -1){
        return "-1";
    }
    // Reconstruct path
    string path = to_string(end);
    int p = parent[(size_t)end];
    
    while(p != -1){
        path = to_string(p) + "->" + path;
        p = parent[(size_t)p];
    }    
    return path;
return "-1";
}



string Algorithms::isContainsCycle(Graph& g) {
    if(g.getSize() == 0)
        return "Graph is empty";

    // Creating arrays to store node colors, their parents, and the path of nodes
    vector<Color> colors(g.getSize(), WHITE);
    vector<int> parents(g.getSize(), -1);
    vector<int> path;

    // Iterate over all nodes in the graph
    for (size_t i = 0; i < g.getSize(); i++) {
        if (colors[i] == WHITE) {
            // Check if there is a cycle passing through node i
            string cycle = isContainsCycleUtil(g, i, &colors, &parents, &path);
            if (!cycle.empty()) {
                return cycle; // If a cycle is found, return the cycle
            }
        }
    }
    return "No cycle found"; // If no cycle is found, return "No cycle found"
}
string Algorithms::isContainsCycleUtil(Graph& g, size_t src, vector<Color>* colors, vector<int>* parents, vector<int>* path) 
{

    (*colors)[src] = GRAY; // Mark the current vertex as being visited (GRAY)
    path->push_back(src); // Add the current vertex to the path

    for (size_t v = 0; v < g.getSize(); v++) 
    {
        if (g.getMatrix()[src][v] != 0) // If there is an edge from src to v
        {
            if ((*colors)[v] == WHITE) // If v is not visited yet
            {
                (*parents)[v] = (int)src; // Set the parent of v as src
                string cycle = isContainsCycleUtil(g, v, colors, parents, path); // Recursively explore v
                if (cycle != "") // If a cycle is found in the recursive call
                {
                    return cycle; // Return the cycle path
                }
            }
            else if ((*colors)[v] == GRAY) // If v is already visited and is in the current path (GRAY)
            {
                if (!g.getDirected() && (*parents)[src] == (int)v) // If the graph is undirected and v is the parent of src, ignore it
                {
                    continue;
                }
                return printCycle(*path, *parents, v); // If a cycle is found, print the cycle
            }
        }
    }

    (*colors)[src] = BLACK; // Mark the current vertex as visited and processed (BLACK)
    path->pop_back(); // Remove the current vertex from the path
    return ""; // No cycle found in this path, return an empty string
}

string Algorithms::printCycle(vector<int>& path, vector<int>& parents, int start) {
  
    string cycle = "The cycle is: "; // Initialize the cycle string
    bool cycleFound = false; // Initialize the flag indicating whether the cycle is found
    size_t idx = 0; // Initialize the index to traverse the path vector

    // Find the starting index of the cycle in the path vector
    for (idx = 0; idx < path.size(); ++idx) {
        if (path[idx] == start) {
            cycleFound = true; // Set the cycleFound flag to true
            break;
        }
    }

    // If the cycle is found in the path
    if (cycleFound) {
        // Append the vertices of the cycle to the cycle string
        for (size_t i = idx; i < path.size(); ++i) {
            cycle += to_string(path[i]); // Append the vertex to the cycle string
            if (i != path.size() - 1) {
                cycle += "->"; // Append "->" if the vertex is not the last one in the cycle
            }
        }
        cycle += "->" + to_string(start); // Append the starting vertex of the cycle again to close the cycle
    }
    return cycle; // Return the cycle path as a string
}



string Algorithms::isBipartite(Graph &graph) {
    int n = graph.getSize();
    if (n == 0)  // Check if the graph has no vertices
        return "The graph is bipartite: A={}, B={}";

    std::vector<int> colors(size_t(n), -1); // Initialize all colors to -1 (unvisited)

    for (int i = 0; i < n; ++i) {
        if (colors[size_t(i)] == -1) {
            if (!d(i, graph, colors, 0)) {
                return "0"; // Graph is not bipartite
            }
        }
    }

    // Construct sets for both partitions
    std::set<int> A, B;
    for (int i = 0; i < n; ++i) {
        if (colors[size_t(i)] == 0) {
            A.insert(i);
        } else {
            B.insert(i);
        }
    }

    // Construct the output string
    std::string result = "The graph is bipartite: A={";
    for (int vertex : A) {
        result += std::to_string(vertex) + ", ";
    }
    if (!A.empty()) {
        result.pop_back(); // Remove trailing comma
        result.pop_back(); // Remove space
    }
    result += "}, B={";
    for (int vertex : B) {
        result += std::to_string(vertex) + ", ";
    }
    if (!B.empty()) {
        result.pop_back(); // Remove trailing comma
        result.pop_back(); // Remove space
    }
    result += "}";
    return result;
}

bool Algorithms::d(int v, Graph &graph, std::vector<int> &colors, int color) {
    colors[size_t(v)] = color; // Assign color to the current vertex

    for (int u = 0; u < graph.getSize(); ++u) {
        if (graph.getWeight(v, u) != 0) { // If there's an edge between v and u
            if (colors[size_t(u)] == -1) { // If u is not colored yet
                if (!d(u, graph, colors, 1 - color)) { // Recursively call d with the opposite color
                    return false;
                }
            } else if (colors[size_t(u)] == color) { // If u is already colored and has the same color as v
                return false; // Graph is not bipartite
            }
        }
    }
    return true; // Graph is bipartite
}



string Algorithms::negativeCycle(Graph& g) {

    size_t V = g.getSize();
    if(!g.isLoaded()){throw invalid_argument("empty graph");}
    int n = g.getSize();
    if (n == 0)  // Check if the graph has no vertices
        return "Graph is empty";
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    std::vector<int> parent(V, -1);

    // אתחול המרחק מהצומת הראשי ל-0
    dist[0] = 0;

    // Step 1: Relax all edges V-1 times
    for (size_t i = 0; i < V - 1; i++) {
        for (size_t u = 0; u < V; u++) {
            for (size_t v = 0; v < V; v++) {
                int weight = g.getWeight(u, v);
                if (weight != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = static_cast<int>(u);
                }
            }
        }
    }

    // Step 2: Check for negative cycle
    std::vector<int> cycle;
    for (size_t u = 0; u < V; u++) {
        for (size_t v = 0; v < V; v++) {
            const int weight = g.getWeight(u, v);
            if (weight != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                // Negative cycle found, trace back to find the cycle
                int current = static_cast<int>(v);
                do {
                    cycle.push_back(current);
                    current = parent.at(static_cast<size_t>(current));
                } while (current != v);

                // Add the starting vertex of the cycle
                cycle.push_back(v);

                // Reverse the cycle to get the correct order
                std::reverse(cycle.begin(), cycle.end());

                // Construct the cycle string
                std::string cycleStr = "Negative Cycle: ";
                for (size_t i = 0; i < cycle.size(); ++i) {
                    cycleStr += std::to_string(cycle.at(i));
                    if (i < cycle.size() - 1) cycleStr += " -> ";
                }

                // Return the cycle string
                return cycleStr;
            }
        }
    }

    // No negative cycle found
    return "No negative cycle found";
}


}


