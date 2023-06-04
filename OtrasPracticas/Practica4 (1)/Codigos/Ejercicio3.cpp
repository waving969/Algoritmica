#include <iostream>

using namespace std; 

int main(){
    int tam;
    char continua;
    cout << "introduzca el tamaño del mapa " << endl; 
    cin >> tam; 

    int mapa[tam][tam]; 
    int D[tam][tam];
    int T[tam][tam];

    //Inicio estará en la posicion mapa[0][tam]
    //Salida estará en la posicion mapa [tam][0]

    //Debemos rellenar las casillas con los costes de cada una
    /* 3 tipos de terreno: 
            1.- Coste bajo
            2.- Coste medio 
            3.- Coste alto

        3 movimientos: 
            1.- Subir -> i-- j
            2.- Subir y derecha -> i-- j++
            3.- Derecha -> i j++

        Objetivo -> llegar a i=0 j=tam                                                  
                                                                        
    */                                                                        
                                                                             
   //Tablero por defecto                                                    
    int coste_terreno[3] = {10, 50, 99}; 
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            int a = rand() % 3; 
            mapa[i][j] = coste_terreno[a]; 
        }
    }
    //Debemos de tener en cuenta el coste de la ultima casilla, que sera el objetivo = 0
    mapa[0][tam-1] = 0;
   
    cout << "Mostrando mapa: " << endl; 
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            if (i==tam-1 && j==0)
                cout <<"R  ";
            else if (i==0 && j==tam-1){
                cout << "O  "; 
            }
            else 
                cout << mapa[i][j] << " " ;
            
        }
        cout << endl;
    }

    cout << "Pulsa cualquier tecla para continuar" << endl;
    cin >> continua; 


    int posF = tam-1,posC = 0;
    int costes[3]; 
    int camino[100];
        int tam_camino = 0;
        bool termina = false;
        bool ultima_fila = false;
        bool ultima_columna = false;
    cout << "posF: " << posF << endl << "posC: " << posC << endl;
    
    
    //Algoritmo de busqueda del camino minimo
    while(!termina){
        int auxF = posF; 
        int auxC = posC;
        

        for (int i = 0; i < 3; i++){
            costes[i] = 0;
        }
        costes[0] = mapa[--auxF][auxC];
         auxF = posF; 
         auxC = posC;
        costes[1] = mapa[--auxF][++auxC];
         auxF = posF; 
         auxC = posC;
        costes[2] = mapa[auxF][++auxC];
         auxF = posF; 
         auxC = posC;

        cout << "costes :";
        for (int i = 0; i<3; i++)
            cout <<costes[i] << " ";
        cout << endl;
    
        cout << "Prueba mapa: " << mapa[auxF][++auxC] << endl;        
        cout << "posF: " << posF << endl << "posC: " << posC << endl;

        //Calculamos el minimo de los 3 valores
        int i; 
        int menor = 1000000;

        if (menor>costes[0]){ 
           menor = costes[0];
           i = 0;
        }
        if (menor>costes[1]){ 
           menor = costes[1];
           i = 1;
        }
        if (menor>costes[2]){ 
           menor = costes[2];
           i = 2;
        }
        

        cout << "Mostrando mapa: " << endl; 
    for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam; j++){
            if (i==posF && j==posC)
                cout <<"R  ";
            else if (i==0 && j==tam-1){
                cout << "O  "; 
            }
            else 
                cout << mapa[i][j] << " " ;
            
        }
        cout << endl;
    }

    //Condicion ultima fila
    if (posF == 0){
        ultima_fila = true;
    }
    if (posC == tam-1)
        ultima_columna = true;

    if (!ultima_fila && !ultima_columna){
        if (i == 0)
            --posF; 
        else if(i==1){
            --posF; 
            ++posC; 
        }else if(i == 2)
            ++posC;
    }
    if(ultima_fila){
        i=2; 
        ++posC;
    }
    if (ultima_columna){
        i =0; 
        --posF;
    }
    cout << "menor " << i << endl << "valor: " << menor << endl;
        camino[tam_camino] = costes[i];
        tam_camino++; 

    if (posF==0 && posC == tam-1){
        cout << "Termina ejecucion" << endl; 
        termina = true;
    }   
        cout << "cambia pos nueva: " << endl; 
        cout << posF << " " << posC << endl;
        cout << "Pulsa cualquier tecla para continuar" << endl;
        cin >> continua; 
    }
    //___________________________FIN_ALGORITMO___________________________
    
    
    //Algoritmo recupera solucion
    int camino_total = 0;
    cout << "Camino recorrido: " << endl; 
    for (int i = 0; i < tam_camino; i++){
        camino_total = camino[i] + camino_total;
        cout << camino[i] << "-> ";
    }
    cout << "Coste total: " << camino_total << endl;
     //___________________________FIN_ALGORITMO_RECUPERACION__________________________
    
}