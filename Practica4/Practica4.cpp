#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Empresa {
    int a;  // Número de acciones disponibles
    int p;  // Precio por acción
    int b;  // Beneficio por acción (en tanto por uno)
    int c;  // Comisión por operación
};

int max_beneficio(const vector<Empresa>& empresas, int X) {
    const int N = empresas.size();
    vector<vector<int>> DP(N + 1, vector<int>(X + 1, 0));
    
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

int main() {
    vector<Empresa> empresas = {
        {10, 5, 2, 1},
        {5, 8, 3, 2},
        {8, 6, 4, 1},
        {4, 10, 2, 3},
        {6, 4, 1, 2},
    };
    int X = 30;
    
    int beneficio_maximo = max_beneficio(empresas, X);
    cout << "El beneficio máximo que se puede obtener es: " << beneficio_maximo << endl;
    
    return 0;
}
