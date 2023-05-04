#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

const int MAXN = 7; // número de nodos en el grafo
vector<int> adj[MAXN]; // vector de adyacencia para representar el grafo
int degree[MAXN]; // arreglo para almacenar el grado de cada nodo

void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    degree[u]++;
    degree[v]++;
}

void euler_path(int u) {
    for (int v : adj[u]) {
        if (degree[v] > 0) {
            degree[u]--;
            degree[v]--;
            adj[u].erase(find(adj[u].begin(), adj[u].end(), v));
            adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
            euler_path(v);
        }
    }
    cout << u << " ";
}

int main() {
    // Creamos un grafo de Euler con 7 nodos y 12 aristas
    add_edge(0, 1);
    add_edge(0, 2);
    add_edge(0, 5);
    add_edge(1, 2);
    add_edge(1, 3);
    add_edge(2, 3);
    add_edge(2, 4);
    add_edge(2, 5);
    add_edge(3, 4);
    add_edge(4, 5);
    add_edge(4, 6);
    add_edge(5, 6);
    
    // Encontramos un camino de Euler empezando en el nodo 0
    euler_path(0);
    
    return 0;
}
