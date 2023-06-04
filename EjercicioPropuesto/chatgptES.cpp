#include <iostream>
#include <vector>
#include <algorithm>

// Estructura para representar un contenedor
struct Contenedor {
    int id;
    int peso;
};

// Función de comparación para ordenar los contenedores por peso en orden descendente
bool compararPorPesoDesc(const Contenedor& c1, const Contenedor& c2) {
    return c1.peso > c2.peso;
}

// Función para cargar los contenedores en el buque
std::vector<Contenedor> cargarContenedores(int capacidadBuque, const std::vector<Contenedor>& contenedores) {
    std::vector<Contenedor> seleccionados;
    int capacidadActual = capacidadBuque;

    // Ordenar los contenedores en orden descendente por peso
    std::vector<Contenedor> contenedoresOrdenados = contenedores;
    std::sort(contenedoresOrdenados.begin(), contenedoresOrdenados.end(), compararPorPesoDesc);

    // Iterar por cada contenedor y seleccionar los que se pueden cargar
    for (const Contenedor& contenedor : contenedoresOrdenados) {
        if (contenedor.peso <= capacidadActual) {
            seleccionados.push_back(contenedor);
            capacidadActual -= contenedor.peso;
        }
    }

    return seleccionados;
}

// Función para imprimir la lista de contenedores seleccionados
void imprimirContenedores(const std::vector<Contenedor>& contenedores) {
    std::cout << "Contenedores seleccionados:\n";
    for (const Contenedor& contenedor : contenedores) {
        std::cout << "Id: " << contenedor.id << " Peso: " << contenedor.peso << "\n"; 
    }
    std::cout << std::endl;
}

int main() {
    // Capacidad del buque
    int capacidadBuque = 25;

    // Contenedores disponibles
    std::vector<Contenedor> contenedores = {
        {1, 6},
        {2, 5},
        {3, 3},
        {4, 20},
        {5, 15}
    };

    // Cargar los contenedores en el buque
    std::vector<Contenedor> contenedoresSeleccionados = cargarContenedores(capacidadBuque, contenedores);

    // Imprimir los contenedores seleccionados y su suma total de pesos
    imprimirContenedores(contenedoresSeleccionados);
    std::cout << "Suma total de pesos: ";
    int sumaPesos = 0;
    for (const Contenedor& contenedor : contenedoresSeleccionados) {
        sumaPesos += contenedor.peso;
    }
    std::cout << sumaPesos << " toneladas" << std::endl;

    return 0;
}
