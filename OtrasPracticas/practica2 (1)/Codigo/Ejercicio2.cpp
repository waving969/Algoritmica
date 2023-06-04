/*
Un número natural n se dice que es cuadrado perfecto si se corresponde con el cuadrado de otro
número natural. Por ejemplo, 4 es perfecto dado que 4=22 . También son cuadrados perfectos 25=52, o
100=102.

Solucion: Podemos decir que un numero es un cuadrado perfecto si y solo si su raiz cuadrada es exacta

Autores:    Juan Navarro Maldonado
            Joaquin Sergio Garcia Ibañez


*/
#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <math.h>
using namespace std;

bool CuadradoPerfecto(int numero);
int main(int argc, char *argv[]){
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
    cout<<"Calculo del cuadrado perfecto" << endl << endl; 

    if (argc <= 1) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida num1";
		return 0;
	}
 t0= std::chrono::high_resolution_clock::now(); 
    int num = atoi(argv[1]);
   
    bool resultado = CuadradoPerfecto(num);

     if (resultado)
        cout << "El numero " << num << " es cuadrado perfecto" << endl;
      else 
          cout << "El numero " << num << " no es cuadrado perfecto" << endl;     
    tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< num<<endl;


}
bool CuadradoPerfecto(int numero){
   bool cuadrado = false;
   for(int i = 0; i <= numero; i++){
    if(i*i == numero){
        cuadrado = true;
    }
   }

   return cuadrado;
}