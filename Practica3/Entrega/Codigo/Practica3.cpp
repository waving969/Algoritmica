#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <algorithm>
using namespace std;

string menu(int &nodoInicial){
    string devolver = "F";
    
    int menu = 6;
    while(menu == 6){    
        
        cout<< "Implementacion Practica3 \nSeleccion del grafo:\n \t1.- Grafo prueba\n\t2.- Grafo 1\n\t3.- Grafo 2\n\t4.- Grafo no euleriano\n\t5.- Grafo 3\n\t6.- Configuracion" << endl;
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
        case 6: 
            cout << "Introduce el nodoInicial: ";
            cin >> nodoInicial;
            break;
        
        }
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

int heuristicaGreedy(vector<vector<int>>& grafo, int v) {
    // Elige el vecino con el menor número de aristas adyacentes
    int minVecino = grafo[v][0];
    int minAristas = grafo[grafo[v][0]].size();

    for (int i = 1; i < grafo[v].size(); i++) {
        int vecino = grafo[v][i];
        int numAristas = grafo[vecino].size();

        if (numAristas < minAristas) {
            minVecino = vecino;
            minAristas = numAristas;
        }
    }

    return minVecino;
}


void fleury(vector<vector<int>>& grafo, vector<int>& camino, int v) { 
    while (!grafo[v].empty()) {
        int w = heuristicaGreedy(grafo, v);
        //cout << "Borrando arista prometedora " << w;
        grafo[v].erase(grafo[v].begin());  // Elimina la arista (v,w) del grafo
        for (size_t i = 0; i < grafo[w].size(); i++) {
            if (grafo[w][i] == v) {  // Elimina la arista (w,v) del grafo
                //cout << " Borrando " << i << " De nodo " << w <<  endl;
                grafo[w].erase(grafo[w].begin() + i);
                break;
            }
        }
        fleury(grafo, camino, w);  // Continúa el recorrido desde w
    }
    camino.push_back(v);  // Agrega v al circuito de Euler
}


int main() {
    //string menue = menu();
    int nodoInicial = 0;
    vector<vector<int>> grafo =LeerFichero(menu(nodoInicial)); // {{1,2},{0,2,3,4},{0,1,3,4},{1,2,4,5},{1,2,3,5},{3,4}};

    if(esEuleriano(grafo)){
        vector<int> camino;
        fleury(grafo, camino, nodoInicial);
        cout << "El camino es: " << endl;
        for (int v : camino) {
            cout << v << " ";
        }
    }else{
        cout << "El grafo dado no es euleriano "<< endl;
    }

    
    return 0;
}


