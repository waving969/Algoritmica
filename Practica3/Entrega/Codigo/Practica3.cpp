#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <algorithm>
using namespace std;

string menu(){
    string devolver = "F";
    int menu;
    cout<< "Implementacion Practica3 \nSeleccion del grafo:\n \t1.- Grafo prueba\n\t2.- Grafo 1\n\t3.- Grafo 2\n\t4.- Grafo no euleriano\n\t5.- Grafo 3\n" << endl;
    cin >> menu;

    switch (menu)
    {
    case 1:
        devolver = "./datos.txt"; 
        break;
    case 2:
        devolver = "./Grafo1.txt"; 
        break;
    case 3:
        devolver = "./Grafo2.txt"; 
        break;
    case 4: 
        devolver = "./GrafoNoEuleriano.txt"; 
        break;
    case 5: 
        devolver = "./grafo3.txt"; 
        break;
    
    }
    return devolver;
}
vector<vector<int>> LeerFichero(string nombrefichero) {
    vector<int> vec;
    ifstream fichero(nombrefichero);
    vector<vector<int>> graf;
    if (fichero.is_open()) {
        int valor;
        while (fichero >> valor) {
            if(valor == -1){
                graf.push_back(vec);
                vec.clear();
            }
            else    
                vec.push_back(valor);  
        }
        fichero.close();
    } else {
        cerr << "Error: no se pudo abrir el archivo " << nombrefichero << endl;
    }

    return graf;
}

//Funcion que realiza la comprobacion de si es un Grafo Euleriano
bool esEuleriano(vector<vector<int>>& grafo) {
    for (int i = 0; i < grafo.size(); i++) {
        if (grafo[i].size() % 2 != 0) {
            return false;
        }
    }
    return true;
}

// Función que realiza el recorrido de Euler
void fleury(vector<vector<int>>& grafo, vector<int>& camino, int v) { 
    while (!grafo[v].empty()) {
        int w = grafo[v][0];  // Selecciona el primer vecino de v
        grafo[v].erase(grafo[v].begin());  // Elimina la arista (v,w) del grafo
        for (int i = 0; i < grafo[w].size(); i++) {
            if (grafo[w][i] == v) {  // Elimina la arista (w,v) del grafo
                grafo[w].erase(grafo[w].begin() + i);
                break;
            }
        }
        fleury(grafo, camino, w);  // Continúa el recorrido desde w
    }
    camino.push_back(v);  // Agrega v al circuito de Euler
}

int main() {
    vector<vector<int>> grafo = LeerFichero(menu());

    if(esEuleriano(grafo)){
        vector<int> camino;
        fleury(grafo, camino, 0);
        cout << "El camino es: " << endl;
        for (int v : camino) {
            cout << v << " ";
        }
    }else{
        cout << "El grafo dado no es euleriano "<< endl;
    }


    return 0;
}


