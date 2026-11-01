#ifndef OUTPUT_H
#define OUTPUT_H
#include <bits/stdc++.h>
#include "input.h"
using namespace std;

// Resultados calculados a partir de los datos de entrada.
struct Results {
    vector<pair<int,int>> kruskalEdges;
    int kruskalCost = 0;
    vector<pair<int,int>> primEdges;
    int primCost = 0;
    vector<int> route;
    int tourCost = 0;
    int maxFlowValue = 0;
    int nearestIdxBruteForce = 0;
    double nearestDistBruteForce = 0.0;
    int nearestIdxKDTree = 0;
    double nearestDistKDTree = 0.0;
};

static void printPoint1(const vector<pair<int,int>> &edges, int kruskalCost, int primCost){
    cout << string(12, ' ') << "Punto 01" << "\n\n";
    for (auto &e : edges)
        cout << "(" << (e.first + 1) << "," << (e.second + 1) << ")\n";
    cout << "Costo total (Kruskal): " << kruskalCost << "\n";
    cout << "Costo total (Prim): " << primCost << "\n\n";
}

static void printPoint2(const vector<int> &route, int tourCost){
    cout << string(12, ' ') << "Punto 02" << "\n\n";
    cout << "El recorrido:\n";
    for (size_t k = 0; k < route.size(); k++) {
        cout << (route[k] + 1);
        if (k + 1 < route.size()) cout << " -> ";
    }
    cout << "\n";
    cout << "El costo: " << tourCost << "\n\n";
}

static void printPoint3(int maxFlowValue){
    cout << string(12, ' ') << "Punto 03" << "\n\n";
    cout << "Flujo máximo: " << maxFlowValue << "\n\n";
}

static void printPoint4(const pair<double,double> &newCentral,
                        const pair<double,double> &nearestBruteForce, double distBruteForce,
                        const pair<double,double> &nearestKDTree, double distKDTree){
    cout << string(12, ' ') << "Punto 04" << "\n\n";
    cout << "La central más cercana a [" << newCentral.first << ", " << newCentral.second
         << "] es [" << nearestBruteForce.first << ", " << nearestBruteForce.second
         << "] con una distancia de " << distBruteForce << " (fuerza bruta).\n";
    cout << "La central más cercana a [" << newCentral.first << ", " << newCentral.second
         << "] es [" << nearestKDTree.first << ", " << nearestKDTree.second
         << "] con una distancia de " << distKDTree << " (KD-Tree).\n";
}

void printOutput(const InputData &data, const Results &results){
    printPoint1(results.kruskalEdges, results.kruskalCost, results.primCost);
    printPoint2(results.route, results.tourCost);
    printPoint3(results.maxFlowValue);
    printPoint4(data.newCentral,
                data.centrales[results.nearestIdxBruteForce], results.nearestDistBruteForce,
                data.centrales[results.nearestIdxKDTree], results.nearestDistKDTree);
}
#endif
