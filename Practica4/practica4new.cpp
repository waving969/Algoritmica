#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std; 

class Empresa{
private: 
    string nombre;
    int acciones; 
    int precioPorAccion; 
    int beneficioPorAccion; 
    double comisionPorOperacion;

    
public: 
    int accionXbeneficioXcomision;
    Empresa(){
        this->nombre = " ";
        this->acciones = 0;
        this->precioPorAccion = 0; 
        this->beneficioPorAccion = 0; 
        this->comisionPorOperacion = 0;
    }

    Empresa(string nombre,int acciones, int precio, int beneficio, double comision){
        this->nombre = nombre;
        this->acciones = acciones; 
        this->precioPorAccion = precio; 
        this->beneficioPorAccion = beneficio; 
        this->comisionPorOperacion = comision / 100;

        this->accionXbeneficioXcomision = (precio * beneficio) - (precio*comision);
    }

    string getNombre(){
        return nombre;
    }
    int getAcciones(){
        return this->acciones;
    }

    int getPrecio(){
        return this->precioPorAccion;
    }

    int getBeneficios(){
        return this->beneficioPorAccion;
    }
    
    //La comision corresponde con el % del precio de las acciones ???
    int getComision(){
        return this->comisionPorOperacion;
    }

    int estimacionPosibleBeneficio(){
        return (this->precioPorAccion*this->beneficioPorAccion);
    }

    int precioComision(int numAcciones){
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

void algoritmoBasico(vector<Empresa> empresas, double dineroInicial){
    //vector<tuple<Empresa, int>> devolver;
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
    }


   

}



int main(){
    double dinero = 100;
    Empresa empresa1("Fruterias Loli", 10, 1, 5, 10);
    Empresa empresa2("Bar Paco", 100, 20, 10, 10); 
    Empresa empresa3("Chuches Paqui", 150,10,20,5);
    Empresa empresa4("Car-Wash Asuncion", 20,5,2,10);
    Empresa empresa5("Ferreteria Manolo",10,5,200,1);
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
        cout << endl;
    }
    
    cout << "Algoritmo basico" << endl; 

    algoritmoBasico(vectorEmpresas, dinero);
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
