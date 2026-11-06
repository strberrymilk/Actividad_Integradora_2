// Ana Camila Cuevas González A01712439

#ifndef TSP_H
#define TSP_H

#include <bits/stdc++.h>
using namespace std;

const long long INFINITO_TSP = LLONG_MAX / 4;

// obtiene el costo de ir de una colonia a otra (0 significa que no es factible)
long long costoRutaTSP(int peso) {
    if (peso > 0) {
        return peso;
    }

    return INFINITO_TSP;
}

// resuelve el problema del agente viajero con programacion dinamica
// (algoritmo de Held-Karp usando mascaras de bits)
inline void tsp(const vector<vector<int>> &graph,
                int n,
                vector<int> &route,
                int &cost) {

    route.clear();
    cost = 0;

    if (n <= 0) {
        cost = -1;
        return;
    }

    if (n == 1) {
        route.push_back(0);
        route.push_back(0);
        return;
    }

    int totalMascaras = 1 << n;

    // dp[mascara][i] = costo minimo para visitar las colonias de la
    // mascara terminando en la colonia i, habiendo iniciado en la colonia 0
    vector<vector<long long>> dp(
        totalMascaras, vector<long long>(n, INFINITO_TSP)
    );

    vector<vector<int>> previo(totalMascaras, vector<int>(n, -1));

    // caso base: solo se ha visitado la colonia de origen
    dp[1][0] = 0;

    for (int mascara = 1; mascara < totalMascaras; mascara++) {

        // la colonia de origen siempre debe estar visitada
        if (!(mascara & 1)) {
            continue;
        }

        for (int actual = 0; actual < n; actual++) {

            if (!(mascara & (1 << actual))) {
                continue;
            }

            if (dp[mascara][actual] >= INFINITO_TSP) {
                continue;
            }

            // intentar extender el recorrido hacia una colonia sin visitar
            for (int siguiente = 0; siguiente < n; siguiente++) {

                if (mascara & (1 << siguiente)) {
                    continue;
                }

                long long peso = costoRutaTSP(graph[actual][siguiente]);

                if (peso >= INFINITO_TSP) {
                    continue;
                }

                int nuevaMascara = mascara | (1 << siguiente);
                long long nuevoCosto = dp[mascara][actual] + peso;

                if (nuevoCosto < dp[nuevaMascara][siguiente]) {
                    dp[nuevaMascara][siguiente] = nuevoCosto;
                    previo[nuevaMascara][siguiente] = actual;
                }
            }
        }
    }

    // cerrar el recorrido regresando a la colonia de origen
    int mascaraCompleta = totalMascaras - 1;
    long long mejorCosto = INFINITO_TSP;
    int mejorFinal = -1;

    for (int actual = 1; actual < n; actual++) {

        if (dp[mascaraCompleta][actual] >= INFINITO_TSP) {
            continue;
        }

        long long regreso = costoRutaTSP(graph[actual][0]);

        if (regreso >= INFINITO_TSP) {
            continue;
        }

        long long total = dp[mascaraCompleta][actual] + regreso;

        if (total < mejorCosto) {
            mejorCosto = total;
            mejorFinal = actual;
        }
    }

    // no existe un recorrido que visite todas las colonias y regrese
    if (mejorFinal == -1 || mejorCosto >= INFINITO_TSP) {
        cost = -1;
        return;
    }

    // reconstruir el recorrido a partir de los padres guardados
    vector<int> recorrido;

    int mascaraActual = mascaraCompleta;
    int nodoActual = mejorFinal;

    while (nodoActual != -1) {
        recorrido.push_back(nodoActual);

        int anterior = previo[mascaraActual][nodoActual];

        mascaraActual ^= (1 << nodoActual);
        nodoActual = anterior;
    }

    reverse(recorrido.begin(), recorrido.end());

    // agregar el regreso a la colonia de origen
    recorrido.push_back(0);

    route = recorrido;
    cost = (int)mejorCosto;
}

#endif
