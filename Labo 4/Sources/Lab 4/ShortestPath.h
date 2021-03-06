//
//  ShortestPath.h
//  ASD2
//
//  Created by Olivier Cuisenaire on 05.11.14.
//
//

#ifndef ASD2_ShortestPath_h
#define ASD2_ShortestPath_h

#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <functional>

#include "PriorityQueue.h"

namespace ASD2 {
    
    // Classe parente de toutes les classes de plus court chemin.
    // Defini les membres edgeTo et distanceTo commun à toutes ces
    // classes, ainsi que les methodes DistanceTo, EdgeTo et PathTo
    // qui permettent de les interroger.
    //
    // Le calcul des plus courts chemins est fait dans les constructeurs
    // des classes derivees.
    
    template<typename GraphType>   // Type du graphe pondere oriente a traiter
                                   // GraphType doit se comporter comme un
                                   // EdgeWeightedDiGraph et definir le
                                   // type GraphType::Edge
    class ShortestPath {
    public:
        // Type des arcs. Normalement ASD2::DirectedEdge<double>
        typedef typename GraphType::Edge Edge;
        
        // Type des poids. Normalement double ou int.
        typedef typename Edge::WeightType Weight;
    
        // Listes d'arcs et de poids
        typedef std::vector<Edge> Edges;
        typedef std::vector<Weight> Weights;
 
        // Renvoie la distance du chemin le plus court du sommet source a v
        Weight DistanceTo(int v) {
            return distanceTo.at(v);
        }
        
        // Renvoie le dernier arc u->v du chemin le plus court du sommet source a v
        Edge EdgeTo(int v) {
            return edgeTo.at(v);
        }
        
        // Renvoie la liste ordonnee des arcs constituant un chemin le plus court du
        // sommet source à v.
        Edges PathTo(int v) {
            // Genere un vacteur des edges pour acceder au sommet v
            Edges es;
            if (distanceTo[v] == std::numeric_limits<Weight>::max()) {
                //std::cout << "No path to " << v << std::endl;
                return es; // no path
            }
            while (distanceTo[v] != 0) {
                es.push_back(edgeTo[v]);
                v = edgeTo[v].From();
            }
            // Les sommet sont dans l'ordre inverse
            std::reverse(es.begin(), es.end());
            return es;
        }

    protected:
        Edges edgeTo;
        Weights distanceTo;
    };

    // Classe a mettre en oeuvre au labo 4. S'inspirer de BellmaFordSP pour l'API
    template<typename GraphType>
    class DijkstraSP : public ShortestPath<GraphType> {
    public:
        typedef ShortestPath<GraphType> BASE;
        typedef typename BASE::Edge Edge;
        typedef typename BASE::Weight Weight;

        // La queue de priorite avec degreaseKey
        PriorityQueue<Weight> queue;
        DijkstraSP(const GraphType& g, int v) : queue(g.V(), std::numeric_limits<Weight>::max())  {
            // Prépare les vecteur edgeTo et distanceTo
            this->edgeTo.reserve(g.V());
            this->distanceTo.assign(g.V(), std::numeric_limits<Weight>::max());
        
            // Initialise la distance et l'edge pour le acceder de debut->debut
            this->edgeTo[v] = Edge(v,v,0);
            this->distanceTo[v] = 0;
            
            // Pas nessaire la pq est initialisée dans le constructeur 
            // (serrais utile si l on utilise l autre constructeur)
            /*
            g.forEachVertex([this](const int e) {
                queue.insert(e, std::numeric_limits<Weight>::max());
            });
            */
       
            // pour acceder a lui meme la distance est de 0
            queue.decreaseKey(v, 0);

            // Tant qu'il reste des edge a traiter on relax tout les edge adjacent
            // au sommet le plus proche
            while (!queue.isEmpty()) {
                int v = queue.pop().data;

                g.forEachAdjacentEdge(v, [this](const Edge& e) {
                    relax(e);
                });
            }
        }

    private:
        void relax(const Edge& e) {
            // Le relay est identique a celui de BellmanFord on ajoute juste le
            // decreaseKey de la pq
            int v = e.From(), w = e.To();
            Weight distThruE = this->distanceTo[v] + e.Weight();

            if(this->distanceTo[w] > distThruE) {
                this->distanceTo[w] = distThruE;
                this->edgeTo[w] = e;
                queue.decreaseKey(w, distThruE);
            }
        }
    };

    // Algorithme de BellmanFord.
    template<typename GraphType> // Type du graphe pondere oriente a traiter
                                 // GraphType doit se comporter comme un
                                 // EdgeWeightedDiGraph et definir forEachEdge(Func),
                                 // ainsi que le type GraphType::Edge. Ce dernier doit
                                 // se comporter comme ASD2::DirectedEdge, c-a-dire definir From(),
                                 // To() et Weight()

    class BellmanFordSP : public ShortestPath<GraphType> {

    private:
        typedef ShortestPath<GraphType> BASE;
        typedef typename BASE::Edge Edge;
        typedef typename BASE::Weight Weight;

        // Relachement de l'arc e
        void relax(const Edge& e) {
            int v = e.From(), w = e.To();
            Weight distThruE = this->distanceTo[v]+e.Weight();
            
            if(this->distanceTo[w] > distThruE) {
                this->distanceTo[w] = distThruE;
                this->edgeTo[w] = e;
            }
        }
        
    public:
        
        // Constructeur a partir du graphe g et du sommet v a la source
        // des plus courts chemins
        BellmanFordSP(const GraphType& g, int v) {
            
            this->edgeTo.reserve(g.V());
            this->distanceTo.assign(g.V(),std::numeric_limits<Weight>::max());
 
            this->edgeTo[v] = Edge(v,v,0);
            this->distanceTo[v] = 0;
            
            for(int i=0;i<g.V();++i)
                g.forEachEdge([this](const Edge& e){
                    this->relax(e);
                });
        }
    };
    
    

    // Algorithme de BellmanFord avec queue simple reprenant les sommets ayant
    // ete modifies par la derniere iteration.
    
    template<typename GraphType> // Type du graphe pondere oriente a traiter
                                 // GraphType doit se comporter comme un
                                 // EdgeWeightedDiGraph et definir forEachAdjacentEdge(int,Func),
                                 // ainsi que le type GraphType::Edge. Ce dernier doit
                                 // se comporter comme ASD2::DirectedEdge, c-a-dire definir From(),
                                 // To() et Weight()

    class BellmanFordQueueSP : public ShortestPath<GraphType> {
    
    private:
        typedef ShortestPath<GraphType> BASE;
        typedef typename BASE::Edge Edge;
        typedef typename BASE::Weight Weight;
        
        std::queue<int> queue;
        std::vector<int> inQueue;
        
        void relax(const Edge& e) {
            int v = e.From(), w = e.To();
            Weight distThruE = this->distanceTo[v]+e.Weight();
            if(this->distanceTo[w] > distThruE) {
                this->distanceTo[w] = distThruE;
                this->edgeTo[w] = e;
                
                if (!inQueue[w]) {
                    inQueue[w] = true;
                    queue.push(w);
                }
            }
        }
        
    public:
        BellmanFordQueueSP(const GraphType& g, int v) {
            
            inQueue.assign(g.V(), false);
            
            this->edgeTo.reserve(g.V());
            this->distanceTo.assign(g.V(),std::numeric_limits<Weight>::max());
            
            this->edgeTo[v] = Edge(v,v,0);
            this->distanceTo[v] = 0;
            queue.push(v);
            inQueue[v] = true;
            
            while (!queue.empty()) {
                int v = queue.front();
                inQueue[v] = false;
                queue.pop();
                
                g.forEachAdjacentEdge(v, [&](const Edge& e) {
                    this->relax(e);
                });
            }
        }
    };
}


#endif
