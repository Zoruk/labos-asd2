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

class RoadNetworkWrapperBase {
protected:
    const RoadNetwork& network;
    RoadNetworkWrapperBase(const RoadNetwork& network) : network(network) {}
public:
    std::size_t V() const {
        return network.cities.size();
    }
};

class RoadNetworkDigraphWrapper : public RoadNetworkWrapperBase {
protected:
    RoadNetworkDigraphWrapper(const RoadNetwork& network) : 
        RoadNetworkWrapperBase(network) {}

public:
    //typedef double Weight;Weight
    typedef typename ASD2::WeightedDirectedEdge<double> Edge;
    
    virtual double getWeight(const RoadNetwork::Road& road) const = 0;

    template<typename Func>
    void forEachEdge(Func f) const {
        for (const RoadNetwork::Road& road : network.roads) {
            double w = getWeight(road);
            Edge a(road.cities.first , road.cities.second, w);
            Edge b(road.cities.second, road.cities.first,  w);
            f(a);
            f(b);
        }
    }

    template<typename Func>
    void forEachAdjacentEdge(int ville, Func f) const {
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

class RoadNetworGraphkWrapper : public RoadNetworkWrapperBase {
protected :
    RoadNetworGraphkWrapper(const RoadNetwork& network) : 
        RoadNetworkWrapperBase(network) {}
public:
    //typedef double Weight;Weight
    typedef typename ASD2::WeightedEdge<double> Edge;
    
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

class RoadNetworkWrapperCheap : public RoadNetworGraphkWrapper {
public:
    const double MOTORWAY_PRICE = 15.;
    const double NORMALWAY_PRICE = 7.;
    
    RoadNetworkWrapperCheap(const RoadNetwork& n) : RoadNetworGraphkWrapper(n) { }
    
    double getWeight(const RoadNetwork::Road& road) const override {
        double mororway = road.motorway.Value();
        double motorWayPrice = (mororway * road.lenght) * MOTORWAY_PRICE;
        double normalWayPrice = ((1 - mororway) * road.lenght) * NORMALWAY_PRICE;
        return motorWayPrice + normalWayPrice;
    }
};

class RoadNetworkWrapperShortest : public RoadNetworkDigraphWrapper {
public:
    RoadNetworkWrapperShortest(const RoadNetwork& n) : RoadNetworkDigraphWrapper(n) { }
    
    double getWeight(const RoadNetwork::Road& road) const override {
        //std::cout << "getWeight" << road.lenght << std::endl;
        return road.lenght;
    }
};

class RoadNetworkWrapperFastest : public RoadNetworkDigraphWrapper {
public:
    RoadNetworkWrapperFastest(const RoadNetwork& n) : RoadNetworkDigraphWrapper(n) { }
    
    const double MOTORWAY_SPEED = 120.;
    const double NORMALWAY_SPEED = 70.;
    double getWeight(const RoadNetwork::Road& road) const override {
        double mororway = road.motorway.Value();
        double motorWaytime = (mororway * road.lenght) / MOTORWAY_SPEED;
        double normalWaytime = ((1 - mororway) * road.lenght) / NORMALWAY_SPEED;
        return motorWaytime + normalWaytime;
    }
}; 
#endif	/* ROADNETWORKWRAPPERS_H */

