// Cesar Augusto Ramirez Davila A01712439

#ifndef MST_KRUSKAL_H
#define MST_KRUSKAL_H

#include <bits/stdc++.h>
using namespace std;

// una arista representa un posible cable entre dos colonias
struct AristaKruskal {
    int origen;
    int destino;
    int peso;
};

// compara dos aristas para ordenarlas por peso
bool esMenorKruskal(const AristaKruskal &a, const AristaKruskal &b) {
    if (a.peso != b.peso) {
        return a.peso < b.peso;
    }

    if (a.origen != b.origen) {
        return a.origen < b.origen;
    }

    return a.destino < b.destino;
}

// ordena las aristas utilizando Merge Sort
void mergeSortKruskal(vector<AristaKruskal> &aristas,
                      vector<AristaKruskal> &auxiliar,
                      int inicio, int fin) {

    if (fin - inicio <= 1) {
        return;
    }

    int mitad = (inicio + fin) / 2;

    mergeSortKruskal(aristas, auxiliar, inicio, mitad);
    mergeSortKruskal(aristas, auxiliar, mitad, fin);

    int i = inicio;
    int j = mitad;
    int k = inicio;

    while (i < mitad && j < fin) {
        if (esMenorKruskal(aristas[j], aristas[i])) {
            auxiliar[k] = aristas[j];
            j++;
        } else {
            auxiliar[k] = aristas[i];
            i++;
        }
        k++;
    }

    while (i < mitad) {
        auxiliar[k] = aristas[i];
        i++;
        k++;
    }

    while (j < fin) {
        auxiliar[k] = aristas[j];
        j++;
        k++;
    }

    for (int p = inicio; p < fin; p++) {
        aristas[p] = auxiliar[p];
    }
}

// busca la raiz del conjunto al que pertenece un nodo
int buscarRaizKruskal(vector<int> &padre, int nodo) {
    if (padre[nodo] != nodo) {
        padre[nodo] = buscarRaizKruskal(padre, padre[nodo]);
    }

    return padre[nodo];
}

// une dos conjuntos si todavia no estan conectados
bool unirKruskal(vector<int> &padre,
                 vector<int> &tamano,
                 int a, int b) {

    int raizA = buscarRaizKruskal(padre, a);
    int raizB = buscarRaizKruskal(padre, b);

    // si tienen la misma raiz, unirlos formaria un ciclo
    if (raizA == raizB) {
        return false;
    }

    // unimos el conjunto pequeno al mas grande
    if (tamano[raizA] < tamano[raizB]) {
        int temporal = raizA;
        raizA = raizB;
        raizB = temporal;
    }

    padre[raizB] = raizA;
    tamano[raizA] += tamano[raizB];

    return true;
}

// obtiene la distancia entre dos colonias en un grafo no dirigido
int pesoCableKruskal(int ida, int vuelta) {
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

// calcula el arbol de expansion minima con Kruskal
inline void mstKruskal(const vector<vector<int>> &graph,
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

    vector<AristaKruskal> aristas;

    // obtener las conexiones disponibles entre colonias
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            int peso = pesoCableKruskal(graph[i][j], graph[j][i]);

            if (peso > 0) {
                AristaKruskal nueva;

                nueva.origen = i;
                nueva.destino = j;
                nueva.peso = peso;

                aristas.push_back(nueva);
            }
        }
    }

    // ordenar las conexiones de menor a mayor costo
    vector<AristaKruskal> auxiliar(aristas.size());

    mergeSortKruskal(aristas, auxiliar, 0, (int)aristas.size());

    // inicializar los conjuntos de Union-Find
    vector<int> padre(n);
    vector<int> tamano(n, 1);

    for (int i = 0; i < n; i++) {
        padre[i] = i;
    }

    long long suma = 0;

    // seleccionar las conexiones mas baratas sin formar ciclos
    for (int i = 0; i < (int)aristas.size(); i++) {

        int a = aristas[i].origen;
        int b = aristas[i].destino;

        if (unirKruskal(padre, tamano, a, b)) {
            edges.push_back(make_pair(a, b));
            suma += aristas[i].peso;
        }

        // el arbol necesita exactamente n-1 conexiones
        if ((int)edges.size() == n - 1) {
            break;
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
