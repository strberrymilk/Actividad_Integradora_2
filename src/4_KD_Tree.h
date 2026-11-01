#ifndef KD_TREE_H
#define KD_TREE_H
#include <bits/stdc++.h>
using namespace std;

// Busca la central más cercana usando un KD-Tree.
int nearestCentralKDTree(const vector<pair<double,double>> &centrales, const pair<double,double> &newCentral, double &distance);
#endif
