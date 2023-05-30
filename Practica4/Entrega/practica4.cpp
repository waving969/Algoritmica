#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <tuple>

using namespace std; 

const int NUM_ACCIONES = 10;

class Empresa{
private: 
    string nombre;
    int acciones; 
    double precioPorAccion; 
    double beneficioPorAccion; 
    double comisionPorOperacion;

    
public: 
    double accionXbeneficioXcomision;
    Empresa(){
        this->nombre = " ";
        this->acciones = 0;
        this->precioPorAccion = 0; 
        this->beneficioPorAccion = 0; 
        this->comisionPorOperacion = 0;
    }

    Empresa(string nombre,int acciones, double precio, double beneficio, double comision){
        this->nombre = nombre;
        this->acciones = acciones; 
        this->precioPorAccion = precio; 
        this->beneficioPorAccion = beneficio/100; 
        this->comisionPorOperacion = comision / 100;

        this->accionXbeneficioXcomision = ((precio * beneficioPorAccion) - (precio*comisionPorOperacion)) -precio;
    }

    string getNombre(){
        return nombre;
    }
    int getAcciones(){
        return this->acciones;
    }

    double getPrecio(){
        return this->precioPorAccion;
    }

    double getBeneficios(){
        return this->beneficioPorAccion;
    }
    
    //La comision corresponde con el % del precio de las acciones ???
    double getComision(){
        return this->comisionPorOperacion;
    }

    double getaccionXbeneficioXcomision(){
        return this->accionXbeneficioXcomision;
    }

    double estimacionPosibleBeneficio(){
        return (this->precioPorAccion*this->beneficioPorAccion);
    }

    double precioComision(int numAcciones){
        if(numAcciones < this->acciones){
            return getComision() * numAcciones;
        }
        else{
            cout << "No se pueden comprar tantas acciones " << endl;
            return -1;
        }
    }

    int numeroMaximoAccionesPuedoComprar(int dinero){
        int numAcciones = 0;
        double precioTotal = 0;
        while(numAcciones <= this->acciones and dinero > precioTotal){
            precioTotal = this->precioPorAccion * numAcciones + (this->comisionPorOperacion * numAcciones);
            //cout << "\nprecioTotal: " << precioTotal << "\nNumAcciones "  << numAcciones << endl;
            numAcciones++;

        }
        
        if(numAcciones != 0){
            numAcciones--;
        }
        if(dinero<precioTotal){
            numAcciones--;
        }

        //cout << "Detalles compra: " << numAcciones << endl;
        return numAcciones;
    }

    void compraAcciones(double &dinero, int numAcciones){
        //cout << numAcciones << endl;
        double precioTotal = 0;
        precioTotal = this->precioPorAccion * numAcciones + (this->comisionPorOperacion * numAcciones);
        dinero = dinero - precioTotal;
        this->acciones = this->acciones-numAcciones;
    }

    double calcularBeneficioTotal(int numAccionesInvertir) {
        double calculo = numAccionesInvertir * this->accionXbeneficioXcomision;
        return calculo;
    }

};

bool operator<(const Empresa& a, const Empresa& n) {
    return a.accionXbeneficioXcomision > n.accionXbeneficioXcomision;
}

//Algoritmo Basico 1
/*
    Comparamos cual es el numero Beneficio maximo de cada empresa y las ordenamos 
    Hasta comprar el numero maximo de acciones que podemos comprar con el dinero inicial y maximizando el beneficio

    Pasos: 
    1.- Calcular el posible maximo beneficio por Accion de cada empresa 
    2.- Ordenar las empresas por el beneficio maximo 
    3.- Comprar el maximo de acciones de cada empresa siguiendo el orden anterior 
    4.- Si no se puede comprar una accion, comprobar las empresas restantes hasta quedarse sin dinero 
*/


//ARREGLAR DOUBLES NO FUNCIONAN

vector<tuple<Empresa, int>> algoritmoBasico(vector<Empresa> empresas, double &dineroInicial){
    vector<tuple<Empresa, int>> devolver;
    set<Empresa> listaEmpresasOrdenada;

    for(Empresa empresa: empresas){
        listaEmpresasOrdenada.insert(empresa);
    }

    auto iterador = listaEmpresasOrdenada.begin();
    Empresa empresa1 = *iterador;

    cout << "\n\tEmpresas ordenadas por el posible beneficio" << endl ;
    for(auto it = listaEmpresasOrdenada.begin(); it != listaEmpresasOrdenada.end(); it++){
        Empresa empresa = *it;
        
        cout << "\nNombre: " << empresa.getNombre() << "\nEstimacionBeneficio: " << empresa.getaccionXbeneficioXcomision() << endl;
    }

    
    //empresa1.compraAcciones(dineroInicial, 2);
      

    for(auto it = listaEmpresasOrdenada.begin(); it != listaEmpresasOrdenada.end(); it++){
        Empresa empresa = *it; 
        cout << "\nNombre empresa: " << empresa.getNombre() << endl;
        int numAcciones = empresa.numeroMaximoAccionesPuedoComprar(dineroInicial);
        cout << "Dinero antes de la compra: " << dineroInicial << endl;
        empresa.compraAcciones(dineroInicial, numAcciones);
        cout << "Dinero despues de la compra " << dineroInicial << endl;
        cout << "Numero de acciones de la empresa: " << empresa.getAcciones() << endl;
        devolver.push_back(make_tuple(empresa, numAcciones));
    }


   
    return devolver;
}


//Algoritmo Basico 2
/*
    Comparamos cual es el numero Beneficio maximo de cada accion de cada empresa y las ordenamos 
    Hasta comprar el numero maximo de acciones que nos darian el maximo beneficio posible por cada accion con el dinero inicial

    Pasos: 
    1.- Calcular el posible maximo beneficio por Accion de cada empresa 
    2.- Ordenar las empresas por el beneficio maximo 
    3.- Comprar el maximo de acciones de cada empresa siguiendo el orden anterior siempre y cuando el beneficio por accion de la empresa sea positivo 
    4.- Si no se puede comprar una accion, comprobar las empresas restantes hasta quedarse sin dinero 
*/


vector<tuple<Empresa, int>> algoritmoBasico2(vector<Empresa> empresas, double &dineroInicial){
    vector<tuple<Empresa, int>> devolver;
    set<Empresa> listaEmpresasOrdenada;

    for(Empresa empresa: empresas){
        listaEmpresasOrdenada.insert(empresa);
    }

    auto iterador = listaEmpresasOrdenada.begin();
    Empresa empresa1 = *iterador;

    cout << "\n\tEmpresas ordenadas por el posible beneficio" << endl ;
    for(auto it = listaEmpresasOrdenada.begin(); it != listaEmpresasOrdenada.end(); it++){
        Empresa empresa = *it;
        
        cout << "\nNombre: " << empresa.getNombre() << "\nEstimacionBeneficio: " << empresa.getaccionXbeneficioXcomision() << endl;
    }

    
    //empresa1.compraAcciones(dineroInicial, 2);
      

    for(auto it = listaEmpresasOrdenada.begin(); it != listaEmpresasOrdenada.end(); it++){
        Empresa empresa = *it; 
        
        if(empresa.getaccionXbeneficioXcomision() > 0){
            cout << "\nNombre empresa: " << empresa.getNombre() << endl;
            int numAcciones = empresa.numeroMaximoAccionesPuedoComprar(dineroInicial);
            cout << "Dinero antes de la compra: " << dineroInicial << endl;
            empresa.compraAcciones(dineroInicial, numAcciones);
            cout << "Dinero despues de la compra " << dineroInicial << endl;
            cout << "Numero de acciones de la empresa restantes: " << empresa.getAcciones() << endl;
            devolver.push_back(make_tuple(empresa, numAcciones));
        }
        else{
            //cout << "\nDe esta empresa no se compra: " <<  empresa.getaccionXbeneficioXcomision() << endl;
        }
    }
    return devolver;
}


//Algoritmo Programacion Dinamica
/*
    Puesto que si compramos el numero maximo de acciones de cada empresa para obtener nuestro mayor beneficio nos jugamos a que esa empresa 
    quiebre y perdamos nuestro dinero, lo que hemos implementado en este algoritmo es una adaptacion del algortimo de mochila junto con el algoritmo
    de cambio de monedas, para que no tengamos nuestra mayoria de acciones en una sola empresa y la tengamos "repartida" y sacando tambien el maximo beneficio

    Pasos: 
    1.- Crear la matriz de los posibles beneficios
    2.- Plantear el caso base, que es cuando no se compran acciones, por tanto el beneficio es 0
    3.- Plantear el problema como una ecuacion de maximizacion recursiva que devuelve el camino que debemos tomar, 
        en este caso, el numero de acciones que compramos de cada empresa, donde en cada iteracion, tomará el mejor valor
        para la compra de una unica accion
    4.- Verificar que se cumple el P.O.B y crear el camino, eliminando las acciones redundantes y quedandose con el valor 
        de las acciones mas altas para comprar,
*/

bool findOnTuple(vector<tuple<Empresa, int>>lista, int i, int j, vector<Empresa> empresas){
    bool devolver = false; 
    int tamLista = lista.size();

    for(const auto it: lista){
        Empresa elemento1 = get<0>(it);
        int elemento2 = get<1>(it);
        //cout << "Comparando "<< elemento1.getNombre() << " con " << empresas[i].getNombre()<< endl;
        //cout << "Numero de acciones " << elemento2 << " con " << j << endl;

        if(empresas[i].getNombre() == elemento1.getNombre() and elemento2 == j){
            //cout << "\tEncontrado similar " << endl;
            return true;
        }
            
    }

    return devolver;
}



vector<tuple<Empresa, int>> ideaOriginal2(std::vector<Empresa>& empresas, double& capital) {
    int numEmpresas = empresas.size();
    double beneficios[empresas.size()][NUM_ACCIONES];
    vector<tuple<Empresa, int>> devolver;
    vector<Empresa> empre;
    int max = 0;


    //Caso base 
    for (int i = 0; i < numEmpresas; i++){
        beneficios[i][0] = 0;
    }
    
    for(int i = 0; i < numEmpresas; i++){
        for(int j = 1; j <= NUM_ACCIONES; j++){
            beneficios[i][j] = empresas[i].getaccionXbeneficioXcomision() * j; 
        }
    }

    //Paso 1 Crear la matriz de beneficios
    cout << "Matriz beneficios " << endl; 
    for(int i = 0; i < numEmpresas; i++){
        cout << empresas[i].getNombre() << " \t";
        for(int j = 1; j <= NUM_ACCIONES; j++){
            cout << beneficios[i][j] << " ";
        }
        cout << endl;
    }

    
    bool puedeComprar = true; 
    double capital_aux = capital;
    int aux_i;
    int aux_j;
    vector<tuple<Empresa, int>> listaCompra;
    int contador = 0;
    

    //Paso 2
    while(capital_aux > 0 and puedeComprar){
        //cout << "\nIteracion " << ++contador << endl;
        max = 0;
        for(int j = 1; j <= NUM_ACCIONES; j++){
            for(int i = 0; i < numEmpresas; i++){
                if(beneficios[i][j] > max and !findOnTuple(listaCompra, i, j, empresas)){
                    //cout << "Mejor empresa " << empresas[i].getNombre() << endl;
                    max = beneficios[i][j];
                    aux_i = i;
                    aux_j = j;
                }
            }
            if(max != 0){
                capital_aux -= empresas[aux_i].getPrecio()+empresas[aux_i].getComision();
                //cout << "Capitalaux: " << capital_aux << endl;
                if(capital_aux < 0){
                    //cout << "Se acabo el dinero"<< endl;
                    puedeComprar = false;
                    
                }
                //cout << "Compramos acciones de: " << empresas[aux_i].getNombre() << " Cantidad: " << aux_j << endl;
                else
                listaCompra.push_back(make_tuple(empresas[aux_i], aux_j));
                
            
            }
            
        }
    }

    Empresa finCompra;
    listaCompra.push_back(make_tuple(finCompra, -1));

    //Paso 3
    //cout << "\nLista de la compra: " << endl;
    string nombreAux = " ";
    Empresa empresaAux; 
    int numAccionesAux = 0;
    int primeraIteracion = 0;
    
    for(const auto &it: listaCompra){
        //cout << "Devolver.size() = " << devolver.size() << endl;
        Empresa elemento1 = get<0>(it);
        int elemento2 = get<1>(it);
        //cout << "\nNombre empresa: " << elemento1.getNombre() << " == " << empresaAux.getNombre() << endl;
        
        if(empresaAux.getNombre() == elemento1.getNombre()){
            //cout << "if " << elemento2 << " > " << numAccionesAux << endl; 
            if(numAccionesAux<elemento2){
                numAccionesAux = elemento2;
            }
        }else{
            if(primeraIteracion != 0)
                devolver.push_back(make_tuple(empresaAux, numAccionesAux));

            empresaAux = elemento1;
            numAccionesAux = elemento2;
            primeraIteracion++;
        }
    }

    cout << "\nVector devolver " << endl;
    for(const auto &it: devolver){
        Empresa elemento1 = get<0>(it);
        int elemento2 = get<1>(it);
        cout << "\nNombre empresa: " << elemento1.getNombre() << " Acciones compradas: " << elemento2 <<  endl;
        cout << "Dinero antes de la compra: " << capital << endl;
        elemento1.compraAcciones(capital, elemento2);
        cout << "Dinero despues de la compra " << capital << endl;
        cout << "Numero de acciones de la empresa restantes: " << elemento1.getAcciones() << endl;
            
    }
    
    

    return devolver;
}










int main(){
    double dinero = 100;
    Empresa empresa1("Fruterias Loli", NUM_ACCIONES, 1, 105.0, 10.0);
    Empresa empresa2("Bar Paco", NUM_ACCIONES, 20, 110.0, 10.0); 
    Empresa empresa3("Chuches Paqui", NUM_ACCIONES,10,120.0,5.0);
    Empresa empresa4("Car-Wash Asuncion", NUM_ACCIONES,5,102.0,10.0);
    Empresa empresa5("Ferreteria Manolo",NUM_ACCIONES,5,200.0,1.0);
    Empresa empresa6("Academia Los Patos", NUM_ACCIONES, 1, 300, 10);
    vector<Empresa> vectorEmpresas;
    vectorEmpresas.push_back(empresa1);
    vectorEmpresas.push_back(empresa2);
    vectorEmpresas.push_back(empresa3);
    vectorEmpresas.push_back(empresa4);
    vectorEmpresas.push_back(empresa5);
    vectorEmpresas.push_back(empresa6);
    
    
   /* 
    Empresa empresa1("Tejidos Manoli", NUM_ACCIONES, 15,110.0, 5.0);
    Empresa empresa2("Joyeria Isidoro", NUM_ACCIONES, 10, 110.0, 2.0); 
    Empresa empresa3("Polleria", NUM_ACCIONES,10,120.0,5.0);
    Empresa empresa4("Car-Wash2", NUM_ACCIONES,10,120.0,10.0);
    Empresa empresa5("Ferreteria2",NUM_ACCIONES,4,150.0,1.0);
    Empresa empresa6("Academia2", NUM_ACCIONES, 1, 120, 5);
    vector<Empresa> vectorEmpresas;
    vectorEmpresas.push_back(empresa1);
    vectorEmpresas.push_back(empresa2);
    vectorEmpresas.push_back(empresa3);
    vectorEmpresas.push_back(empresa4);
    vectorEmpresas.push_back(empresa5);
    vectorEmpresas.push_back(empresa6);    */

    /*for (Empresa empresa : vectorEmpresas) {
        cout << "Nombre: " << empresa.getNombre() << endl;
        cout << "Acciones: " << empresa.getAcciones() << endl;
        cout << "Precio por accion: " << empresa.getPrecio() << endl;
        cout << "Beneficio por accion: " << empresa.getBeneficios() << endl;
        cout << "Comision por operacion: " << empresa.getComision() << endl;
        cout << "Estimacion de la mejor empresa: " << empresa.getaccionXbeneficioXcomision() << endl;  
        cout << endl;
    }*/
    
   cout << "\n\n\tALGORITMO BASICO RESULTADOS" << endl; 

    vector<tuple<Empresa, int>> solucion;
    solucion = algoritmoBasico(vectorEmpresas, dinero);
    double posibleBeneficio = 0;
    vector<tuple<Empresa, int>> solucionPD;
    cout << "\n\tNumero de acciones compradas: " << endl; 
    for (const auto& it: solucion){
        Empresa elemento1 = get<0>(it);
        int elemento2 = get<1>(it); 

        if(elemento2 != 0){
            cout << "\nEmpresa: "<< elemento1.getNombre() << " \nAcciones Compradas: " << elemento2 << endl;
            posibleBeneficio += elemento2 * elemento1.getBeneficios() * elemento1.getPrecio();
            cout << "Empresa, beneficio por accion: "<<elemento1.getBeneficios() << " * " << elemento2 << endl;
        }
    }

    cout << "\n\nDinero Final: "<< dinero << endl;
    cout << "Posible Beneficio " << posibleBeneficio << endl; 
    cout << "Dinero total " << dinero + posibleBeneficio << endl;




    posibleBeneficio = 0;

    cout << "\n\n\tALGORITMOS DE PROGRAMACION DINAMICA RESULTADOS  " << endl;
    double capital = 100;
    solucionPD = ideaOriginal2(vectorEmpresas, capital);
    for (const auto& it: solucionPD){
        Empresa elemento1 = get<0>(it);
        int elemento2 = get<1>(it); 

        if(elemento2 != 0){
            cout << "\nEmpresa: "<< elemento1.getNombre() << " \nAcciones Compradas: " << elemento2 << endl;
            posibleBeneficio += elemento2* elemento1.getBeneficios() * elemento1.getPrecio();
            cout << "Empresa, beneficio por accion: "<<elemento1.getBeneficios() << " * " << elemento2 << endl;
        }
    }
    cout << "\n\nDinero final: " << capital << endl;
    cout << "Posible Beneficio " << posibleBeneficio << endl; 
    cout << "Dinero total " << capital + posibleBeneficio << endl;


    return 0;
}
