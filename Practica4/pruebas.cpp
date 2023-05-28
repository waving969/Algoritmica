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

        cout << "Detalles compra: " << numAcciones << endl;
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
        cout << "\nEmpresa: " << empresa.getNombre() << endl;
        int numAcciones = empresa.numeroMaximoAccionesPuedoComprar(dineroInicial);
        cout << "DInero antes de la compra: " << dineroInicial << endl;
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
        cout << "\nEmpresa: " << empresa.getNombre() << endl;
        if(empresa.getaccionXbeneficioXcomision() > 0){
            int numAcciones = empresa.numeroMaximoAccionesPuedoComprar(dineroInicial);
            cout << "DInero antes de la compra: " << dineroInicial << endl;
            empresa.compraAcciones(dineroInicial, numAcciones);
            cout << "Dinero despues de la compra " << dineroInicial << endl;
            cout << "Numero de acciones de la empresa: " << empresa.getAcciones() << endl;
            devolver.push_back(make_tuple(empresa, numAcciones));
        }
        else{
            cout << "\nDe esta empresa no se compra: " <<  empresa.getaccionXbeneficioXcomision() << endl;
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
    1.- Calcular el posible maximo beneficio por Accion de cada empresa 
    2.- Ordenar las empresas por el beneficio maximo 
    3.- Comprar el maximo de acciones de cada empresa siguiendo el orden anterior 
    4.- Si no se puede comprar una accion, comprobar las empresas restantes hasta quedarse sin dinero 
*/



double CambiodeMonedas(std::vector<Empresa>& empresas, int capital) {
    int numEmpresas = empresas.size();
    std::vector<double> dp(capital+1, INT_MIN);

    dp[0] = 0;

    for (int i = 0; i < capital; i++) {
        for (int j = 0; j < numEmpresas; j++) {
            if (i >= empresas[j].getPrecio()) {
                double beneficioInvertir = empresas[j].calcularBeneficioTotal(1) + dp[i - empresas[j].getPrecio()];
                dp[i] = std::max(dp[i], beneficioInvertir);
            }
        }
    }

    return dp[capital];
}


double Mochila(std::vector<Empresa>& empresas, int capital) {
    int numEmpresas = empresas.size();

    // Creamos una matriz para almacenar los beneficios máximos acumulados
    std::vector<std::vector<double>> beneficios(numEmpresas + 1, std::vector<double>(capital + 1, 0.0));

    for (int i = 1; i <= numEmpresas; i++) {
        for (double j = 1; j <= capital; j++) {
            if (empresas[i - 1].getPrecio() <= j) {
                double beneficioInvertir = empresas[i - 1].calcularBeneficioTotal(1) + beneficios[i - 1][j - empresas[i - 1].getPrecio()];
                beneficios[i][j] = std::max(beneficios[i - 1][j], beneficioInvertir);
            }
            else {
                beneficios[i][j] = beneficios[i - 1][j];
            }
        }
    }

    return beneficios[numEmpresas][capital];
}


double ideaOriginal(std::vector<Empresa>& empresas, int capital) {
    int numEmpresas = empresas.size();

    // Creamos una matriz para almacenar los beneficios acumulados
    std::vector<std::vector<double>> beneficios(numEmpresas + 1, std::vector<double>(capital + 1, 0.0));

    for (double i = 1; i <= numEmpresas; i++) {
        for (double j = 1; j <= capital; j++) {
            double maxBeneficio = beneficios[i - 1][j];  // Beneficio máximo sin invertir en la empresa actual
            
            // Comprobamos si es posible invertir en la empresa actual con el capital disponible
            if (j >= empresas[i - 1].getPrecio()) {
                double beneficioInvertir = empresas[i - 1].calcularBeneficioTotal(j / empresas[i - 1].getPrecio()) + beneficios[i - 1][static_cast<int>(j) % static_cast<int>(empresas[i - 1].getPrecio())];
                maxBeneficio = std::max(maxBeneficio, beneficioInvertir);
            }
            
            beneficios[i][j] = maxBeneficio;
        }
    }

    return beneficios[numEmpresas][capital];
}

bool findOnTuple(vector<tuple<Empresa, int>>lista, int i, int j, vector<Empresa> empresas){
    bool devolver = false; 
    int tamLista = lista.size();

    for(const auto it: lista){
        Empresa elemento1 = get<0>(it);
        int elemento2 = get<1>(it);
        cout << "Comparando "<< elemento1.getNombre() << " con " << empresas[i].getNombre()<< endl;
        cout << "Numero de acciones " << elemento2 << " con " << j << endl;

        if(empresas[i].getNombre() == elemento1.getNombre() and elemento2 == j){
            cout << "\tEncontrado similar " << endl;
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

    cout << "Matriz beneficios " << endl; 
    for(int i = 0; i < numEmpresas; i++){
        cout << empresas[i].getNombre() << " ";
        for(int j = 1; j <= NUM_ACCIONES; j++){
            cout << beneficios[i][j] << " ";
        }
        cout << endl;
    }

    
    bool puedeComprar = true; 
    int capital_aux = capital;
    int aux_i;
    int aux_j;
    vector<tuple<Empresa, int>> listaCompra;
    int contador = 0;

    while(capital_aux > 0 and puedeComprar){
        cout << "\nIteracion " << ++contador << endl;
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
                if(capital_aux < 0){
                    cout << "Se acabo el dinero"<< endl;
                    puedeComprar = false;
                    break;
                }
                //cout << "Compramos acciones de: " << empresas[aux_i].getNombre() << " Cantidad: " << aux_j << endl;
                
                    listaCompra.push_back(make_tuple(empresas[aux_i], aux_j));
                
            
            }
            
        }
    }

    //Hacer lista para recorrer el vector de empresas y modificarlo 
    cout << "\nLista de la compra: " << endl;
    for(const auto &it: listaCompra){
        Empresa elemento1 = get<0>(it);
        int elemento2 = get<1>(it);
        cout << "\nNombre empresa: " << elemento1.getNombre() << endl;
        cout << "DInero antes de la compra: " << capital << endl;
        elemento1.compraAcciones(capital, 1);
        cout << "Dinero despues de la compra " << capital << endl;
        cout << "Numero de acciones de la empresa: " << elemento1.getAcciones() << endl;
    }
            
    
    
    

    return listaCompra;
}










int main(){
    double dinero = 100;
    Empresa empresa1("Fruterias Loli", NUM_ACCIONES, 1, 105.0, 10.0);
    Empresa empresa2("Bar Paco", NUM_ACCIONES, 20, 110.0, 10.0); 
    Empresa empresa3("Chuches Paqui", NUM_ACCIONES,10,120.0,5.0);
    Empresa empresa4("Car-Wash Asuncion", NUM_ACCIONES,5,102.0,10.0);
    Empresa empresa5("Ferreteria Manolo",NUM_ACCIONES,5,200.0,1.0);
    vector<Empresa> vectorEmpresas;
    vectorEmpresas.push_back(empresa1);
    vectorEmpresas.push_back(empresa2);
    vectorEmpresas.push_back(empresa3);
    vectorEmpresas.push_back(empresa4);
    vectorEmpresas.push_back(empresa5);
    

    /*for (Empresa empresa : vectorEmpresas) {
        cout << "Nombre: " << empresa.getNombre() << endl;
        cout << "Acciones: " << empresa.getAcciones() << endl;
        cout << "Precio por accion: " << empresa.getPrecio() << endl;
        cout << "Beneficio por accion: " << empresa.getBeneficios() << endl;
        cout << "Comision por operacion: " << empresa.getComision() << endl;
        cout << "Estimacion de la mejor empresa: " << empresa.getaccionXbeneficioXcomision() << endl;  
        cout << endl;
    }*/
    
   cout << "Algoritmo basico" << endl; 

    vector<tuple<Empresa, int>> solucion;
    solucion = algoritmoBasico(vectorEmpresas, dinero);
    double posibleBeneficio = 0;
    vector<tuple<Empresa, int>> solucionPD;
  /*  cout << "\n\tNumero de acciones compradas: " << endl; 
    for (const auto& it: solucion){
        Empresa elemento1 = get<0>(it);
        int elemento2 = get<1>(it); 

        if(elemento2 != 0){
            cout << "\nEmpresa: "<< elemento1.getNombre() << " \nAcciones Compradas: " << elemento2 << endl;
            posibleBeneficio += elemento2 * elemento1.getBeneficios() * elemento1.getPrecio();
            cout << "\nEmpresa, beneficio por accion: "<<elemento1.getBeneficios() << " * " << elemento2 << endl;
        }
    }

    cout << "Dinero Final: "<< dinero << endl;
    cout << "Posible Beneficio " << posibleBeneficio << endl; 
    cout << "Dinero total " << dinero + posibleBeneficio << endl;
*/





    cout << "\n\n\tALGORITMOS DE PROGRAMACION DINAMICA RESULTADOS  " << endl;
    double capital = 100;
    solucionPD = ideaOriginal2(vectorEmpresas, capital);
    for (const auto& it: solucionPD){
        Empresa elemento1 = get<0>(it);
        int elemento2 = get<1>(it); 

        if(elemento2 != 0){
            cout << "\nEmpresa: "<< elemento1.getNombre() << " \nAcciones Compradas: " << elemento2 << endl;
            posibleBeneficio += elemento2 * elemento1.getBeneficios() * elemento1.getPrecio();
            cout << "\nEmpresa, beneficio por accion: "<<elemento1.getBeneficios() << " * " << elemento2 << endl;
        }
    }

    cout << "Posible Beneficio " << posibleBeneficio << endl; 
    cout << "Dinero total " << capital + posibleBeneficio << endl;


    return 0;
}
/*
int max_beneficio(const vector<Empresa>& empresas, int X) {
    const int N = empresas.size();
    vector<vector<int>> DP(N,) (N + 1, vector<int>(X + 1, 0));
    
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= X; ++j) {
            DP[i][j] = DP[i - 1][j];  // No comprar acciones de la empresa i
            for (int k = 1; k <= empresas[i - 1].a; ++k) {
                if (j >= k * empresas[i - 1].p + empresas[i - 1].c) {
                    DP[i][j] = max(DP[i][j], DP[i - 1][j - k * empresas[i - 1].p - empresas[i - 1].c] + k * empresas[i - 1].b);
                }
            }
        }
    }
    
    return DP[N][X];
}*/
