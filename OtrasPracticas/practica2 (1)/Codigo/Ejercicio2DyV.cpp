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

bool CuadradoPerfecto(int p[], int tam, int posIni, int posFin, int num);
bool combina(bool solucion1, bool solucion2);
int main(int argc, char *argv[]){
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
    cout<<"Calculo del cuadrado perfecto" << endl << endl; 

    if (argc <= 1) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida num1";
		return 0;
	}

    int num = atoi(argv[1]);
    int problema[num]; 

    for (int i = 0; i<=num; i++)
        problema[i] = i;

t0= std::chrono::high_resolution_clock::now(); 
    bool resultado = CuadradoPerfecto(problema, num, 0 ,num - 1 , num);
tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
     if (resultado)
        cout << "El numero " << num << " es cuadrado perfecto" << endl;
      else 
          cout << "El numero " << num << " no es cuadrado perfecto" << endl;     

		
	unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
    cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< num<<endl;

}
bool CuadradoPerfecto(int p[], int tam, int posIni, int posFin, int num){
    bool solucion1 = false; 
    bool solucion2 = false; 
    bool solucion = false;
    int s = -1; 
    int s2 = -1;
    if (tam == 1){
        s = p[posIni]*p[posIni]; 
        s2 = p[posIni+1]*p[posIni+1];

        if (s == num){
            solucion = true;
        }else if (s2==num){
            solucion = true;
        }
        else
            solucion = false;
            
    }
    else{
        int centro = (posIni+posFin)/2;
        solucion1 = CuadradoPerfecto(p, tam/2, posIni, centro, num);
        solucion2 = CuadradoPerfecto(p, tam/2, centro+1, posFin, num);
        solucion = combina(solucion1, solucion2);
    } 
    //cout << "Probado para " << tam << " " << posIni << " " << posFin << endl << endl; 
    return solucion;
}

bool combina(bool solucion1, bool solucion2){
    if (solucion1 == true || solucion2 == true){
        return true; 
    }
    if(solucion1 == false && solucion2 == false)
        return false;
}