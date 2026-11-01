#ifndef INPUT_H
#define INPUT_H
#include <bits/stdc++.h>
using namespace std;

// Datos leídos desde la entrada estándar.
struct InputData {
    int n = 0;                              // número de colonias
    vector<vector<int>> graph;              // matriz de costos de cableado
    vector<vector<int>> maxFlows;           // matriz de capacidades de flujo
    vector<pair<double,double>> centrales;  // coordenadas de las centrales existentes
    pair<double,double> newCentral;         // coordenada de la nueva central
};

// Lee un punto en formato "(x,y)" o "(x, y)" 
pair<double,double> readPoint(){
    char c;
    double x, y;
    cin>>c>>x>>c>>y>>c;  
    return {x, y};
}

InputData input(){
    InputData data;
    cin >> data.n;
    int n = data.n;

    // Matriz de costos de cableado entre colonias.
    data.graph.assign(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> data.graph[i][j];

    // Matriz de capacidades máximas de flujo entre colonias.
    data.maxFlows.assign(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> data.maxFlows[i][j];

    // Coordenadas de las centrales existentes.
    data.centrales.resize(n);
    for (int i = 0; i < n; i++)
        data.centrales[i] = readPoint();

    // Coordenada de la nueva central a ubicar.
    data.newCentral = readPoint();

    return data;
}

#endif
