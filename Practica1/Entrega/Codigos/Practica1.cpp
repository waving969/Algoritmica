    // Ejemplo de la ordenacion por burbuja sobre un vector de enteros

#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <cstring> // Para usar memcpy
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;

void OrdenaBurbuja(int *v, int n);
int menu();

//Algoritmos Iterativos
void eliminaComponentesOrdenados(int *v, int &tam); 
void eliminaComponentesDesordenado(int *v, int &tam); //Version Inicial menos eficiente
void eliminaComponentesDesordenado2(int *v, int &tam);//Version Final

//Algoritmos Recursivos
void hanoi(int M, int i, int j); 
void HeapSort(int *v, int n);
void insertarEnPos(double *apo, int pos); 
void reestructurarRaiz(double *apo, int pos, int tamapo);
void MergeSort(int *v, int posIni, int posFin, int *vaux);
void fusionaMS(int *v, int posIni, int centro, int posFin, int *vaux);



int main(int argc, char *argv[]) {
	
	int *v;
    int *vaux;
	int n, i, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	double tejecucion; // tiempo de ejecucion del algoritmo en ms
	unsigned long int semilla;
	ofstream fsalida;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	// Inicializamos generador de no. aleatorios
	semilla= atoi(argv[2]);
	srand(semilla);

    int opcion = menu();
	
	// Pasamos por cada tamaÒo de caso
	for (argumento= 3; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
        int n_original = n;
		
		// Reservamos memoria para el vector
		v= new int[n];
        vaux= new int[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			v[i]= rand()%n;
		
		
        if(opcion == 2){
            cerr << "Ejecutando Burbuja para tam. caso: " << n << endl;
            //OrdenaBurbuja(v, n); // Ejecutamos el algoritmo para tamaÒo de caso tam
            HeapSort(v,n);
        }
        int M,i,j;
        if(opcion == 3){
            cout << "Introduce M" << endl; 
                cin >> M; 
            cout << "Introduce i (valores entre [1,2,3])" << endl;
                cin >> i;
            cout << "Introduce j (valores entre [1,2,3])" << endl;
                cin >> j; 
        }

        if(n_original <= 100 ){
            fsalida << "vector Original: " << endl;
            for (int i = 0; i < n; i++)
                fsalida << v[i] << " " ;
        }

		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
        switch (opcion)
        {
        case 1:
            eliminaComponentesDesordenado2(v,n);
            break;
        case 2: 
            eliminaComponentesOrdenados(v,n);
            break;
        case 3: 
            hanoi(M,i,j);
            break;
        case 4: 
            HeapSort(v,n);
            break;
        case 5: 
            MergeSort(v,0,n-1,vaux);
            break;
        default:
            cerr << "Salida " << endl;
            break;
        }
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n_original<<endl;

        if (n_original <= 100){
            fsalida << "\nVector modificado: " << endl; 

            for(int i = 0; i < n; i++)
                fsalida << v[i] << " " ;
        }
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<"\nTamano Caso: "<<n_original<<"\t\tTiempo de ejecucion: "<<tejecucion<<"\n\n";
		
		/*for(int i = 0; i < n; i++){
			cout << " " << v[i] << " " << endl;
		}*/
		
		// Liberamos memoria del vector
		delete [] v, vaux;
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;      
}


void OrdenaBurbuja(int *v, int n) {
	
	int i, j, aux;
	bool haycambios= true;
	
	i= 0;
	while (haycambios) {
		
	 haycambios=false; // Suponemos vector ya ordenado
	 for (j= n-1; j>i; j--) { // Recorremos vector de final a i
		 
		 if (v[j-1]>v[j]) { // Dos elementos consecutivos mal ordenados
		  aux= v[j]; // Los intercambiamos
		  v[j]= v[j-1];
		  v[j-1]= aux;
		  haycambios= true; // Al intercambiar, hay cambio
		 }
	 }
	 i++;
	}
}

int menu(){
    int opcion;
    cout << "Elija la opcion que desee: " 
        << endl << "\t1: Para ejecutar eliminaComponentesRepetidas vector desordenado. "
        << endl << "\t2: Para ejecutar eliminaComponentesRepetidas vector ordenado" 
        << endl << "\t3: Para ejecutar Hanoi"
        << endl << "\t4: Para ejecutar HeapSort"
        << endl << "\t5: Para ejecutar MergeSort" << endl; 
    cin>>opcion;

    switch (opcion)
    {
    case 1:
        cout << "\nEjercicio 1\n" << endl;
        return opcion;
        break;
    case 2:
        cout << "\nEjercicio 2\n"<< endl;
        return opcion;
        break;
    case 3: 
        cout << "\nHanoi\n"<< endl; 
        return opcion;
        break;
    case 4: 
        cout << "\nHeapSort\n"<<endl;
        return opcion;
        break;
    case 5:
        cout << "\nMergeSort\n" << endl; 
        return opcion;
        break;
    default:
        cerr<<"\nError: debe seleccionar un valor valido entre 1-5";
        return 0;
        break;
    }
}


void eliminaComponentesOrdenados(int *v, int &tam){
    bool ordenado = false;
    int i = 0; 
    int aux_tam = tam;
    int aux_int = -1;
    int aux_i = i;

    while (!ordenado){
        if (v[i] == v[i+1]){
            for(int k = i; k<tam; k++)
                v[k] = v[k+1];
            aux_tam--;
        }else 
            i++;

        if(i == aux_tam-1)
            ordenado = true;
    }
    tam = aux_tam;
}

//Version Inicial
void eliminaComponentesDesordenado(int *v, int &tam){
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
                //cout << "Repetido " << v[aux] << " en " << k << " Iteracion " << aux << endl;
                repetido = true;
            }else if (k == tam_copia-1){ 
                //cout << "No se repite "<< v[aux] << endl;
                v_copia [tam_copia] = v[aux];
                copiaRealizada = true;
            }
        //cout << "   Nueva Iteracion "<< endl << endl;
        repetido = false;

        if(copiaRealizada)
            tam_copia++;
        if(aux == tam-1)
            terminado = true;
        
        //cout << "tam_copia " << tam_copia << endl;
        aux++;
        copiaRealizada = false;
    }

    for (int i= 0; i< tam_copia; i++){
        v[i] = v_copia[i];
    }

    //v = v_copia;
    tam = tam_copia;
}

//Version Final
void eliminaComponentesDesordenado2(int *v, int &tam){
    int tam_copia = 0;
    int v_copia[tam];
    int k= 0;
    int i = 1;
    bool terminado = false;
    int aux = 0;
    bool repetido = false;
    bool copiaRealizada = false;
    bool encontrado = false;

    v_copia[0] = v[0];
    tam_copia++;
    //cout << "Bucles anidados " << endl;
    while (!terminado){
        while(!encontrado){
            
            //cout << "\t\t Comparando v[]" << v[i] << " con v_copia[] " << v_copia[k] << endl;
            if(v[i] == v_copia[k]){
                //cout << "\tSon iguales No copia v = " << v[i] << " k " << k << endl;
                v[i] = v[i+1];
                encontrado = true;
            }else{
                //cout << " Iteracion k valor:" << k << endl;
                k++;
            }

            if( k >= tam_copia && !encontrado){
                //cout << "Finalizada la busqueda en el vector copia ... copiando " << v[i] << endl;
                v_copia[k] = v[i]; 
                //cout << "Copiado numero " << v[i] << endl;
                tam_copia++;
                encontrado = true;
                
            }
        }
        if(i == tam-1){
            //cout << "Terminado i:" << i  << endl;
            terminado = true; 
        }
        else{
            encontrado = false;
            k=0;
            //cout << "Incremente i "<< endl;
            i++;
        }
    }
    
    //Copiamos v_copia
    for(int i = 0; i < tam_copia; i++)
        v[i] = v_copia[i];
    
    tam = tam_copia;
    
}

void hanoi(int M, int i, int j){
    if(M>0){
        hanoi(M-1, i, 6-i-j);
        cout << i << " -> " << j << endl;
        hanoi(M-1, 6-i-j,j);
    }
}

void HeapSort(int *v, int n){
    double *apo=new double[n]; 
    int tamapo = 0; 

    for (int i = 0; i < n; i++){
        apo[tamapo] = v[i]; 
        tamapo++; 
        insertarEnPos(apo, tamapo); 
    }

    for (int i =0; i < n; i++){
        v[i] = apo[0];
        tamapo--; 
        apo[0] = apo[tamapo]; 
        reestructurarRaiz(apo,0,tamapo); 
    }
    delete[] apo;
}

void insertarEnPos(double *apo, int pos){
    int idx = pos-1; 
    int padre; 

    if(idx > 0){
        padre =(idx-2)/2;
    }else{
        padre=(idx-1)/2;
    }

    if(apo[padre] > apo[idx]){
        double tmp=apo[idx]; 
        apo[idx] = apo[padre];
        apo[padre] = tmp;
        insertarEnPos(apo, padre+1);
    }
}

void reestructurarRaiz(double *apo, int pos, int tamapo){
    int minhijo; 
    if(2*pos+1 < tamapo){
        minhijo = 2*pos+1;
        if((minhijo+1 < tamapo) && (apo[minhijo] > apo[minhijo+1]))
            minhijo++;
        if(apo[pos] > apo[minhijo]){
            double tmp = apo[pos];
            apo[pos] = apo[minhijo]; 
            apo[minhijo] = tmp;
            reestructurarRaiz(apo, minhijo,tamapo);
        }
    }
}

void MergeSort(int *v, int posIni, int posFin, int *vaux) {

    if (posIni>=posFin) return;

    int centro= (posIni+posFin)/2;

    MergeSort(v, posIni, centro, vaux);
    MergeSort(v, centro+1, posFin, vaux);
    fusionaMS(v, posIni, centro+1, posFin, vaux);
}

void fusionaMS(int *v, int posIni, int centro, int posFin, int *vaux) {

    int i= posIni;
    int j= centro;
    int k= 0;

    while (i<centro && j<=posFin) {
        if (v[i]<=v[j]) {
            vaux[k]= v[i];
            i++;
        } else {
            vaux[k]= v[j];
            j++;
        }
        k++;
    }

    while (i<centro) {
        vaux[k]= v[i];
        i++, k++;
    }
    while (j<=posFin) {
        vaux[k]= v[j];
        j++, k++;
    }

    memcpy(v+posIni, vaux, k*sizeof(int));
}


