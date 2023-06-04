/*
La unidad aritmético-lógica (ALU) de un microcontrolador de consumo ultrabajo no dispone de la
operación de multiplicación. Sin embargo, necesitamos multiplicar un número natural i por otro
número natural j, que notamos como i*j. Sabemos, por la definición matemática de la operación de
multiplicación en los números naturales, que:
                                 {      i j=1                }
                            i∗j= {                           }∀i , j∈N
                                 {      i∗( j−1)+i j>1       }


Autores:    Juan Navarro Maldonado
            Joaquin Sergio Garcia Ibañez


*/
#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;

int AlgoritmoBasico(int i, int j);

int main(int argc, char *argv[]){
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
    cout<<"Calculo de la multiplicacion en la ALU" << endl; 

    if (argc <= 1) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida num1 num2";
		return 0;
	}

    int tam = atoi(argv[1]); 
    int multiplicador[tam];
    int multiplicando[tam];

    for(int i = 0; i<=tam; i++){
        multiplicador[i] = rand()%10;
        multiplicando[i] = rand()%10;

        if (multiplicador[i] < 0)
            multiplicador[i] = multiplicador[i] * -1;
        
        if (multiplicando[i] < 0)
            multiplicando[i] = multiplicando[i] * -1;

    }

    
   
       
    t0= std::chrono::high_resolution_clock::now(); 
    //int j = atoi(argv[2]);  rand()%10;
    int resultado; 
    for(int i = 0; i < tam; i++){
    resultado = AlgoritmoBasico(multiplicando[i],multiplicador[i]);

    //cout <<"\n Resultado = " << resultado << endl;
}
    tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< tam<<endl;

}

int AlgoritmoBasico(int i, int j){
    int resultado;
    if (j == 1){
        resultado = i; 
    }
    else if(j >= 0){
        resultado = i*(j-1)+i; 
    }
    else{
        cerr<<"\n Error: Los numeros introducidos deben de ser enteros y positivos";
    }

    return resultado;
}