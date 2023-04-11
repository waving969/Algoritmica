#include<iostream>

using namespace std; 

void eliminaComponentes(int v[], int tam, int *v_copia, int &tam_copia);
int* eliminaComponentes2(int *v, int tam, int &tam_copia); //Debe de devolver el mismo vector, no uno diferente
void eliminaComponentesOrdenados(int *v, int &tam); //No funciona con 3 o mas numeros seguidos repes 
void eliminaComponentes3(int *v, int &tam);


int main(){
    int v[5] = {2,4,1,2,4}; 
    int v_ordenado[5] = {1,2,2,3,3};
    int tam = 5; 
    int *v_copia; 
    int tam_copia = 0; 
    bool terminado = false; 
    int aux = 0;
    bool copiaRealizada = false;
    bool repetido = false;

    v_copia = new int[tam];
    for(int i = 0; i < tam ;i ++){
        v_copia[i] = -1;
    }

    for(int i = 0; i < tam+1; i++)
        cout << " " << v[i] << " ";
    cout << endl;

    //eliminaComponentes(v, tam, v_copia, tam_copia);
    //eliminaComponentesOrdenados(v_ordenado, tam);
    eliminaComponentes3(v,tam);
    int *v_copia2; 
    v_copia2=new int[tam];
    //v_copia2=eliminaComponentes2(v, tam, tam_copia);

    for(int i = 0; i < tam; i++)
        cout << " " << v[i] << " "; 
    cout << endl;

    delete[] v_copia;
}

void eliminaComponentes(int v[], int tam, int *v_copia, int &tam_copia){
    //int tam_copia;
   //int v_copia[tam];
    int k = 0;
    bool terminado = false;
    int aux = 0;
    bool repetido = false;
    bool copiaRealizada = false;

    v_copia[0] = v[0];
    tam_copia++;

    while (!terminado){
        for(k = 0; k<tam_copia && !repetido; k++)
            if (v[aux] == v_copia[k]){
                cout << "Repetido " << v[aux] << " en " << k << " Iteracion " << aux << endl;
                repetido = true;
            }else if (k == tam_copia-1){ 
                cout << "No se repite "<< v[aux] << endl;
                v_copia [tam_copia] = v[aux];
                copiaRealizada = true;
            }
        cout << "   Nueva Iteracion "<< endl << endl;
        repetido = false;

        if(copiaRealizada)
            tam_copia++;
        if(aux == tam-1)
            terminado = true;
        
        //cout << "tam_copia " << tam_copia << endl;
        aux++;
        copiaRealizada = false;
    }

    for(int i = 0; i < tam_copia; i++)
        cout << " " << v_copia[i] << " "; 
    cout << endl;
    
}

int *eliminaComponentes2(int v[], int tam, int &tam_copia){
    int *v_copia =new int[tam];
    int k = 0;
    bool terminado = false;
    int aux = 0;
    bool repetido = false;
    bool copiaRealizada = false;

    v_copia[0] = v[0];
    tam_copia++;

    while (!terminado){
        for(k = 0; k<tam_copia && !repetido; k++)
            if (v[aux] == v_copia[k]){
                cout << "Repetido " << v[aux] << " en " << k << " Iteracion " << aux << endl;
                repetido = true;
            }else if (k == tam_copia-1){ 
                cout << "No se repite "<< v[aux] << endl;
                v_copia [tam_copia] = v[aux];
                copiaRealizada = true;
            }
        cout << "   Nueva Iteracion "<< endl << endl;
        repetido = false;

        if(copiaRealizada)
            tam_copia++;
        if(aux == tam-1)
            terminado = true;
        
        //cout << "tam_copia " << tam_copia << endl;
        aux++;
        copiaRealizada = false;
    }

    return  v_copia;
    
}

void eliminaComponentesOrdenados(int *v, int &tam){
    bool ordenado = false;
    int i = 0; 
    int aux_tam = tam;
    int aux_int = -1;
    int aux_i = i;

    while (!ordenado){
        cout << "Comparando v[" << i << "]: " << v[i] << " con v["<<i+1<<"]: " << v[i+1] << endl;
        if (v[i] == v[i+1]){
            cout << "   Son iguales "<< endl;
            if(i+1 >= tam-1){
                //aux_tam--;
            }else{
                for (int k = i; k<aux_tam; k++)
                    v[k] = v[k+1];
                aux_tam--;
            }
        }

        cout<<endl << "aux_tam " << aux_tam << endl;
        i++;

        if(i == tam-1)
            ordenado = true;
    }

    cout << "Ordenado " << endl;
    for(int i = 0; i < aux_tam; i++)
        cout << " " << v[i] << " "; 
    cout << endl;
}

void eliminaComponentes3(int *v, int &tam){
    int tam_copia = 0;
    int v_copia[tam];
    int k = 0;
    bool terminado = false;
    int aux = 0;
    bool repetido = false;
    bool copiaRealizada = false;

    v_copia[0] = v[0];
    tam_copia++;

    while (!terminado){
        for(k = 0; k<tam_copia && !repetido; k++)
            if (v[aux] == v_copia[k]){
                cout << "Repetido " << v[aux] << " en " << k << " Iteracion " << aux << endl;
                repetido = true;
            }else if (k == tam_copia-1){ 
                cout << "No se repite "<< v[aux] << endl;
                v_copia [tam_copia] = v[aux];
                copiaRealizada = true;
            }
        cout << "   Nueva Iteracion "<< endl << endl;
        repetido = false;

        if(copiaRealizada)
            tam_copia++;
        if(aux == tam-1)
            terminado = true;
        
        //cout << "tam_copia " << tam_copia << endl;
        aux++;
        copiaRealizada = false;
    }

    v = v_copia;
    tam = tam_copia;
    
    cout << "Dentro funcion: " << endl;
    for(int i = 0; i < tam_copia; i++)
        cout << " " << v_copia[i] << " "; 
    cout << "\nFuera funcion "<< endl;
}