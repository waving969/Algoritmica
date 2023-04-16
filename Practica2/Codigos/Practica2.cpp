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
vector<Punto> algoritmoFuerzaBruta(vector<Punto>& vector_puntos);
int menu(bool &debug);
vector<Punto> algoritmoDyV(vector<Punto>& vector_puntos);
vector<Punto> algoritmoDyV2(vector<Punto>& vector_puntos);
vector<Punto> fusiona(vector<Punto>& izda, vector<Punto>& dcha);

template <typename T>
std::vector<T> operator+(const std::vector<T>& A, const std::vector<T>& B)
{
    std::vector<T> AB;
    AB.reserve( A.size() + B.size() );
    AB.insert( AB.end(), A.begin(), A.end() );        
    AB.insert( AB.end(), B.begin(), B.end() );        
    return AB;
}

template <typename T>
std::vector<T>& operator+=(std::vector<T>& A, const std::vector<T>& B)
{
    A.reserve( A.size() + B.size() );                
    A.insert( A.end(), B.begin(), B.end() ); 
    return A;
}


int main(int argc, char *argv[]){
    vector<Punto> vector_puntos;
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
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
        
		for (i= 0; i<n; i++){
           Punto Punto1 (semilla + i);
            vector_puntos.push_back(Punto1);
        }
        

        int coordenadas[TAM];

        for(int i =0 ; i < n; i++){
            fsalida << "Punto " << i << " :" << endl;
            fsalida << vector_puntos[i].to_string();

            fsalida << endl << endl;
        }

        
        cout << "Debug "<< debug << endl;
        vector<Punto> PuntosFuertes;

        if(debug){
            Punto puntoDebug(debug,9);
            vector_puntos[n-1] = puntoDebug;
        }
        int auxPuntosFuertes = 0;
        
        t0= std::chrono::high_resolution_clock::now();
        switch (opcion)
        {
        case 1:
            PuntosFuertes = algoritmoFuerzaBruta(vector_puntos);
            break;
        case 2: 
            
            PuntosFuertes = algoritmoDyV(vector_puntos);
            break;
        case 3: 
            PuntosFuertes = algoritmoDyV2(vector_puntos);
            break;
        default:
            cerr << "Salida " << endl;
            break;
        }
        tf= std::chrono::high_resolution_clock::now();
        unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
        
        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n_original<<endl;
        cout << "Numero de puntos dominantes: " << PuntosFuertes.size() << endl << endl;
        for(int i = 0; i <PuntosFuertes.size(); i++){
           fsalida2 << "Punto Fuerte: " << PuntosFuertes[i].to_string() << endl;
        }
       
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
    for (int i = 0; i < TAM; i++) {
        if (p1.getK(i) < p2.getK(i)) {
            return true;
        }
        else if (p1.getK(i) > p2.getK(i)) {
            return false;
        }
    }
    return false;
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

vector<Punto> algoritmoFuerzaBruta(vector<Punto>& vector_puntos){
    vector<Punto> PuntosFuertes;
    for(int i = 0; i < vector_puntos.size(); i++){
        bool esDominado = false;
        for(int j = 0; j < vector_puntos.size(); j++){
            if(vector_puntos[j].dominaPunto(vector_puntos[i])){
                esDominado = true;
                break; 
            }
        }
        if(!esDominado){
            PuntosFuertes.push_back(vector_puntos[i]);
        }
    }
    return PuntosFuertes;
}

vector<Punto> algoritmoDyV(vector<Punto>& vector_puntos){
   if(vector_puntos.size() == 1){
        return vector_puntos;
    }
    
    int mid = vector_puntos.size()/2;
    
    vector<Punto> izq(vector_puntos.begin(), vector_puntos.begin() + mid);
    vector<Punto> der(vector_puntos.begin() + mid, vector_puntos.end());
  
    izq = algoritmoDyV(izq);  
    der = algoritmoDyV(der);

   
     //IMPLEMENTACION 2 POSIBLE
    vector<Punto> puntosFuertes = fusiona(izq,der);
    
    return puntosFuertes;
}


vector<Punto> fusiona(vector<Punto>& izda, vector<Punto>& dcha){
    vector<Punto> resultado;  
    int i = 0;
    int j = 0; 
    while (i<izda.size() && j<dcha.size()){
        if(izda[i].dominaPunto(dcha[j])){
            resultado.push_back(izda[i++]);
        }else{
           resultado.push_back(dcha[j++]);
        }
    }

    while(i<izda.size()){
       resultado.push_back(izda[i++]);
    } 
    while(j<dcha.size()){
        resultado.push_back(dcha[j++]);
    }

    //Borrar si mal
    vector<Punto> puntos;
    for(int i = 0; i < resultado.size(); i++){
        bool esDominado = false;
        for(int j = 0; j < resultado.size(); j++){
            if(resultado[j].dominaPunto(resultado[i])){
                esDominado = true;
                break; 
            }
        }
        if(!esDominado){
            puntos.push_back(resultado[i]);

        }
    }

    return resultado;
    
}

vector<Punto> fusiona2(vector<Punto>& izda, vector<Punto>& dcha){
    vector<Punto> resultado;  
    int i = 0;
    int j = 0; 
    while (i<izda.size() && j<dcha.size()){
        if(!izda[i].dominaPunto(dcha[j])){
            resultado.push_back(izda[i++]);
        }else{
            resultado.push_back(dcha[j++]);
        }
    }

    while(i<izda.size()){
       resultado.push_back(izda[i++]);
    } 
    while(j<dcha.size()){
        resultado.push_back(dcha[j++]);
    }

    return resultado;
    
}

vector<Punto> algoritmoDyV2(vector<Punto>& vector_puntos){  
    if(vector_puntos.size() == 1){
        vector_puntos[0].setDominador(false);
        return vector_puntos;
    }
    

    int mid = vector_puntos.size()/2;
    
    vector<Punto> izq(vector_puntos.begin(), vector_puntos.begin() + mid);
    vector<Punto> der(vector_puntos.begin() + mid, vector_puntos.end());

       

    
    izq = algoritmoDyV2(izq);
    
    der = algoritmoDyV2(der);
    //cout << "Antes" << endl;
   
    vector<Punto> puntosFuertes = fusiona2(izq,der);

    //cout << puntosFuertes[0].to_string() << endl;
    

    /*for(int i = 0; i < puntosFuertes.size(); i++){
        for (int j = i+1; j < puntosFuertes.size(); j++){
            puntosFuertes[i].setDominador(puntosFuertes[i].dominaPunto(puntosFuertes[j]));
            if(puntosFuertes[i].getDominador())
                break;
        }
    }*/

    // Filter out dominated points
    vector<Punto> noDominado;
    
    for(int i = puntosFuertes.size(); i>0; i++){
        if(!puntosFuertes[i].dominaPunto(puntosFuertes[i-1]))
            noDominado.push_back(puntosFuertes[i]);
    }
    return  noDominado;


}

vector<Punto> algoritmoDyV3(vector<Punto> &vector_puntos, int inicio, int fin){
    if(inicio == fin){
        vector<Punto> resultado; 
        resultado.push_back(vector_puntos[inicio]); 
        return resultado;
    }

    
}