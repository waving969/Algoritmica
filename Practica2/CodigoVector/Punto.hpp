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
    bool posibleDomidador;

public:
    Punto(int semilla);
    Punto();
    Punto(bool debug, int num);

    void setDominador(bool _posibleDominador);

    void asignarPuntos(); 
    void mostrarCoordenadas();
    void setPunto(Punto punto);
    //void liberarMemoria();
    int getPrimerPunto();
    bool dominaPunto(Punto otroPunto);
    bool dominaPunto2(Punto otroPunto);
    int getK(int i);
    int getOcupados();
    bool getDominador();

    std::string to_string();
};

#endif