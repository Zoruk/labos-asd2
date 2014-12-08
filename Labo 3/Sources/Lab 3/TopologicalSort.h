//
//  TopologicalSort.h
//  ASD2
//
//  Created by Olivier Cuisenaire on 08.10.14.
//
//  A implementer
//  Classe permettant le tri topologique d'un graphe oriente

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include "ParcoursEnProfondeur.h"
#include <vector>

namespace ASD2 {

    template < typename GraphType >
    class TopologicalSort {
    private:

        bool isDag;
        std::vector<int> postOrder;
        DirectedCycle<GraphType> dc;
    public:
        //constructeur
        TopologicalSort(const GraphType & g) : dc(g) {
            
            if (dc.HasCycle()) {
                isDag = false;
                return;
            } else {
                isDag = true;
            }
            postOrder.reserve(g.V());
            
            // postodrer = tris topologique
            // pas de reverse post order cat le graph generer dans Symbol graph
            // est deja dans l'ordre que l'on souhaite
            DFS<GraphType> dfs(g);
            dfs.visitAll([](int) { }, [this](int v) {
                postOrder.push_back(v);
            });
            
        }
        
        const DirectedCycle<GraphType>& getDC() {
            return dc;
        }

        //indique si le graphe est DAG (Directed Acyclic Graph))

        bool IsDAG() {
            return isDag;
        }

        //tableau contenant l'ordre de parcours des indexes des sommets dans le graphe

        const std::vector<int>& Order() {
            return postOrder;
        }
    };
}
#endif
