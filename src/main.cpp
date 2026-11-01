#include<bits/stdc++.h>
#include "input.h"
#include "output.h"
#include "1_MST_Kruskal.h"
#include "1_MST_Prim.h"
#include "2_TSP.h"
#include "3_MaxFlow_EK.h"
#include "4_EuclideanDistance.h"
#include "4_KD_Tree.h"
using namespace std;

int main(){
    InputData data = input();

    Results results;
    mstKruskal(data.graph, data.n, results.kruskalEdges, results.kruskalCost);
    mstPrim(data.graph, data.n, results.primEdges, results.primCost);
    tsp(data.graph, data.n, results.route, results.tourCost);
    results.maxFlowValue = maxFlowEdmondsKarp(data.maxFlows, data.n, 0, data.n - 1);
    results.nearestIdxBruteForce = nearestCentralBruteForce(data.centrales, data.newCentral, results.nearestDistBruteForce);
    results.nearestIdxKDTree = nearestCentralKDTree(data.centrales, data.newCentral, results.nearestDistKDTree);

    printOutput(data, results);

    return 0;
}
