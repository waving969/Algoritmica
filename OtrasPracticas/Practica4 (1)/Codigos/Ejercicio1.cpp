#include <iostream>

using namespace std; 

int main(){
    int tam = 5; //ejemplo de un tamaño de 5 diccionarios con 5 idiomas
    int tam2;
    int k;
    int i;
    int j;
    int continuar;
    int contar = 0;
    cout << "introduzca el idioma origen " << endl; 
    cin >> i; 

    cout << "introduzca el idioma destino " << endl; 
    cin >> j; 

    cout << "Pulsa una tecla para avanzar " << endl; 
    cin >> continuar; 
    int traducir[tam][tam] = {
    {0, 1, 2, 2, 1},    //latin
    {1, 0, 1, 2, 2},    //griego
    {2, 1, 0, 1, 2},    //etrusco
    {2, 2, 1, 0, 1},    //Arameo
    {1, 2, 2, 1, 0}     //demotico
  };
  /*int traducir[tam][tam] = {
    {0, 0, 1, 4, 0},    //latin
    {0, 0, 0, 2, 0},    //griego
    {1, 0, 0, 0, 3},    //etrusco
    {4, 2, 0, 0, 0},    //Arameo
    {0, 0, 3, 0, 0}     //demotico
  };*/
 /* int traducir[tam][tam] = {
    {0, 1, 0, 0, 0},    //latin
    {1, 0, 1, 0, 1},    //griego
    {0, 1, 0, 0, 1},    //etrusco
    {0, 0, 0, 0, 1},    //Arameo
    {0, 1, 1, 1, 0}     //demotico
  };*/
  
  int tamk = 0;
  for (int i = 0; i <tam; i++){
        for (int j = 0; j<tam; j++){        
        cout << traducir[i][j] << " " ;
        }
        cout << endl;
    }
    int D[tam][tam];
    int T[tam][tam];
   
     for (int i = 0; i <tam; i++){
        for (int j = 0; j<tam; j++){
                D[i][j] = traducir[i][j];
                T[i][j] = 0;      
        }
    }
    for (k = 0; k <tam; k++){
        for (int i = 0; i<tam; i++){
            for (int j = 0; j<tam; j++){
               int dt = D[i][k] + D[k][j];
                if(D[i][j] > dt){
                    D[i][j] = dt;
                    T[i][j] = k;
                    
                }
            }
        }
    }
            
    cout <<"Tenemos " << tam << " idiomas" << endl;

    cout <<"Minimo de traducciones necesarias: " << D[i][j] << endl;
 
    
           
}