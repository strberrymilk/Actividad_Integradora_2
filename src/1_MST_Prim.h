// Ana Camila Cuevas González A01712439

#ifndef MST_PRIM_H
#define MST_PRIM_H

#include <bits/stdc++.h>
using namespace std;

// obtiene la distancia entre dos colonias en un grafo no dirigido
int pesoCablePrim(int ida, int vuelta) {
    if (ida > 0 && vuelta > 0) {
        if (ida < vuelta) {
            return ida;
        }
        return vuelta;
    }

    if (ida > 0) {
        return ida;
    }

    if (vuelta > 0) {
        return vuelta;
    }

    return 0;
}

// calcula el arbol de expansion minima con Prim
inline void mstPrim(const vector<vector<int>> &graph,
                    int n,
                    vector<pair<int, int>> &edges,
                    int &totalCost) {

    edges.clear();
    totalCost = 0;

    if (n <= 0) {
        totalCost = -1;
        return;
    }

    if (n == 1) {
        return;
    }

    // construir la matriz de pesos no dirigida a partir del grafo
    vector<vector<int>> peso(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            int valor = pesoCablePrim(graph[i][j], graph[j][i]);

            peso[i][j] = valor;
            peso[j][i] = valor;
        }
    }

    vector<bool> enArbol(n, false);
    vector<int> costoMinimo(n, INT_MAX);
    vector<int> padre(n, -1);

    // el arbol siempre inicia en la primera colonia
    costoMinimo[0] = 0;

    long long suma = 0;

    for (int iteracion = 0; iteracion < n; iteracion++) {

        // buscar la colonia mas barata que aun no esta en el arbol
        int actual = -1;

        for (int i = 0; i < n; i++) {
            if (!enArbol[i]) {
                if (actual == -1 || costoMinimo[i] < costoMinimo[actual]) {
                    actual = i;
                }
            }
        }

        // si ninguna colonia es alcanzable, el grafo esta desconectado
        if (actual == -1 || costoMinimo[actual] == INT_MAX) {
            edges.clear();
            totalCost = -1;
            return;
        }

        enArbol[actual] = true;
        suma += costoMinimo[actual];

        if (padre[actual] != -1) {
            edges.push_back(make_pair(padre[actual], actual));
        }

        // actualizar el costo minimo de las colonias vecinas
        for (int vecino = 0; vecino < n; vecino++) {

            if (enArbol[vecino]) {
                continue;
            }

            int distancia = peso[actual][vecino];

            if (distancia <= 0) {
                continue;
            }

            if (distancia < costoMinimo[vecino]) {
                costoMinimo[vecino] = distancia;
                padre[vecino] = actual;
            }
        }
    }

    // verificar que todas las colonias quedaron conectadas
    if ((int)edges.size() != n - 1 || suma > INT_MAX) {
        edges.clear();
        totalCost = -1;
        return;
    }

    totalCost = (int)suma;
}

#endif
