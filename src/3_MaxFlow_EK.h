
#ifndef MAXFLOW_EK_H
#define MAXFLOW_EK_H

#include <bits/stdc++.h>
using namespace std;

// Busca un camino disponible utilizando BFS.
bool buscarCaminoEK(const vector<vector<long long>> &residual,
                    const vector<vector<int>> &vecinos,
                    int origen,
                    int destino,
                    vector<int> &padre) {

    int n = (int)residual.size();

    padre.assign(n, -1);

    // Cola implementada manualmente.
    vector<int> cola(n);

    int primero = 0;
    int ultimo = 0;

    cola[ultimo] = origen;
    ultimo++;

    padre[origen] = origen;

    while (primero < ultimo) {

        int actual = cola[primero];
        primero++;

        // Revisar los vecinos del nodo actual.
        for (int i = 0; i < (int)vecinos[actual].size(); i++) {

            int siguiente = vecinos[actual][i];

            // Evitar visitar nuevamente el mismo nodo.
            if (padre[siguiente] != -1) {
                continue;
            }

            // Solo recorrer conexiones con capacidad disponible.
            if (residual[actual][siguiente] <= 0) {
                continue;
            }

            padre[siguiente] = actual;

            // Se encontro un camino hasta el destino.
            if (siguiente == destino) {
                return true;
            }

            cola[ultimo] = siguiente;
            ultimo++;
        }
    }

    return false;
}

// Calcula el flujo maximo usando Edmonds-Karp.
inline int maxFlowEdmondsKarp(const vector<vector<int>> &capacity,
                             int n,
                             int source,
                             int sink) {

    // Verificar que los nodos sean validos.
    if (n <= 0 || source < 0 || sink < 0 ||
        source >= n || sink >= n) {
        return 0;
    }

    if (source == sink) {
        return 0;
    }

    // Crear una copia de la matriz de capacidades.
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

    // Guardar los vecinos de cada nodo.
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

    // Buscar caminos mientras exista capacidad disponible.
    while (buscarCaminoEK(residual, vecinos,
                          source, sink, padre)) {

        long long cuello = LLONG_MAX;
        int actual = sink;

        // Encontrar la capacidad minima del camino.
        while (actual != source) {

            int anterior = padre[actual];

            if (residual[anterior][actual] < cuello) {
                cuello = residual[anterior][actual];
            }

            actual = anterior;
        }

        // Actualizar las capacidades residuales.
        actual = sink;

        while (actual != source) {

            int anterior = padre[actual];

            // Restar el flujo enviado.
            residual[anterior][actual] -= cuello;

            // Agregar capacidad en la direccion inversa.
            residual[actual][anterior] += cuello;

            actual = anterior;
        }

        flujoTotal += cuello;
    }

    // La funcion debe devolver un entero.
    if (flujoTotal > INT_MAX) {
        return -1;
    }

    return (int)flujoTotal;
}

#endif
