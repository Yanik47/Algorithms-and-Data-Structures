#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>
using namespace std;

class DirectedGraph {
private:
    unordered_map<int, unordered_set<int>> adj;

public:
    
    void addEdge(int v, int w) {
        adj[v].insert(w); 
    }

    
    int getInDegree(int v) {
        int inDegree = 0;
        for (auto& pair : adj) {
            if (pair.second.find(v) != pair.second.end()) {
                inDegree++;
            }
        }
        return inDegree;
    }

    
    int getOutDegree(int v) {
        return adj[v].size();
    }

    
    void printOutgoingNeighbors(int v) {
        cout << "Outgoing neighbors of vertex " << v << ": ";
        for (auto neighbor : adj[v]) {
            cout << neighbor << " ";
        }
        cout << "\n";
    }

    
    void printIncomingNeighbors(int v) {
        cout << "Incoming neighbors of vertex " << v << ": ";
        for (auto& pair : adj) {
            if (pair.second.find(v) != pair.second.end()) {
                cout << pair.first << " ";
            }
        }
        cout << "\n";
    }
};

class Graph {
private:
    std::unordered_map<int, std::unordered_set<int>> adj; 

public:
    
    void addEdge(int v, int w) {
        adj[v].insert(w); 
        adj[w].insert(v); 
    }

    
    int degree(int v) const {
        if (adj.find(v) == adj.end()) return 0; 
        return adj.at(v).size();
    }

    
    void printNeighbors(int v) const {
        if (adj.find(v) == adj.end()) {
            std::cout << "Vertex " << v << " not found.\n";
            return;
        }

        std::cout << "Neighbors of vertex " << v << ": ";
        for (const int& neighbor : adj.at(v)) {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }

    
    bool hasEdge(int v, int w) const {
        if (adj.find(v) == adj.end()) return false; 
        return adj.at(v).find(w) != adj.at(v).end(); 
    }
};

const int MAX_V = 100; 

class DirectedGraph_tb {
private:
    int adj[MAX_V][MAX_V]; 
    int V; 
    int outDegree[MAX_V]; 
    int inDegree[MAX_V]; 

public:
    
    DirectedGraph_tb(int V) {
        this->V = V;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                adj[i][j] = 0;
            }
            outDegree[i] = 0;
            inDegree[i] = 0;
        }
    }

    
    void addEdge(int v, int w) {
        if (v >= V || w >= V) return; 
        if (adj[v][w] == 1) return; 

        adj[v][w] = 1; 
        outDegree[v]++;
        inDegree[w]++;
    }

    
    int getInDegree(int v) {
        if (v >= V) return -1; 
        return inDegree[v];
    }

    
    int getOutDegree(int v) {
        if (v >= V) return -1; 
        return outDegree[v];
    }

    
    void printOutgoingNeighbors(int v) {
        if (v >= V) {
            cout << "Invalid vertex\n";
            return;
        }

        cout << "Outgoing neighbors of vertex " << v << ": ";
        for (int i = 0; i < V; i++) {
            if (adj[v][i] == 1) {
                cout << i << " ";
            }
        }
        cout << "\n";
    }

    
    void printIncomingNeighbors(int v) {
        if (v >= V) {
            cout << "Invalid vertex\n";
            return;
        }

        cout << "Incoming neighbors of vertex " << v << ": ";
        for (int i = 0; i < V; i++) {
            if (adj[i][v] == 1) {
                cout << i << " ";
            }
        }
        cout << "\n";
    }
};

class Graph_tb {
private:
    int adj[MAX_V][MAX_V]; 
    int V; 
    int edgeCount[MAX_V]; 

public:
    
    Graph_tb(int V) {
        this->V = V;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                adj[i][j] = 0;
            }
            edgeCount[i] = 0;
        }
    }

    
    void addEdge(int v, int w) {
        if (v >= V || w >= V) return; 
        if (adj[v][w] == 1) return; 

        adj[v][w] = 1; 
        adj[w][v] = 1; 

        edgeCount[v]++;
        edgeCount[w]++;
    }

    
    int degree(int v) {
        if (v >= V) return -1; 
        return edgeCount[v];
    }

    
    void printNeighbors(int v) {
        if (v >= V) {
            cout << "Invalid vertex\n";
            return;
        }

        cout << "Neighbors of vertex " << v << ": ";
        for (int i = 0; i < V; i++) {
            if (adj[v][i] == 1) {
                cout << i << " ";
            }
        }
        cout << "\n";
    }
};

class Graph_in_nsk {
private: 
    int adj[MAX_V][MAX_V];
    int V; 
    int edgeCount[MAX_V];
public: 
    Graph_in_nsk(int V) {
        this->V = V;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                adj[i][j] = 0;
            }
            edgeCount[i] = 0;
        }
    }

    void addEdge(int e, int v, int w) {
        if (v >= V || w >= V) return; 
        if (v == w){
            adj[w][e] = 2;
            edgeCount[v]++;
        } 
        else{
            adj[w][e] = 1; 
            adj[v][e] = 1; 
    
        edgeCount[v]++;
        edgeCount[w]++;
        }

    }
    int degree(int v) {
        if (v >= V) return -1; 
        return edgeCount[v];
    }

    void printNeighbors(int v) {
        if (v >= V) {
            cout << "Invalid vertex\n";
            return;
        }
        set<int> neighbors;

        cout << "Neighbors of vertex " << v << ": ";
        for (int i = 0; i < V; i++) {
            if (adj[v][i] == 1) {
                for(int j = 0; j < V; j++){
                    if(adj[j][i] == 1 && j != v || adj[j][i] == 2){
                        neighbors.insert(j);
                    }
                }
                
            }
        }
        for(int elem : neighbors){
            cout << elem << " ";
        }
        cout << "\n";
    }
};    

class DirectedGraph_in_sk {
private: 
    int adj[MAX_V][MAX_V]; 
    int V; 
    int outDegree[MAX_V]; 
    int inDegree[MAX_V]; 
public: 
    DirectedGraph_in_sk(int V) {
        this->V = V;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                adj[i][j] = 0;
            }
            outDegree[i] = 0;
            inDegree[i] = 0;
        }
    }
    void addEdge(int e, int we, int wy) {
        if (we >= V || wy >= V) return; 
        if (we == wy){
            adj[e][we] = 3;
            outDegree[wy]++;
        } 
        else{
            cout << " dfsf";
            adj[e][we] = 1;
            adj[e][wy]  = 2;
        
            outDegree[wy]++;
            inDegree[we]++;
        }
    }

    int getInDegree(int v) {
        if (v >= V) return -1; 
        return inDegree[v];
    }

    
    int getOutDegree(int v) {
        if (v >= V) return -1; 
        return outDegree[v];
    }    

    void printOutgoingNeighbors(int v) {
        if (v >= V) {
            cout << "Invalid vertex\n";
            return;
        }

        for(int i = 1; i < V+1; i++){
            
            for(int j = 1; j < V+1; j++){
                cout << adj[i][j] << " ";
            }
        cout << "\n";
        }

        set<int> neighbors;

        cout << "Outgoing neighbors of vertex " << v << ": ";
        for (int i = 0; i < V+1; i++) {
            if (adj[i][v] == 2 || adj[i][v] == 3) {
                for(int j = 0; j < V+1; j++){
                    if(adj[i][j] == 1 || adj[i][v] == 3){
                        neighbors.insert(j);
                    }
                }
                
            }
        }
        for(int elem : neighbors){
            if(elem != v){
                cout << elem << " ";
            }
        }

        cout << "\n";
    }

    
    void printIncomingNeighbors(int v) {
        if (v >= V) {
            cout << "Invalid vertex\n";
            return;
        }

        set<int> neighbors;

        cout << "Incoming neighbors of vertex" << v << ": ";
        for (int i = 0; i < V+1; i++) {
            if (adj[i][v] == 1 || adj[i][v] == 3) {
                for(int j = 0; j < V+1; j++){
                    if(adj[i][j] == 2 || adj[i][v] == 3){
                        neighbors.insert(j);
                    }
                }
                
            }
        }
        for(int elem : neighbors){
            if(elem != v){
                cout << elem << " ";
            }
        }

        cout << "\n";
    }
};

int main(int argc, char *argv[]) {

    DirectedGraph g_sk_sl;
    Graph g_nsk_sl;
    DirectedGraph_tb g_sk_tb(atoi(argv[3]));
    Graph_tb g_nsk_tb(atoi(argv[3]));
    DirectedGraph_in_sk g_sk_mi(atoi(argv[3]));
    Graph_in_nsk g_nsk_mi(atoi(argv[3]));

    //SKIEROWANY SLOWNIK
    if(strcmp(argv[1], "1") == 0){

        for(int i = 4; i < argc; i++){
        int a, b;
        if(sscanf(argv[i], "(%d, %d)", &a, &b) == 2){
            g_sk_sl.addEdge(a, b);
        }else{
            cout << "Niepoprawny format danych: "<< argv[i] << "Musi być: (1, 2) \n";
        }
    }

    cout << "1In-degree of vertex 1: " << g_sk_sl.getInDegree(1) << "\n"; 
    cout << "Out-degree of vertex 1: " << g_sk_sl.getOutDegree(1) << "\n"; 

    g_sk_sl.printIncomingNeighbors(1); 
    g_sk_sl.printOutgoingNeighbors(1);

    }
    //NIESKIEROWANY SLOWNIK
    else if(strcmp(argv[1], "2") == 0){

        for(int i = 4; i < argc; i++){
        int a, b;
        if(sscanf(argv[i], "(%d,%d)", &a, &b) == 2){
            g_nsk_sl.addEdge(a, b);
        }else{
            cout << "Niepoprawny format danych: "<< argv[i] << "Musi być: (1, 2) \n";
        }
        }
        cout << "1Degree of vertex 1: " << g_nsk_sl.degree(1) << "\n";
        g_nsk_sl.printNeighbors(1); 
    }
    //SKIEROWANA TABLICA
    else if(strcmp(argv[1], "3") == 0){

        for(int i = 4; i < argc; i++){
        int a, b;
        if(sscanf(argv[i], "(%d, %d)", &a, &b) == 2){
            g_sk_tb.addEdge(a, b);
        }else{
            cout << "Niepoprawny format danych: "<< argv[i] << "Musi być: (1, 2) \n";
        }
    }

    cout << "2In-degree of vertex 1: " << g_sk_tb.getInDegree(1) << "\n"; 
    cout << "Out-degree of vertex 1: " << g_sk_tb.getOutDegree(1) << "\n"; 

    g_sk_tb.printIncomingNeighbors(1); 
    g_sk_tb.printOutgoingNeighbors(1);

    }
    //TABLICA NIESKIEROWANY
    else if(strcmp(argv[1], "4") == 0){
        for(int i = 4; i < argc; i++){
            int a, b;
            if(sscanf(argv[i], "(%d,%d)", &a, &b) == 2){
                g_nsk_tb.addEdge(a, b);
            }else{
                cout << "Niepoprawny format danych: "<< argv[i] << "Musi być: (1, 2) \n";
            }
        }
            cout << "2Degree of vertex 1: " << g_nsk_tb.degree(1) << "\n";
            g_nsk_tb.printNeighbors(1); 
        }

    else if(strcmp(argv[1], "5") == 0){
        for(int i = 4; i < argc; i++){
        int a, b, e;
        if(sscanf(argv[i], "(%d,%d,%d)", &e, &a, &b) == 3){
            g_sk_mi.addEdge(e, a, b);
        }else{
            cout << "Niepoprawny format danych: "<< argv[i] << "Musi być: (\'numer krawędzi\', 1, 2) \n";
        }
    }

    cout << "3In-degree of vertex 1: " << g_sk_mi.getInDegree(1) << "\n"; 
    cout << "Out-degree of vertex 1: " << g_sk_mi.getOutDegree(1) << "\n"; 

    g_sk_mi.printIncomingNeighbors(1); 
    g_sk_mi.printOutgoingNeighbors(1);

    }
    else if(strcmp(argv[1], "6") == 0){
        for(int i = 4; i < argc; i++){
            int a, b, e;
            if(sscanf(argv[i], "(%d,%d,%d)",  &e, &a, &b) == 3){
                g_nsk_mi.addEdge(e, a, b);
            }else{
                cout << "Niepoprawny format danych: "<< argv[i] << " Musi być: (\'numer krawędzi\', 1, 2) \n";
            }
        }
            cout << "3Degree of edge: " << g_nsk_mi.degree(1) << "\n";
            g_nsk_mi.printNeighbors(1); 

    }

    else{
            cout << "nie ma takiego typu grafu do wyboru" << "\n";
            return 0;        

        }

    return 0;
}