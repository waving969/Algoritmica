#include "Punto.hpp"
#include<iostream>
#include <cstdlib>



using namespace std;

Punto::Punto(int semilla){
    
    ocupados = 0;
    
    //srand(time(NULL));
    srand(semilla);
    for (int i = 0; i < TAM; i++){
        k[i] = rand()%TAM;
    }

}

Punto::Punto(bool debug, int num){
    for(int i = 0; i < TAM; i++){
        k[i] = num;
    }
}

Punto::Punto(){
    for(int i = 0; i < TAM; i++)
        k[i] = 0;
    ocupados = 0; 
}

int Punto::getPrimerPunto(){
    return k[0];
}

void Punto::mostrarCoordenadas(){
    for(int i = 0; i < TAM; i++)
        cout << "\nCoordenada  " << i << " : " << k[i];
}

int Punto::getK(int i){
    return k[i];
}


int Punto::getOcupados(){
    return ocupados;
}

bool Punto::dominaPunto(Punto otroPunto){
    bool domina = false;
    for(int i = 0; i < TAM; i++){
        if(this->getK(i) > otroPunto.getK(i))
            domina = true;
        else if(this->getK(i) < otroPunto.getK(i)){
            domina = false;
            break;
        }
    }
    return domina;
}

bool Punto::dominaPunto2(Punto otroPunto){
    bool noDomina = true;
    int aux = 0;
    for(int i = 0; i < TAM && noDomina; i++){
        if(this->getK(i) <= otroPunto.getK(i)){
            noDomina = false;
        
        }else{
            noDomina = true;
        }
    }
    return noDomina;
}

std::string Punto::to_string(){
    string devuelve = "";
    int i;
    for(i = 0; i < TAM; i++)
        devuelve += "\nCoordenada  " +  std::to_string(i) + " : " + std::to_string(k[i]);
    return devuelve;
}

