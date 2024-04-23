/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique / TP3
 *
 *  Vos noms + codes permanents : BOUARGAN Zakariae BOUZ90340206
 *                                Bissonnette Vincent BISV28059906
 */

#ifndef CARTE_H
#define CARTE_H

#include <vector>
#include <string>
#include <iostream>
#include <map>

struct Edge {
    std::string name, start, end;
    int cost;
    bool operator<(const Edge& other) const {
        if(cost != other.cost) return cost < other.cost;
        if(start != other.start) return start < other.start;
        return end < other.end;
    }
};

class Carte {
private:
    std::vector<std::string> nodes;
    std::vector<Edge> edges;
    std::map<std::string, int> nodeIndexMap;

public:
    Carte();
    void addNode(const std::string& node);
    void addEdge(const std::string& name, const std::string& start, const std::string& end, int cost);
    const std::vector<std::string>& getNodes() const;
    std::vector<Edge>& getEdges() ;
    int getNodeIndex(const std::string& node) const;
    friend std::istream& operator>>(std::istream& is, Carte& carte);
};

#endif
