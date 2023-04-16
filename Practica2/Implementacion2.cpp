#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Definición de un punto en K dimensiones
struct Point {
    vector<double> coords;
};

// Compara dos puntos según una coordenada
bool comparePoints(const Point& p1, const Point& p2, int coord) {
    return p1.coords[coord] < p2.coords[coord];
}

// Devuelve el conjunto de puntos no dominados de un subconjunto de puntos
vector<Point> nonDominatedSet(vector<Point>& points, int start, int end) {
    // Caso base: un solo punto
    if (start == end) {
        vector<Point> result;
        result.push_back(points[start]);
        return result;
    }

    // Dividir el conjunto de puntos según la coordenada mediana
    int mid = start + (end - start) / 2;
    int k = points[start].coords.size();
    vector<Point> leftPoints = nonDominatedSet(points, start, mid);
    vector<Point> rightPoints = nonDominatedSet(points, mid + 1, end);
    vector<Point> result;
    int left = 0, right = 0;

    // Combinar los conjuntos de puntos no dominados de las dos mitades
    while (left < leftPoints.size() && right < rightPoints.size()) {
        bool isDominated = false;
        for (int i = 0; i < k; i++) {
            if (leftPoints[left].coords[i] > rightPoints[right].coords[i]) {
                isDominated = true;
                break;
            }
        }
        if (isDominated) {
            right++;
        } else {
            result.push_back(leftPoints[left]);
            left++;
        }
    }
    while (left < leftPoints.size()) {
        result.push_back(leftPoints[left]);
        left++;
    }
    while (right < rightPoints.size()) {
        result.push_back(rightPoints[right]);
        right++;
    }
    return result;
}

int main() {
    // Ejemplo de uso
    vector<Point> points = {
        {{1, 3, 2}},
        {{2, 2, 3}},
        {{3, 1, 1}},
        {{4, 5, 6}},
        {{5, 4, 4}},
        {{6, 6, 5}}
    };
    vector<Point> nonDominated = nonDominatedSet(points, 0, points.size() - 1);
    for (Point p : nonDominated) {
        for (double coord : p.coords) {
            cout << coord << " ";
        }
        cout << endl;
    }
    return 0;
}
