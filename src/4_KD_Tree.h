
#ifndef KD_TREE_H
#define KD_TREE_H

#include <bits/stdc++.h>
using namespace std;

// cada nodo guarda una central y sus dos hijos
struct NodoKD {
    int punto;
    int eje;
    int izquierdo;
    int derecho;
};

// compara dos puntos utilizando el eje X o Y
bool menorKD(int a, int b, int eje,
             const vector<pair<double, double>> &puntos) {

    double principalA;
    double principalB;
    double secundarioA;
    double secundarioB;

    if (eje == 0) {
        principalA = puntos[a].first;
        principalB = puntos[b].first;

        secundarioA = puntos[a].second;
        secundarioB = puntos[b].second;
    } else {
        principalA = puntos[a].second;
        principalB = puntos[b].second;

        secundarioA = puntos[a].first;
        secundarioB = puntos[b].first;
    }

    if (principalA != principalB) {
        return principalA < principalB;
    }

    if (secundarioA != secundarioB) {
        return secundarioA < secundarioB;
    }

    return a < b;
}

// ordena los puntos segun el eje utilizando Merge Sort
void mergeSortKD(vector<int> &orden,
                 vector<int> &auxiliar,
                 int inicio,
                 int fin,
                 int eje,
                 const vector<pair<double, double>> &puntos) {

    if (fin - inicio <= 1) {
        return;
    }

    int mitad = (inicio + fin) / 2;

    mergeSortKD(orden, auxiliar, inicio, mitad, eje, puntos);
    mergeSortKD(orden, auxiliar, mitad, fin, eje, puntos);

    int i = inicio;
    int j = mitad;
    int k = inicio;

    while (i < mitad && j < fin) {

        if (menorKD(orden[j], orden[i], eje, puntos)) {
            auxiliar[k] = orden[j];
            j++;
        } else {
            auxiliar[k] = orden[i];
            i++;
        }

        k++;
    }

    while (i < mitad) {
        auxiliar[k] = orden[i];
        i++;
        k++;
    }

    while (j < fin) {
        auxiliar[k] = orden[j];
        j++;
        k++;
    }

    for (int p = inicio; p < fin; p++) {
        orden[p] = auxiliar[p];
    }
}

// construye el arbol alternando entre los ejes X y Y
int construirKD(const vector<pair<double, double>> &puntos,
                vector<int> &orden,
                vector<int> &auxiliar,
                vector<NodoKD> &arbol,
                int inicio,
                int fin,
                int nivel) {

    if (inicio >= fin) {
        return -1;
    }

    // eje 0 = X, eje 1 = Y
    int eje = nivel % 2;

    mergeSortKD(orden, auxiliar, inicio, fin, eje, puntos);

    // seleccionar el punto central
    int mitad = (inicio + fin) / 2;

    NodoKD nuevo;

    nuevo.punto = orden[mitad];
    nuevo.eje = eje;
    nuevo.izquierdo = -1;
    nuevo.derecho = -1;

    int posicion = (int)arbol.size();

    arbol.push_back(nuevo);

    // construir el lado izquierdo
    arbol[posicion].izquierdo = construirKD(
        puntos, orden, auxiliar, arbol,
        inicio, mitad, nivel + 1
    );

    // construir el lado derecho
    arbol[posicion].derecho = construirKD(
        puntos, orden, auxiliar, arbol,
        mitad + 1, fin, nivel + 1
    );

    return posicion;
}

// calcula la distancia euclidiana al cuadrado
double distanciaCuadradaKD(const pair<double, double> &a,
                          const pair<double, double> &b) {

    double dx = a.first - b.first;
    double dy = a.second - b.second;

    return dx * dx + dy * dy;
}

// busca la central mas cercana dentro del arbol
void buscarKD(const vector<pair<double, double>> &puntos,
              const vector<NodoKD> &arbol,
              int nodo,
              const pair<double, double> &consulta,
              int &mejorPunto,
              double &mejorDistancia2) {

    if (nodo == -1) {
        return;
    }

    const NodoKD &actual = arbol[nodo];

    // calcular la distancia al punto actual
    double distancia2 = distanciaCuadradaKD(
        puntos[actual.punto], consulta
    );

    // actualizar la mejor central encontrada
    if (mejorPunto == -1 ||
        distancia2 < mejorDistancia2 ||
        (distancia2 == mejorDistancia2 &&
         actual.punto < mejorPunto)) {

        mejorPunto = actual.punto;
        mejorDistancia2 = distancia2;
    }

    // comparar la consulta con el eje actual
    double diferencia;

    if (actual.eje == 0) {
        diferencia = consulta.first -
                     puntos[actual.punto].first;
    } else {
        diferencia = consulta.second -
                     puntos[actual.punto].second;
    }

    int cercano = actual.izquierdo;
    int lejano = actual.derecho;

    if (diferencia >= 0) {
        cercano = actual.derecho;
        lejano = actual.izquierdo;
    }

    // buscar primero en la rama mas cercana
    buscarKD(puntos, arbol, cercano, consulta,
             mejorPunto, mejorDistancia2);

    // revisar la otra rama solo si puede tener
    // una central igual o mas cercana
    if (diferencia * diferencia <= mejorDistancia2) {

        buscarKD(puntos, arbol, lejano, consulta,
                 mejorPunto, mejorDistancia2);
    }
}

// encuentra la central mas cercana a la nueva ubicacion
inline int nearestCentralKDTree(
    const vector<pair<double, double>> &centrales,
    const pair<double, double> &newCentral,
    double &distance) {

    int n = (int)centrales.size();

    if (n == 0) {
        distance = -1;
        return -1;
    }

    // crear una lista con los indices de las centrales
    vector<int> orden(n);

    for (int i = 0; i < n; i++) {
        orden[i] = i;
    }

    vector<int> auxiliar(n);
    vector<NodoKD> arbol;

    arbol.reserve(n);

    // construir el KD-Tree
    int raiz = construirKD(
        centrales, orden, auxiliar, arbol,
        0, n, 0
    );

    int mejorPunto = -1;
    double mejorDistancia2 = 0;

    // buscar la central mas cercana
    buscarKD(
        centrales, arbol, raiz, newCentral,
        mejorPunto, mejorDistancia2
    );

    // convertir la distancia al cuadrado a distancia real
    distance = sqrt(mejorDistancia2);

    return mejorPunto;
}

#endif
