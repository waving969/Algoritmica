#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <queue>
#include <vector>
#include <array>
#include <fstream> // Para usar ficheros
#include <math.h>
using namespace std;

int* AlgoritmoGreedy(int *p, int n, int k, int &tam_sol);
void OrdenaBurbuja(int *v, int n);

int main(int argc, char* argv[]){
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;

    int tam = atoi(argv[1]); 
    int vector[tam]; 
    int *solucion = new int[tam];
    int tam_sol = 0;
    int carga_maxima = atoi(argv[2]);
    if (argc-3 != tam){
        cerr<<"\nERROR: Metodo de ejecucion \n ./Ejercicio3 <tam_vector_comp> <tam_contenedor> <componentes_del_vector>...<componentes_del_vector-1>\n";
        return 0;
    }
    cout << "Carga maxima del buque: " << carga_maxima << endl;
    cout << "Numero de contenedores: " << tam << endl;
    cout << "Pesos de los contenedores: " << endl;
    for (int i = 0; i<tam; i++){
        vector[i] = atoi(argv[i+3]);
        cout << vector[i] << "t ";
    }
    cout << endl;

    t0= std::chrono::high_resolution_clock::now(); 
    solucion = AlgoritmoGreedy(vector, tam, carga_maxima, tam_sol);
    tf= std::chrono::high_resolution_clock::now();
    
    cout << endl<<endl;
    /*cout << "Peso de los contenedores que recoge: "<< endl;
    
    for (int i = 0; i<tam_sol; i++){
        cout << solucion[i]<<"t ";
    }*/
    //cout << endl<<endl;

    cout << "Numero de contenedores aniadidos: " << tam_sol<< endl;
    unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
    cerr << "\tTiempo de ejec. (us): " << tejecucion << endl;
}   


int* AlgoritmoGreedy(int *p, int n, int k, int &tam_sol){
    OrdenaBurbuja(p,n);
    cout <<"Ordenamos los contenedores por pesos: " << endl;
    for (int i = 0; i<n; i++){
        cout << p[i]<<"t ";
    }
    cout << endl<<endl;
    int *solucion = new int[n];
    int i = 0;
    int sum = 0;

    while(i<=n){
        if(sum + p[i] <= k){ 
            solucion[i] = p[i];
            cout << "Aniadimos contenedor de: " << solucion[i] << "t "<< endl;
            sum = sum+p[i];
            i++;
            tam_sol++;  
        }
        else
            i++;
    }
    cout << "No se pueden aniadir mas contenedores...";
     
    return solucion;
}


void OrdenaBurbuja(int *v, int n) {
	
	int i, j, aux;
	bool haycambios= true;
	
	i= 0;
	for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-1; j++){
            if(v[j+1] > v[j]){
                aux = v[j+1];
                v[j+1] = v[j];
                v[j] = aux;
            }
        }
    }
}
