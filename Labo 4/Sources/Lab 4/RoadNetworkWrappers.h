/* 
 * File:   RoadNetworkWrappers.h
 * Author: zoruk
 *
 * Created on 28. novembre 2014, 20:40
 */

#ifndef ROADNETWORKWRAPPERS_H
#define	ROADNETWORKWRAPPERS_H
#include "RoadNetwork.h"
#include "EdgeWeightedDigraph.h"
#include "EdgeWeightedGraph.h"

// Tout les wrapper de RoadNetwork herite de cette class
class RoadNetworkWrapperBase {
protected:
    const RoadNetwork& network;
    RoadNetworkWrapperBase(const RoadNetwork& network) : network(network) {}
public:
    std::size_t V() const {
        return network.cities.size();
    }
};

// tout les wrapper de graph orienté herite de cette class
class RoadNetworkDigraphWrapper : public RoadNetworkWrapperBase {
protected:
    RoadNetworkDigraphWrapper(const RoadNetwork& network) : 
        RoadNetworkWrapperBase(network) {}

public:
    // Type de Edge (oriente)
    typedef typename ASD2::WeightedDirectedEdge<double> Edge;
    
    // Le poids doit être implementé par les class enfants
    virtual double getWeight(const RoadNetwork::Road& road) const = 0;

    template<typename Func>
    void forEachEdge(Func f) const {
        for (const RoadNetwork::Road& road : network.roads) {
            double w = getWeight(road);
            
            // Une route ca dans les deux sens (dans notre cas mais dans le cas general
            // il est possible qu'il y ai des sens unique)
            Edge a(road.cities.first , road.cities.second, w);
            Edge b(road.cities.second, road.cities.first,  w);
            f(a);
            f(b);
        }
    }

    template<typename Func>
    void forEachAdjacentEdge(int ville, Func f) const {
        // Les Edge adjassent sont les routes qui partes de la ville
        for (int roadid : network.cities.at(ville).roads) {
            const RoadNetwork::Road& road = network.roads[roadid];
            int from, to;
           
            if (road.cities.first == ville) {
                from = road.cities.first;
                to = road.cities.second;
            } else {
                from = road.cities.second;
                to = road.cities.first;
            }

            Edge e(from, to, getWeight(road));
            f(e);
        }
    }
    
    template<typename Func>
    void forEachVertex(Func f) const {
        for (std::size_t i = 0; i < V(); ++i) {
            f(i);
        }
    }
};

// Les Wrapper de graph non oriente herittent de cette class
class RoadNetworGraphkWrapper : public RoadNetworkWrapperBase {
protected :
    RoadNetworGraphkWrapper(const RoadNetwork& network) : 
        RoadNetworkWrapperBase(network) {}
public:
    // type de Edge (non oriente)
    typedef typename ASD2::WeightedEdge<double> Edge;
    
    // le poid des egres doit etre calculé par les classs enfants
    virtual double getWeight(const RoadNetwork::Road& road) const = 0;

    template<typename Func>
    void forEachEdge(Func f) const {
        for (const RoadNetwork::Road& road : network.roads) {
            double w = getWeight(road);
            f(Edge(road.cities.first , road.cities.second, w));
        }
    }

    template<typename Func>
    void forEachAdjacentEdge(int ville, Func f) const {
        for (int roadid : network.cities.at(ville).roads) {
            const RoadNetwork::Road& road = network.roads[roadid];
            f(Edge(road.cities.first, road.cities.second, getWeight(road)));
        }
    }
    
    template<typename Func>
    void forEachVertex(Func f) const {
        for (std::size_t i = 0; i < V(); ++i) {
            f(i);
        }
    }
};

/*
 * Class wrapper de RoadNetwork les Weight sera le prix de rénovation de la route
 */
class RoadNetworkWrapperPrice : public RoadNetworGraphkWrapper {
public:
     // Prix par km pour renover une autoroute en M
    const double MOTORWAY_PRICE = 15.;
    
    // Prix par mk pour renover une route normal en M
    const double NORMALWAY_PRICE = 7.;
    
    RoadNetworkWrapperPrice(const RoadNetwork& n) : RoadNetworGraphkWrapper(n) { }
    
    double getWeight(const RoadNetwork::Road& road) const override {
        // Proportion d'autoroute
        double mororway = road.motorway.Value(); 
        // Prix de renovation de la partie autoroute
        double motorWayPrice = (mororway * road.lenght) * MOTORWAY_PRICE;
        // Prix de renovation de la partie route normal
        double normalWayPrice = ((1 - mororway) * road.lenght) * NORMALWAY_PRICE;
        // Retoure le prix total
        return motorWayPrice + normalWayPrice;
    }
};

/*
 * Wrapper qui a comme poid la longeur de la route
 */
class RoadNetworkWrapperLength : public RoadNetworkDigraphWrapper {
public:
    RoadNetworkWrapperLength(const RoadNetwork& n) : RoadNetworkDigraphWrapper(n) { }
    
    double getWeight(const RoadNetwork::Road& road) const override {
        return road.lenght;
    }
};

/*
 * Wrapper qui a comme poid le temps de trajet
 */
class RoadNetworkWrapperTime : public RoadNetworkDigraphWrapper {
public:
    RoadNetworkWrapperTime(const RoadNetwork& n) : RoadNetworkDigraphWrapper(n) { }
    
    // Vitesse sur les autoroutes
    const double MOTORWAY_SPEED = 120.;
    // Vitesse sur les routes normal
    const double NORMALWAY_SPEED = 70.;
    double getWeight(const RoadNetwork::Road& road) const override {
        // Proportion d autoroute
        double mororway = road.motorway.Value();
        // Temps passe sur les autoroute en H
        double motorWaytime = (mororway * road.lenght) / MOTORWAY_SPEED;
        // temps passe sur les route normal en H
        double normalWaytime = ((1 - mororway) * road.lenght) / NORMALWAY_SPEED;
        return motorWaytime + normalWaytime;
    }
}; 
#endif	/* ROADNETWORKWRAPPERS_H */

