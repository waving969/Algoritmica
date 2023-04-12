#include <iostream>
#include <vector>
#include <array>

using namespace std;

typedef array<double, 10> Point;
typedef vector<Point> PointSet;

bool dominates(const Point& p1, const Point& p2) {
    bool strict = false;
    for (size_t i = 0; i < 10; ++i) {
        if (p1[i] < p2[i]) {
            return false;
        }
        else if (p1[i] > p2[i]) {
            strict = true;
        }
    }
    return strict;
}

PointSet findNonDominatedPoints(const PointSet& C) {
    PointSet P;
    for (const Point& p1 : C) {
        bool is_dominated = false;
        for (const Point& p2 : C) {
            if (dominates(p2, p1)) {
                is_dominated = true;
                break;
            }
        }
        if (!is_dominated) {
            P.push_back(p1);
        }
    }
    return P;
}

int main() {
    PointSet C = {{ {5,8,8,5,8,7,5,1,7,7},
                    {3,4,7,5,3,5,1,1,9,3},
                    {0,4,4,8,3,5,9,3,7,4},
                    {9,9,9,9,9,9,9,9,9,9}}};
    PointSet P = findNonDominatedPoints(C);
    for (const Point& p : P) {
        for (double v : p) {
            cout << v << " ";
        }
        cout << endl;
    }
    return 0;
}
