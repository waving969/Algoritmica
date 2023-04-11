#ifndef PUNTO_H
#define PUNTO_H
#include<iostream>
#include<vector>


const int TAM = 10;

class Punto{
private: 
    int k[TAM]; 
    int ocupados; 
    int semilla;

public:
    Punto(int semilla);
    Punto();
    Punto(bool debug, int num);

    void asignarPuntos(); 
    void mostrarCoordenadas();
    void setPunto(Punto punto);
    //void liberarMemoria();
    int getPrimerPunto();
    bool dominaPunto(Punto otroPunto);
    bool dominaPunto2(Punto otroPunto);
    int getK(int i);
    int getOcupados();

    std::string to_string();
};

#endif