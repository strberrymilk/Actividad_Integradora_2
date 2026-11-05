
#ifndef MAXFLOW_EK_H
#define MAXFLOW_EK_H

#include <bits/stdc++.h>
using namespace std;

// busca un camino disponible utilizando BFS
bool buscarCaminoEK(const vector<vector<long long>> &residual,
                    const vector<vector<int>> &vecinos,
                    int origen,
                    int destino,
                    vector<int> &padre) {

    int n = (int)residual.size();

    padre.assign(n, -1);

    // cola implementada manualmente
    vector<int> cola(n);

    int primero = 0;
    int ultimo = 0;

    cola[ultimo] = origen;
    ultimo++;

    padre[origen] = origen;

    while (primero < ultimo) {

        int actual = cola[primero];
        primero++;

        // revisar los vecinos del nodo actual
        for (int i = 0; i < (int)vecinos[actual].size(); i++) {

            int siguiente = vecinos[actual][i];

            // evitar visitar nuevamente el mismo nodo
            if (padre[siguiente] != -1) {
                continue;
            }

            // solo recorrer conexiones con capacidad disponible
            if (residual[actual][siguiente] <= 0) {
                continue;
            }

            padre[siguiente] = actual;

            // se encontro un camino hasta el destino
            if (siguiente == destino) {
                return true;
            }

            cola[ultimo] = siguiente;
            ultimo++;
        }
    }

    return false;
}

// calcula el flujo maximo usando Edmonds-Karp
inline int maxFlowEdmondsKarp(const vector<vector<int>> &capacity,
                             int n,
                             int source,
                             int sink) {

    // verificar que los nodos sean validos
    if (n <= 0 || source < 0 || sink < 0 ||
        source >= n || sink >= n) {
        return 0;
    }

    if (source == sink) {
        return 0;
    }

    // crear una copia de la matriz de capacidades
    vector<vector<long long>> residual(
        n, vector<long long>(n, 0)
    );

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (i != j && capacity[i][j] > 0) {
                residual[i][j] = capacity[i][j];
            }
        }
    }

    // guardar los vecinos de cada nodo
    vector<vector<int>> vecinos(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            if (residual[i][j] > 0 || residual[j][i] > 0) {
                vecinos[i].push_back(j);
                vecinos[j].push_back(i);
            }
        }
    }

    long long flujoTotal = 0;
    vector<int> padre;

    // buscar caminos mientras exista capacidad disponible
    while (buscarCaminoEK(residual, vecinos,
                          source, sink, padre)) {

        long long cuello = LLONG_MAX;
        int actual = sink;

        // encontrar la capacidad minima del camino
        while (actual != source) {

            int anterior = padre[actual];

            if (residual[anterior][actual] < cuello) {
                cuello = residual[anterior][actual];
            }

            actual = anterior;
        }

        // actualizar las capacidades residuales
        actual = sink;

        while (actual != source) {

            int anterior = padre[actual];

            // restar el flujo enviado
            residual[anterior][actual] -= cuello;

            // agregar capacidad en la direccion inversa
            residual[actual][anterior] += cuello;

            actual = anterior;
        }

        flujoTotal += cuello;
    }

    // la funcion debe devolver un entero
    if (flujoTotal > INT_MAX) {
        return -1;
    }

    return (int)flujoTotal;
}

#endif
