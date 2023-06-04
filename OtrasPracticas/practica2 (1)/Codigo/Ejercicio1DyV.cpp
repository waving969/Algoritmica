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

int *multiplicaDyV(int multiplicando[], int multimplicador[], int tam, int posIni, int posFin);
int *combina(int solucion1[], int solucion2[], int tam);
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

    
   int i = 0;
       
    t0= std::chrono::high_resolution_clock::now(); 
   
    
    int *resultado = multiplicaDyV(multiplicando,multiplicador, tam, 0, tam);
    

    tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo	




    
	unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
	cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< tam<<endl;


   

}

int *multiplicaDyV(int multiplicando[], int multiplicador[], int tam, int posIni, int posFin){
    int *solucion1 = new int[tam];
    int *solucion2 = new int[tam];
    int *solucion = new int[tam];

    
    if (tam == 1){
        if (multiplicador[posIni] == 1){
            solucion[posIni] = multiplicando[posIni];
        }
        else if (multiplicador[posIni]>=0 && multiplicador[posIni] != 1){
            solucion[posIni] = multiplicando[posIni] * (multiplicador[posIni]-1)+multiplicando[posIni];
        }
    }
    else{
        
        int centro = (posIni+posFin)/2; 
        solucion1 = multiplicaDyV(multiplicando, multiplicador, tam/2, posIni, centro);
        solucion2 = multiplicaDyV(multiplicando, multiplicador, tam/2, centro+1, posFin);
        solucion = combina(solucion1, solucion2, tam);
    }


    return solucion;
}


int *combina(int solucion1[], int solucion2[], int tam){
    int i = 0;
    int *solucion = new int[tam];
    while(i < tam){
        if(i < tam/2){
         solucion[i] = solucion1[i];  
        }
        else{
             solucion[i] = solucion2[i];   
             
        }
        i++;
    }
    return solucion;
}
