#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <queue>
#include <vector>
#include <fstream> // Para usar ficheros
#include <math.h>
using namespace std;

int* calcularParadas(int distancia, int num_gasolineras, int *gasolineras, int &combustible, int &num_paradas);
void OrdenaBurbuja(int *v, int n);
int main (int argc ,char* argv[]){
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
    
    int deposito = atoi(argv[1]); 
    int distancia = atoi(argv[2]);
    int num_gasolineras = atoi(argv[3]);
    int *solucion = new int[num_gasolineras];
    int num_paradas = 0;
    int gasolineras[num_gasolineras];

    if (argc-4 != num_gasolineras){
        cerr<<"\nERROR: Metodo de ejecucion \n ./Ejercicio3 <combustible> <Distancia total> <gasolineras> <componentes_del_vector>...<componentes_del_vector-1>\n";
        return 0;
    }
    cout <<"Distancia hasta el destino: "  << distancia << endl; 
    cout << "Numero de gasolineras por el camino: " << num_gasolineras << endl; 
    cout << "Kilometros que se pueden recorrer con el deposito: " << deposito <<  endl << endl; 


    cout <<"Kilometros en los que se encuentran las gasolineras: " << endl; 
    for (int i = 0; i<num_gasolineras; i++){
        gasolineras[i] = atoi(argv[i+4]);
        cout << gasolineras[i] << "km ";
    }
    cout << endl;
    gasolineras[num_gasolineras] = distancia;
    t0= std::chrono::high_resolution_clock::now(); 
    solucion = calcularParadas(distancia, num_gasolineras, gasolineras, deposito);
    tf= std::chrono::high_resolution_clock::now();

    unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
    cerr << "\tTiempo de ejec. (us): " << tejecucion << endl;
}
int* calcularParadas(int distancia,int num_gasolineras, int *gasolineras, int &combustible){
    int *solucion = new int[num_gasolineras];
    int i = 0;
    //OrdenaBurbuja(gasolineras, num_gasolineras);
    
        while(combustible < distancia){
            if(combustible<=gasolineras[i]){
                num_paradas++;
                distancia = distancia-gasolineras[i-1];
                cout << "Parada en el kilometro: " << gasolineras[i-1] << "km " << endl;
                solucion[i] = i;
                i++;
            }
            else
                i++;
           
    }

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