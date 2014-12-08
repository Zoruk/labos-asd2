/* 
 * File:   SymbolGraph.h
 * Author: Olivier Cuisenaire
 *
 * Created on 26. septembre 2014, 15:08
 */

#ifndef SYMBOLGRAPH_H
#define	SYMBOLGRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include "Util.h"

namespace ASD2 {

    template<typename GraphType>
    class SymbolGraph {
        typedef GraphType Graph;
    private:
        Graph* g;

        // deux conteneurs pour les performances consomment plus de memoire mais les
        // fonctions de recherche en fonction de la clé string ou de la clé int
        // sont les deux d'ordre 1 contre ordre n * (longeur moyenne de string)
        // pour une recherche de string dans un vecteur.
        // unordered_map pour rechercher avec la clé string
        // vector pour rechercher avec l'id
        std::unordered_map<std::string, int> vertices_map;
        std::vector<std::string> vertices_vector;
    public:

        ~SymbolGraph() {
            delete g;
        }

        // creation du SymbolGraph a partir du fichier movies.txt

        SymbolGraph(const std::string& filename) {
            // lecture du fichier, ligne par ligne puis element par element (separe par des /)
            std::string line;

            // Set n'accepte pas les doublons il est donc simple a remplire avec
            // un seul exemplaire de chaques acteur ou filme.
            std::unordered_set<std::string> verticies;

            // on stock chaques lignes pour construire les liens une fois qu'on 
            // connaitra tous les noeuds
            std::set<std::vector < std::string>> lignes;
            std::ifstream s(filename);

            // On pourrait remplir directement les conteneurs internes de la class
            // dans la boucle ce qui reduirait la memoire utilisee
            // mais pour des raisons de simplicite du code et de lisibilite
            // nous preferons faire en deux étapes
            while (std::getline(s, line)) {
                auto names = ASD2::split(line, ',');
                lignes.insert(names);
                for (auto name : names)
                    verticies.insert(name);
            }
            s.close();

            int cnt = 0;
            // Remplit le vecteur et la hash map
            vertices_vector.reserve(verticies.size());
            for (auto& v : verticies) {
                vertices_map[v] = cnt++;
                vertices_vector.push_back(v);
            }

            // genere le graph avec ses liens.
            g = new Graph(verticies.size());
            int superId;
            for (auto names : lignes) {
                superId = -1;
                for (auto _name : names) {
                    if (superId == -1) {
                        superId = index(_name);
                    } else {
                        //std::cout << name(superId).c_str() << " " << _name << std::endl;
                        g->addEdge(superId, index(_name));
                    }
                }
            }
        }

        //verifie la presence d'un symbole

        bool contains(const std::string& name) const {
            return vertices_map.find(name) != vertices_map.end();
        }

        //index du sommet correspondant au symbole

        int index(const std::string& name) const {
            return vertices_map.at(name);
        }

        //symbole correspondant au sommet
        // throw std::out_of_range

        std::string name(int idx) const {
            return vertices_vector.at(idx);
        }

        //symboles adjacents a un symbole

        std::vector<std::string> adjacent(const std::string & name) {
            std::vector<std::string> list;
            int id = index(name);
            for (int v : g->adjacent(id)) {
                list.push_back(this->name(v));
            }
            return list;
        }

        const Graph& G() const {
            return *g;
        }
    };
}

#endif	/* SYMBOLGRAPH_H */
