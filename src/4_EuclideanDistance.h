#ifndef EUCLIDEAN_DISTANCE_H
#define EUCLIDEAN_DISTANCE_H
#include <bits/stdc++.h>
using namespace std;

// Distancia euclidiana entre dos puntos.
double euclideanDistance(const pair<double,double> &a, const pair<double,double> &b);

// Busca la central más cercana probando una por una (fuerza bruta).
int nearestCentralBruteForce(const vector<pair<double,double>> &centrales, const pair<double,double> &newCentral, double &distance);
#endif
