// Ana Camila Cuevas González A01412609

#ifndef EUCLIDEAN_DISTANCE_H
#define EUCLIDEAN_DISTANCE_H

#include <bits/stdc++.h>
using namespace std;

// calcula la distancia euclidiana entre dos puntos
inline double euclideanDistance(const pair<double, double> &a,
                                const pair<double, double> &b) {

    double dx = a.first - b.first;
    double dy = a.second - b.second;

    return sqrt(dx * dx + dy * dy);
}

// busca la central mas cercana probando una por una (fuerza bruta)
inline int nearestCentralBruteForce(
    const vector<pair<double, double>> &centrales,
    const pair<double, double> &newCentral,
    double &distance) {

    int n = (int)centrales.size();

    if (n == 0) {
        distance = -1;
        return -1;
    }

    int mejorPunto = -1;
    double mejorDistancia = 0;

    // revisar cada central y quedarse con la mas cercana
    for (int i = 0; i < n; i++) {

        double distanciaActual = euclideanDistance(centrales[i], newCentral);

        if (mejorPunto == -1 || distanciaActual < mejorDistancia) {
            mejorPunto = i;
            mejorDistancia = distanciaActual;
        }
    }

    distance = mejorDistancia;

    return mejorPunto;
}

#endif
