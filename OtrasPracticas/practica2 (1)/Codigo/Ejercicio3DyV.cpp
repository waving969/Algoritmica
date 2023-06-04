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

bool FuerzaBrutaEj3(int p[], int tam, int posIni, int posFin, int num, int &posibleSolucion);
bool combina(bool solucion1, bool solucion2, int num);

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
    int p[n];
   for(int j = 0; j <= n; j++){
       p[j] = j;

   }

    int posibleSolucion;
    t0= std::chrono::high_resolution_clock::now(); 
    bool resultado = FuerzaBrutaEj3(p, n, 0, n-1, n, posibleSolucion);
    tf = std::chrono::high_resolution_clock::now();
		
    
    if (resultado)
        cout << "\nPara 'n' = " << n << " 'y' = " << posibleSolucion << endl;
    else
        cout << "\nNo existe un numero natural para 'n' "<<n << endl;
    

    unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

    cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;
   
    
}

bool FuerzaBrutaEj3(int p[], int tam, int posIni, int posFin, int num, int &posibleSolucion){
    /*int resultado;
    while (n != resultado && i<n){
        ++i;
        resultado = i*(i+1)*(i+2);
    }
    return resultado;*/

    bool solucion1 = -1; 
    bool solucion2 = -1; 
    bool solucion = -1; 

    

    int aux1 = -1; 
    int aux2 = -1; 

    if(tam == 1){
        aux1 = p[posIni]*(p[posIni]+1)*(p[posIni]+2); 
        aux2 = p[posIni+1]*(p[posIni+1]+1)*(p[posIni+1]+2);

        if (aux1 == num){
            solucion =true;
            posibleSolucion= posIni;
        }else if (aux2 == num){
            solucion = true;
            posibleSolucion = posIni+1;
        }else 
            solucion = false;
    }
    else{
        int centro = (posIni+posFin)/2; 
        solucion1 = FuerzaBrutaEj3(p, tam/2, posIni, centro, num, posibleSolucion);
        solucion2 = FuerzaBrutaEj3(p, tam/2, centro+1, posFin, num, posibleSolucion);
        solucion = combina(solucion1, solucion2, num);
    }
    //cout << "Probado para " << tam << " : " << aux1 << " " << aux2 << " " << solucion <<endl << endl;
    return solucion;

    
    
}

bool combina(bool solucion1, bool solucion2, int num){
    if (solucion1 == true || solucion2 == true){
        return true; 
    }
    if(solucion1 == false && solucion2 == false)
        return false;
}