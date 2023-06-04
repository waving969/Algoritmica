/*
Dado un número natural n, deseamos saber si existe otro número natural y de modo que
n=y*(y+1)*(y+2). Por ejemplo, para n=60, existe y=3 de modo que y*(y+1)*(y+2)=3*4*5=60.

Autores:    Juan Navarro Maldonado
            Joaquin Sergio Garcia Ibañez


*/
#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <math.h>
using namespace std;

int FuerzaBrutaEj3(int n, int &i);

int main(int argc, char *argv[]){
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
    cout<<"Calculo de un numero natural y" << endl; 

    if (argc <= 1) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida num1";
		return 0;
	}

    int n = atoi(argv[1]);
    
    int i;
   
    i = 0;
     t0= std::chrono::high_resolution_clock::now(); 
    int resultado = FuerzaBrutaEj3(n,i);
    
    if (n == resultado)
        cout << "\nPara 'n' = " << n << " 'y' = " << i << endl;
    else
        cout << "\nNo existe un numero natural para 'n' "<<n << endl;



      tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;
    
}

int FuerzaBrutaEj3(int n, int &i){
    int resultado;
    while (n != resultado && i<n){
        ++i;
        resultado = i*(i+1)*(i+2);
    }
    return resultado;
}