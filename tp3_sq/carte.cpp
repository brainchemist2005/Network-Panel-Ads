/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique / TP3
 *
 *  Vos noms + codes permanents : BOUARGAN Zakariae BOUZ90340206
 *                                Bissonnette Vincent BISV28059906
 */

#include <cstdio>
#include <limits>
#include <math.h>
#include <queue>
#include <sstream>
#include "carte.h"

Carte::Carte() {}

void Carte::addNode(const std::string& node) {
    if(nodeIndexMap.find(node) == nodeIndexMap.end()) {
        nodeIndexMap[node] = nodes.size();
        nodes.push_back(node);
    }
}

void Carte::addEdge(const std::string& name, const std::string& start, const std::string& end, int cost) {
    edges.push_back({name, start, end, cost});
}

const std::vector<std::string>& Carte::getNodes() const {
    return nodes;
}

 std::vector<Edge>& Carte::getEdges()  {
    return edges;
}

int Carte::getNodeIndex(const std::string& node) const {
    auto it = nodeIndexMap.find(node);
    if(it != nodeIndexMap.end()) {
        return it->second;
    }
    return -1;
}

std::istream& operator>>(std::istream& is, Carte& carte) {
    std::string line;
    bool readingNodes = true;
    while(std::getline(is, line)) {
        std::istringstream iss(line);
        if(line == "---") {
            readingNodes = false;
            continue;
        }
        if(readingNodes) {
            carte.addNode(line);
        } else {
            std::string name, colon, start, end, semicolon;
            int cost;
            if (getline(iss, name, ':') && iss >> start >> end >> cost && getline(iss, semicolon, ';')) {
                carte.addEdge(name, start, end, cost);
            }
        }
    }
    return is;
}


