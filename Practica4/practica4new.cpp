#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <tuple>

using namespace std; 

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

        this->accionXbeneficioXcomision = (precio * beneficioPorAccion) - (precio*comisionPorOperacion);
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
        cout << "Detalla compra: " << numAcciones << endl;
        if(numAcciones != 0){
            numAcciones--;
        }
        if(dinero<precioTotal){
            numAcciones--;
        }

        return numAcciones;
    }

    void compraAcciones(double &dinero, int numAcciones){
        cout << numAcciones << endl;
        double precioTotal = 0;
        precioTotal = this->precioPorAccion * numAcciones + (this->comisionPorOperacion * numAcciones);
        dinero = dinero - precioTotal;
        this->acciones = this->acciones-numAcciones;
    }

};

bool operator<(const Empresa& a, const Empresa& n) {
    return a.accionXbeneficioXcomision > n.accionXbeneficioXcomision;
}

//Algoritmo Basico 
/*
    Comparamos cual es el numero Beneficio maximo de cada empresa y las ordenamos 
    Hasta comprar el numero maximo de acciones que podemos comprar con el dinero inicial

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



int main(){
    double dinero = 100;
    Empresa empresa1("Fruterias Loli", 10, 1, 105.0, 10.0);
    Empresa empresa2("Bar Paco", 100, 20, 110.0, 10.0); 
    Empresa empresa3("Chuches Paqui", 150,10,120.0,5.0);
    Empresa empresa4("Car-Wash Asuncion", 20,5,102.0,10.0);
    Empresa empresa5("Ferreteria Manolo",10,5,200.0,1.0);
    vector<Empresa> vectorEmpresas;
    vectorEmpresas.push_back(empresa1);
    vectorEmpresas.push_back(empresa2);
    vectorEmpresas.push_back(empresa3);
    vectorEmpresas.push_back(empresa4);
    vectorEmpresas.push_back(empresa5);
    int X = 300; //Dinero disponible

    for (Empresa empresa : vectorEmpresas) {
        cout << "Nombre: " << empresa.getNombre() << endl;
        cout << "Acciones: " << empresa.getAcciones() << endl;
        cout << "Precio por accion: " << empresa.getPrecio() << endl;
        cout << "Beneficio por accion: " << empresa.getBeneficios() << endl;
        cout << "Comision por operacion: " << empresa.getComision() << endl;
        cout << "Estimacion de la mejor empresa: " << empresa.getaccionXbeneficioXcomision() << endl;  
        cout << endl;
    }
    
    cout << "Algoritmo basico" << endl; 

    vector<tuple<Empresa, int>> solucion;
    solucion = algoritmoBasico(vectorEmpresas, dinero);
    double posibleBeneficio = 0;

    cout << "\n\tNumero de acciones compradas: " << endl; 
    for (const auto& it: solucion){
        Empresa elemento1 = get<0>(it);
        int elemento2 = get<1>(it); 

        if(elemento2 != 0){
            cout << "\nEmpresa: "<< elemento1.getNombre() << " \nAcciones Compradas: " << elemento2 << endl;
            posibleBeneficio += elemento2 * elemento1.getBeneficios();
            cout << "\nEmpresa, beneficio por accion: "<<elemento1.getBeneficios() << " * " << elemento2 << endl;
        }
    }

    cout << "Dinero Final: "<< dinero << endl;
    cout << "Posible Beneficio " << posibleBeneficio << endl;
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
