#include <iostream>
#include <string>
#include <vector>

using namespace std; 

class Empresa{
private: 
    string nombre;
    int acciones; 
    int precioPorAccion; 
    int beneficioPorAccion; 
    int comisionPorOperacion;
public: 
    Empresa(){
        this->nombre = " ";
        this->acciones = 0;
        this->precioPorAccion = 0; 
        this->beneficioPorAccion = 0; 
        this->comisionPorOperacion = 0;
    }

    Empresa(string nombre,int acciones, int precio, int beneficio, int comision){
        this->nombre = nombre;
        this->acciones = acciones; 
        this->precioPorAccion = precio; 
        this->beneficioPorAccion = beneficio; 
        this->comisionPorOperacion = comision;
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
};



int main(){
    Empresa empresa1("Fruterias Loli", 10, 1, 5, 10);
    Empresa empresa2("Bar Paco", 100, 20, 10, 10); 
    Empresa empresa3("Chuches Paqui", 150,10,20,5);
    Empresa empresa4("Car-Wash Asuncion", 20,5,2,10);
    Empresa empresa5("Ferreteria Manolo",10,5,20,10);
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
    

    
}

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
}
