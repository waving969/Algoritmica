#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Función para comprobar si un grafo es Euleriano (todos los nodos tienen grado par)
bool esEuleriano(vector<vector<int>>& grafo) {
    for (int i = 0; i < grafo.size(); i++) {
        if (grafo[i].size() % 2 != 0) {
            return false;
        }
    }
    return true;
}

// Función para encontrar un camino de Euler en un grafo Euleriano
vector<int> caminoDeEuler(vector<vector<int>>& grafo) {
    vector<int> camino;
    if (!esEuleriano(grafo)) {
        return camino;
    }
    int numNodos = grafo.size();
    int nodoActual = 0;
    vector<int> pila;
    pila.push_back(nodoActual);
    while (!pila.empty()) {
        if (grafo[nodoActual].size() == 0) {
            camino.push_back(nodoActual);
            nodoActual = pila.back();
            pila.pop_back();
            
        } else {
            int siguienteNodo = grafo[nodoActual].back();
            grafo[nodoActual].pop_back();
            for (int i = 0; i < grafo[siguienteNodo].size(); i++) {
                if (grafo[siguienteNodo][i] == nodoActual) {
                    grafo[siguienteNodo].erase(grafo[siguienteNodo].begin() + i);
                    break;
                }
            }
            pila.push_back(nodoActual);
            nodoActual = siguienteNodo;
        }
    }
    camino.push_back(nodoActual);
    reverse(camino.begin(), camino.end());
    return camino;
}


// Ejemplo de uso
int main() {
    // Grafo de ejemplo con 4 nodos y 5 aristas
    vector<vector<int>> grafo = {{1,2}, {0,2,3,4}, {0,1,3,4}, {1,2,4,5}, {1,2,3,5}, {3,4}};
    vector<vector<int>> grafo2 = {{1,2},{0,3},{0,3},{1,2}};
    vector<int> camino = caminoDeEuler(grafo2);
    if (camino.size() == 0) {
        cout << "El grafo no es Euleriano" << endl;
    } else {
        cout << "Camino de Euler: ";
        for (int i = 0; i < camino.size(); i++) {
            cout << camino[i] << " ";
        }
        cout << endl;
    }
    cout << "Fin del algoritmo " << endl;
    return 0;
}