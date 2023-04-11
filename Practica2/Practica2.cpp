#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <cstring> // Para usar memcpy
#include <iostream>
#include <fstream> // Para usar ficheros
#include<vector>
#include "Punto.hpp"

using namespace std;

int main(int argc, char *argv[]){
    Punto *vector_puntos;
    //vector<Punto> vector_puntos;
	int n, i, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	double tejecucion; // tiempo de ejecucion del algoritmo en ms
	unsigned long int semilla;
	ofstream fsalida;

    if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}

    // Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}

    // Inicializamos generador de no. aleatorios
	semilla= atoi(argv[2]);

    // Pasamos por cada tamaÒo de caso
	for (argumento= 3; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
        int n_original = n;
		
		// Reservamos memoria para el vector
		vector_puntos = new Punto[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
        
		for (i= 0; i<n; i++){
           Punto Punto1 (semilla + i);
            vector_puntos[i] = Punto1;
        }
        

        int coordenadas[TAM];

        //Punto puntoFuerte (true, 9);
        //vector_puntos[n-1] = puntoFuerte;
        for(int i =0 ; i < n; i++){
            fsalida << "Punto " << i << " :" << endl;
            fsalida << vector_puntos[i].to_string();

            fsalida << endl << endl;
        }

        //tenemos que comparar las coordenadas con getK
        int indicePuntoFuerte[n];
        int auxIndicePuntoFuerte = 0;
        Punto *PuntosFuertes;
        PuntosFuertes = new Punto[n];
        int auxDomina = 0;
        bool noDominante = false;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n && noDominante; j++){
                if(vector_puntos[i].getK(i) < vector_puntos[j].getK(i)){
                    
                }                  
            }
           
         

        }
        
        cout << "Puntos dominantes = " << auxDomina << endl;
         /*for(int i = 0; i < auxDomina; i++){
           cout << "Punto Fuerte: " << PuntosFuertes[i].to_string() << endl;
         }*/
        delete[] vector_puntos;
        delete [] PuntosFuertes;
    }


            
}