//
//  main.cpp
//  Labo4
//
//  Created by Olivier Cuisenaire on 18.11.14.
//
//

#include <iostream>
#include <ctime>

#include "EdgeWeightedGraph.h"
#include "EdgeWeightedDigraph.h"
#include "RoadNetwork.h"
#include "MinimumSpanningTree.h"
#include "ShortestPath.h"
#include "RoadNetworkWrappers.h"

using namespace std;

// Calcule et affiche le plus court chemin de la ville depart a la ville arrivee
// en passant par le reseau routier rn. Le critere a optimiser est la distance.

void PlusCourtChemin(const string& depart, const string& arrivee, RoadNetwork& rn) {
    /* A IMPLEMENTER */
    RoadNetworkWrapperShortest wp(rn);
    ASD2::DijkstraSP<RoadNetworkWrapperShortest> sp(wp, rn.cityIdx[depart]);
    double dist = 0;
    for (auto& a : sp.PathTo(rn.cityIdx[arrivee])) {
        cout << rn.cities[a.From()].name << "->" << rn.cities[a.To()].name <<
                " " << a.Weight() << "km" << endl;
        dist += a.Weight();
    }
    cout << "Distance totale : " << dist << "km" << endl;
}

// Calcule et affiche le plus rapide chemin de la ville depart a la ville arrivee via la ville "via"
// en passant par le reseau routier rn. Le critere a optimiser est le temps de parcours
// sachant que l'on roule a 120km/h sur autoroute et 70km/h sur route normale.

void PlusRapideChemin(const string& depart, const string& arrivee, const string& via, RoadNetwork& rn) {
    /* A IMPLEMENTER */
    RoadNetworkWrapperFastest wp(rn);
    ASD2::DijkstraSP<RoadNetworkWrapperFastest> sp1(wp, rn.cityIdx[depart]);
    ASD2::DijkstraSP<RoadNetworkWrapperFastest> sp2(wp, rn.cityIdx[via]);
    
    auto path = sp1.PathTo(rn.cityIdx[via]);
    auto tmp = sp2.PathTo(rn.cityIdx[arrivee]);
    
    path.reserve(path.size() + tmp.size());
    path.insert(path.end(), tmp.begin(), tmp.end());
    double temps = 0;
    for (auto& a : path) {
        cout << rn.cities[a.From()].name << "->" << rn.cities[a.To()].name 
                << " (" << a.Weight() * 60 << "min)" << endl;
        temps += a.Weight();
    }
    cout << "Temps total : " << temps * 60 << "min" << endl;
}

// Calcule et affiche le plus reseau a renover couvrant toutes les villes le moins
// cher, en sachant que renover 1km d'autoroute coute 15 MF, et renover 1km de route normale
// coute 7 MF.

void ReseauLeMoinsCher(RoadNetwork &rn) {
    /* A IMPLEMENTER */
    RoadNetworkWrapperCheap wp(rn);
    auto edges = ASD2::MinimumSpanningTree<RoadNetworkWrapperCheap>::Kruskal(wp);
    double sum = 0;
    for (const auto& edge : edges) {
        int e = edge.Either();
        int o = edge.Other(e);
        cout << rn.cities[e].name << "<->" << rn.cities[o].name << endl;
        sum += edge.Weight();
    }
    cout << "Prix total : " << sum << "M" << endl;
}

// compare les algorithmes Dijkstra et BellmanFord pour calculer les plus courts chemins au
// sommet 0 dans le graphe defini par filename.

void testShortestPath(string filename)
{
    cout << "Testing " << filename << endl;
    
    bool ok = true;
    
    typedef ASD2::EdgeWeightedDiGraph<double> Graph;
    Graph ewd(filename);
    
    clock_t startTime = clock();

    ASD2::BellmanFordQueueSP<Graph> referenceSP(ewd,0);
    
    cout << "Bellman-Ford: " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
    startTime = clock();

    ASD2::DijkstraSP<Graph> testSP(ewd,0);
    
    cout << "Dijkstra:     " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;

    for (int v=0; v<ewd.V(); ++v) {
        if (referenceSP.DistanceTo(v) != testSP.DistanceTo(v) ) {
            cout << "Oops: vertex" << v << " has " << referenceSP.DistanceTo(v) << " != " <<  testSP.DistanceTo(v) << endl;
            ok = false;
            break;
        }
    }
    
    if(ok) cout << " ... test succeeded " << endl << endl;
}

int main(int argc, const char * argv[]) {
    
    //*
    testShortestPath("tinyEWD.txt");
    testShortestPath("mediumEWD.txt");
    testShortestPath("1000EWD.txt");
    testShortestPath("10000EWD.txt");
    testShortestPath("largeEWD.txt"); // disponible sur dossier du cours
    //*/
    RoadNetwork rn("reseau.txt");
    
    //cout << rn << endl;
    cout << "1. Chemin le plus court entre Geneve et Emmen" << endl;
    
    PlusCourtChemin("Geneve", "Emmen", rn);
    
    cout << "2. Chemin le plus court entre Lausanne et Bale" << endl;
    
    PlusCourtChemin("Lausanne", "Basel", rn);
  
    cout << "3. chemin le plus rapide entre Geneve et Emmen en passant par Yverdon" << endl;
    
    PlusRapideChemin("Geneve", "Emmen", "Yverdon-Les-Bains", rn);
    
    cout << "4. chemin le plus rapide entre Geneve et Emmen en passant par Vevey" << endl;
    
    PlusRapideChemin("Geneve", "Emmen", "Vevey", rn);

    cout << "5. Quelles routes doivent etre renovees ? Quel sera le cout de la renovation de ces routes ?" << endl;
    
    ReseauLeMoinsCher(rn);
    
    return 0;
}
