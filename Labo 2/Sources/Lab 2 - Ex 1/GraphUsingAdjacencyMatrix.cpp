#include "GraphUsingAdjacencyMatrix.h"
 
namespace ASD2 {
 
    void GraphUsingAdjacencyMatrix::Init(int V) {
        adjMatrix.resize(V);
        for (int v = 0; v < V; v++)
            adjMatrix[v].resize(V);
    }
 
    GraphUsingAdjacencyMatrix::GraphUsingAdjacencyMatrix(int V) {
        Init(V);
    }
 
    GraphUsingAdjacencyMatrix::GraphUsingAdjacencyMatrix(std::istream& s) {
        int V, E, v, w;
 
        s >> V;
        s >> E;
 
        Init(V);
 
        for (int i = 0; i < E; i++) {
            s >> v;
            s >> w;
            addEdge(v, w);
        }
    }
 
    //throws std::out_of_range
    void GraphUsingAdjacencyMatrix::addEdge(int v, int w) {
        /* A IMPLEMENTER */
        // throw automatiquement std::out_of_range
        // met a true les deux correspondances dans la matrice
        adjMatrix.at(v).at(w) = true;
        adjMatrix.at(w).at(v) = true;
    }
   
    //throws std::out_of_range
    GraphUsingAdjacencyMatrix::Iterable GraphUsingAdjacencyMatrix::adjacent(int v) const {
        // Generation de la liste des sommets adjacents en fonction de la matrice
        GraphUsingAdjacencyMatrix::Iterable liste;
        for (int i = 0 ; i < adjMatrix.size(); i++){
            if (adjMatrix[v][i]) {
                liste.push_back(i);
            }
        }
        return liste;
    }
 
    int GraphUsingAdjacencyMatrix::V() const {
        return adjMatrix.size();
    }
   
}