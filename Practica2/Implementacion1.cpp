#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    vector<double> coords;
    bool isDominated;
};

bool comparePoints(const Point& p1, const Point& p2) {
    for (int i = 0; i < p1.coords.size(); i++) {
        if (p1.coords[i] < p2.coords[i]) {
            return true;
        } else if (p1.coords[i] > p2.coords[i]) {
            return false;
        }
    }
    return false;
}

vector<Point> mergePoints(vector<Point>& left, vector<Point>& right) {
    vector<Point> result;
    int i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (comparePoints(left[i], right[j])) {
            result.push_back(left[i++]);
        } else {
            result.push_back(right[j++]);
        }
    }
    while (i < left.size()) {
        result.push_back(left[i++]);
    }
    while (j < right.size()) {
        result.push_back(right[j++]);
    }
    return result;
}

vector<Point> findNonDominatedPoints(vector<Point>& points) {
    if (points.size() == 1) {
        points[0].isDominated = false;
        return points;
    }

    int mid = points.size() / 2;
    vector<Point> left(points.begin(), points.begin() + mid);
    vector<Point> right(points.begin() + mid, points.end());

    left = findNonDominatedPoints(left);
    right = findNonDominatedPoints(right);

    vector<Point> result = mergePoints(left, right);

    // Mark dominated points
    for (int i = 0; i < result.size(); i++) {
        if (!result[i].isDominated) {
            for (int j = i + 1; j < result.size(); j++) {
                if (!result[j].isDominated) {
                    bool dominated = true;
                    for (int k = 0; k < result[i].coords.size(); k++) {
                        if (result[j].coords[k] > result[i].coords[k]) {
                            dominated = false;
                            break;
                        }
                    }
                    if (dominated) {
                        result[j].isDominated = true;
                    }
                }
            }
        }
    }

    // Filter out dominated points
    vector<Point> nonDominated;
    for (int i = 0; i < result.size(); i++) {
        if (!result[i].isDominated) {
            nonDominated.push_back(result[i]);
        }
    }

    return nonDominated;
}

int main() {
    // Example usage
    vector<Point> points = {
        {{1, 2, 3}},
        {{3, 2, 1}},
        {{2, 3, 1}},
        {{4, 4, 4}},
        {{2, 2, 2}}
    };

    vector<Point> nonDominated = findNonDominatedPoints(points);

    cout << "Non-dominated points:" << endl;
    for (int i = 0; i < nonDominated.size(); i++) {
        for (int j = 0; j < nonDominated[i].coords.size(); j++) {
            cout << nonDominated[i].coords[j] << " ";
        }
        cout << endl;
    }

    return 0;
}




/*
----------PSEUDOCODIGO-----------

function findNonDominatedPoints(points)
    if size(points) == 1:
        return points
    
    mid = size(points) / 2
    leftPoints = findNonDominatedPoints(points[0:mid])
    rightPoints = findNonDominatedPoints(points[mid:])
    
    return mergePoints(leftPoints, rightPoints)
    
function mergePoints(leftPoints, rightPoints)
    nonDominatedPoints = []
    
    for each point in leftPoints:
        dominated = false
        for each otherPoint in rightPoints:
            if otherPoint dominates point:
                dominated = true
                break
        if not dominated:
            nonDominatedPoints.append(point)
    
    for each point in rightPoints:
        dominated = false
        for each otherPoint in leftPoints:
            if otherPoint dominates point:
                dominated = true
                break
        if not dominated:
            nonDominatedPoints.append(point)
    
    return nonDominatedPoints

*/