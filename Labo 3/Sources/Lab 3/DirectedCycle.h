//
//  DirectedCycle.h
//  ASD2
//
//  Created by Olivier Cuisenaire on 08.10.14.
//  
//  A implementer
//  Classe permettant la detection de cycle sur un graphe oriente

#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

#include <vector>

namespace ASD2 {

    template<typename GraphType>
    class DirectedCycle {
    private:
        const GraphType& G;
        int cycle;

        std::vector<int> parents;
        std::vector<bool> marked;

        // Custom dfs pour la detection de cycle
        void dfs(int v, int parent) {
            marked[v] = true;
            
            // stoque le parent pour récuperer le cycle
            parents[v] = parent;
            for (int w : G.adjacent(v)) {
                if (!marked[w]) 
                    dfs(w, v); // Cherche les cycles par recursion
                // Si on a un parent pour ce noeud -> il y as un cycle
                // Vu qu'on garde uniquement les parent pour la recursion en cour
                else if (parents[w] != -1) {
                    cycle = v; // On garde le noeud avec le quel on a trouvé un cycle
                    parents[w] = cycle; // parents forme maintenant une boucle
                }
                
                // on a un cycle inutile de continuer
                if (cycle != -1) return;
            }
            
            // il n'y as pas de cycle avec ce noeud on le redéfini a -1
            parents[v] = -1;
        }
    
    public:
        //constructeur
        DirectedCycle(const GraphType& g) : G(g) {
            cycle = -1;
            parents.assign(G.V(), -1);
            marked.assign(G.V(), false);
            
            for (int i = 0; i < marked.size(); ++i) {
                if (!marked[i])
                    dfs(i, i);
                if (cycle != -1)
                    break;
            }
        }

        //indique la presence d'un cycle

        bool HasCycle() const {
            return cycle != -1;
        }

        //liste les indexes des sommets formant une boucle (dans l'ordre)
        std::list<int> Cycle() const {
            std::list<int> list;
            if (!HasCycle()) // Pas de cycle on retourne une liste vide
                return list;
            // On genere la liste du cycle dans l'ordre
            list.push_back(cycle);
            int v = parents[cycle];
            while (cycle != v) {
                list.push_back(v);
                v = parents[v];
            }
            list.reverse(); // Pas obligatoire mais plus joli selon moi 
            return list;
        }
    };
}

#endif
