//
//  main.cpp
//  Labo 3
//
//  Created by Olivier Cuisenaire on 03.11.14.
//

#include <iostream>
#include <stdlib.h>
#include <cassert>
#include "DiGraph.h"
#include "TopologicalSort.h"

// vous devez reutiliser celui du labo 2, ex 3 (cf. donnee)
#include "SymbolGraph.h"

using namespace ASD2;
using namespace std;

//methode permettant de verifier le graphe trie par rapport au fichier d'entree
bool checkOrder(const std::vector<int>& order,
                const SymbolGraph<DiGraph>& SG,
                const std::string& filename,
                char delim) {

    if (order.size() != SG.G().V()) {
        std::cout << "Order size different de GS size" << std::endl;
        return false;
    }
    std::vector<int> positionInOrder(order.size());
    for( size_t i = 0; i < order.size(); ++i )
        positionInOrder[order[i]] = int(i);
    
    bool ok = true;
    
    std::string line;
    
    std::ifstream s(filename);
    while (std::getline(s, line))
    {
        auto names = ASD2::split(line,delim);
        
        for(size_t i = 1; i < names.size(); ++i) {
         
            int v = SG.index(names[0]); // cours
            int w = SG.index(names[i]); // ieme prerequis
            
            if ( positionInOrder[ v ] < positionInOrder [ w ]) {
                cout << "Erreur d'ordre : " << names[0] << " avant " << names[i] << endl;
                ok = false;
            }
        }
    }
    s.close();
    
    return ok;
}

int main(int /*argc*/, const char ** /*argv*/) {

    const string FILE = "prerequis.txt"; // Fichier a charger
    SymbolGraph<DiGraph> graf(FILE); // Genere le SymbolGraph a partir du fichier
    
    // Trie le graph (si c'est possible)
    TopologicalSort<DiGraph> ts(graf.G());
    
    // Vérifie 
    const vector<int>& order = ts.Order();
    const bool ISCORRECTORDER = checkOrder(order, graf, FILE, ',');
    
    // Le graph est il un Directed Acyclic Graph
    // cout << "DAG : " << boolalpha << ISCORRECTORDER << endl;
    
    // si selon notre algo le graph doit être correct si on arrive ici et que c'est
    // un dag
    assert(ISCORRECTORDER == ts.IsDAG());
    
    // Si il est orgonnée et sans cycle
    if (ts.IsDAG()) {
        cout << FILE << " est un DAG" << endl << "Ordre topologique : " << endl;
        // Affichage dans l'ordre
        for (auto& v : order) {
            cout << graf.name(v) << "(" << v << ") ";
        }
    } else { // Si il y as un cycle.
        cout << FILE << " n'est pas un DAG" << endl;
        const DirectedCycle<DiGraph>& dc = ts.getDC(); // récupère le cycle
        // Affichage du cycle
        cout << "Cycle trouve : " << endl;
        for (int idx : dc.Cycle())
            cout << "    " << graf.name(idx) << " (" << idx << ")" << endl;
    }
    if (ISCORRECTORDER)
        cout << "\nVerification reussie" << endl;
    return EXIT_SUCCESS;
}
