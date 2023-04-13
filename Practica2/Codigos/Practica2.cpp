#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <cstring> // Para usar memcpy
#include <iostream>
#include <fstream> // Para usar ficheros
#include <vector>
#include <algorithm>
#include "Punto.hpp"

using namespace std;

bool estaEnLista(int pos, int *indices, int tam);
bool domina(Punto p1, Punto p2);
void algoritmoFuerzaBruta(Punto *PuntosFuertes, int &auxPuntosFuertes, Punto *vector_puntos, int n);
int menu(bool &debug);
void algoritmoDyV(Punto *PuntosFuertes, int &auxPuntosFuertes, Punto *vector_puntos, int ini, int fin);
Punto *algoritmoDyV2(Punto *vector_puntos, int tam);
Punto *fusiona(Punto *izda, Punto *dcha, int tam);
int main(int argc, char *argv[]){
    Punto *vector_puntos;
    //vector<Punto> vector_puntos;
	int n, i, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	double tejecucion; // tiempo de ejecucion del algoritmo en ms
	unsigned long int semilla;
	ofstream fsalida;
    ofstream fsalida2;
    bool debug;

    if (argc <= 4) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida NombreFicheroSalida2 Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}

    // Abrimos fichero de salida
	fsalida.open(argv[1]);
    fsalida2.open(argv[2]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}

    // Inicializamos generador de no. aleatorios
	semilla= atoi(argv[3]);

    int opcion = menu(debug);

    // Pasamos por cada tamaÒo de caso
	for (argumento= 4; argumento<argc; argumento++) {
		
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

        for(int i =0 ; i < n; i++){
            fsalida << "Punto " << i << " :" << endl;
            fsalida << vector_puntos[i].to_string();

            fsalida << endl << endl;
        }

        
        cout << "Debug "<< debug << endl;
        Punto *PuntosFuertes;
        PuntosFuertes = new Punto[n];
        if(debug){
            Punto puntoDebug(debug,9);
            vector_puntos[n-1] = puntoDebug;
        }
        int auxPuntosFuertes = 0;
        t0= std::chrono::high_resolution_clock::now();
        switch (opcion)
        {
        case 1:
            algoritmoFuerzaBruta(PuntosFuertes, auxPuntosFuertes, vector_puntos, n);
            break;
        case 2: 
            algoritmoDyV(PuntosFuertes, auxPuntosFuertes, vector_puntos, 0,n);
            break;
        case 3: 
            PuntosFuertes = algoritmoDyV2(vector_puntos, n);
            break;
        default:
            cerr << "Salida " << endl;
            break;
        }
        tf= std::chrono::high_resolution_clock::now();
        unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n_original<<endl;
    
        cout << "Numero de puntos dominantes: " << sizeof(PuntosFuertes) << endl << endl;
        /*for(int i = 0; i < auxPuntosFuertes; i++){
           fsalida2 << "Punto Fuerte: " << PuntosFuertes[i].to_string() << endl;
        }*/

        delete[] vector_puntos;
        delete [] PuntosFuertes;
    }         
}


int menu(bool &debug){
    int opcion;
    int a;
    cout << "Elija la opcion que desee: " 
        << endl << "\t1: Para ejecutar algoritmoFuerzaBruta "
        << endl << "\t2: Para ejecutar implementacion1 DyV" 
        << endl << "\t3: Para ejecutar implementacion2 DyV" << endl; 
    cin>>opcion;

    switch (opcion)
    {
    case 1:
        cout << "\nAlgoritmoFuerzaBruta\n" << endl;
        opcion = 1;
        break;
    case 2:
        cout << "\nimplementacion1 DyV\n"<< endl;
        opcion = 2;
        break;
    case 3: 
        cout << "\nimplementacion2 DyV\n"<< endl;  //problema de seleccion
        opcion = 3;
        break;
    default:
        cerr<<"\nError: debe seleccionar un valor valido entre 1-5";
        return 0;
        break;
    }

    cout << "¿Deseas activar el debug? \n\t1.-no\n\t2.-Si" << endl;
    cin >> a;

    if(a == 1)
        debug = false;
    else 
        debug = true;

    return opcion;
}


bool domina(Punto p1, Punto p2) {
    bool domina = false;
    for (int i = 0; i < TAM; i++) {
        if (p1.getK(i) < p2.getK(i)) {
            return false;
        }
        else if (p1.getK(i) > p2.getK(i)) {
            domina = true;
        }
    }
    return domina;
}


bool estaEnLista(int pos, int *indices, int tam){
        for(int i = 0; i < tam; i++){
            if(pos == indices[i]){
                //cout << "esta dentro de la lista " << endl;
                return true;
            }
        }
        //cout << "No esta en la lista " << endl;
        return false;
    }

void algoritmoFuerzaBruta(Punto *PuntosFuertes, int &auxPuntosFuertes, Punto *vector_puntos, int n){
    for(int i = 0; i < n; i++){
        bool esDominado = false;
        for(int j = 0; j < n; j++){
            if(vector_puntos[j].dominaPunto(vector_puntos[i])){
                esDominado = true;
                break; 
            }
        }
        if(!esDominado){
             PuntosFuertes[auxPuntosFuertes] = vector_puntos[i];
            auxPuntosFuertes++;
        }
    }
}

void algoritmoDyV(Punto *PuntosFuertes, int &auxPuntosFuertes, Punto *vector_puntos, int ini, int fin){
    int aux1 = 0;
    int aux2 = 0;
    Punto * Puntos1 = new Punto[fin];
    Punto * Puntos2 = new Punto[fin];

    algoritmoDyV(Puntos1,aux1, vector_puntos,0,fin/2);
    algoritmoDyV(Puntos2,aux2, vector_puntos,fin/2+1, fin);


    for(int i = ini; i < fin; i++){
            bool esDominado = false;
            for(int j = ini; j < fin; j++){
                if(vector_puntos[j].dominaPunto(vector_puntos[i])){
                    esDominado = true;
                    break; 
                }
            }
            if(!esDominado){
                PuntosFuertes[auxPuntosFuertes] = vector_puntos[i];
                auxPuntosFuertes++;
            }
    }
   


    
}

Punto *divideMitad(int ini, int fin, Punto *vector){
    Punto *devolver = new Punto[fin];
    for(int i = ini; i<fin; i++){
        devolver[i] = vector[i];
    }

    return devolver;
}

Punto *fusiona(Punto *izda, Punto *dcha, int tam){
    Punto *resultado = new Punto[tam];    
    int i ,j, aux = 0; 
    int tam_izq = sizeof(izda);
    int tam_der = sizeof(dcha);
    while (i<tam_izq && j<tam_der){
        if(!izda[i].dominaPunto(dcha[j])){
            resultado[aux] = izda[i];
            aux++;
            i++;
        }else{
            resultado[aux] = dcha[j];
            aux++;
            j++;
        }
    }

    while(i<tam_izq){
        resultado[aux] = izda[i];
        i++;
        aux++;
    } 
    while(j<tam_der){
        resultado[aux] = dcha[j];
        aux++;
        j++;
    }

    return resultado;
    
}

Punto *algoritmoDyV2(Punto *vector_puntos, int tam){
    bool esDominado = false;
    int auxPuntosFuertes = 0;
    //caso base
    if(tam == 1){
        vector_puntos[0].setDominador(false);
    }

    int mid = tam/2;

    Punto *izq = new Punto[mid];
    Punto *der = new Punto[mid];
    izq = divideMitad(0,mid, vector_puntos);
    der = divideMitad(mid+1, tam, vector_puntos);

    Punto *puntosFuertes = new Punto[tam];

    izq = algoritmoDyV2(izq,mid);
    der = algoritmoDyV2(der,mid);

    puntosFuertes = fusiona(izq,der,tam);

    /*for(int i = 0; i < tam; i++){
        if(!puntosFuertes[i].getDominador()){
            for(int j = i+1; j < tam; j++){
                if(!puntosFuertes[j].getDominador()){
                    esDominado = false;
                    if(vector_puntos[j].dominaPunto(vector_puntos[i])){
                        esDominado = true;
                        break; 
                     }
                }
                if(!esDominado){
                    puntosFuertes[auxPuntosFuertes] = vector_puntos[i];
                    auxPuntosFuertes++;
                    }
                }           
            }
        }*/

    return puntosFuertes;
}