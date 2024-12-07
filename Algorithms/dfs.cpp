#include <iostream>
#include <vector>

class Graph {
private:
    int V; 
    std::vector<std::vector<int>> adj; 

    bool dfs(int v, std::vector<bool>& visited, int parent) {
        visited[v] = true; 


        for (int u : adj[v]) {

            if (!visited[u]) {
                if (dfs(u, visited, v)) {
                    return true;
                }
            }

            else if (u != parent) {
                return true;
            }
        }
        return false;
    }

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v); 
    }

    bool containsCycle() {
        std::vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) { 
                if (dfs(i, visited, -1)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    Graph g(5); 
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0); 

    if (g.containsCycle()) {
        std::cout << "Graph contains a cycle" << std::endl;
    } else {
        std::cout << "Graph does not contain a cycle" << std::endl;
    }

    return 0;
}