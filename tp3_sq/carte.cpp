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
    int compteur = 0;

    while (std::getline(is, line)) {
        // Supprimer les espaces avant et après la ligne
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char c) { return !std::isspace(c); }));
        line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char c) { return !std::isspace(c); }).base(), line.end());

        if (line.empty()) {
            continue; // Ignorer les lignes vides
        }

        if (line == "---") {
            // Basculer entre les modes de lecture
            readingNodes = false;
            compteur++;
            continue;
        }

        if (readingNodes) {
            // Ajouter le nœud à la carte
            carte.addNode(line);
        } else {
            // Lire une arête à partir de la ligne
            std::istringstream iss(line);
            std::string name, start, end;
            char colon;
            int cost;
            char semicolon;

            if (iss >> name >> colon >> start >> end >> cost >> semicolon) {
                // Ajouter l'arête à la carte
                carte.addEdge(name, start, end, cost);
            } else {
                std::cerr << "Erreur de lecture de l'arête: " << line << std::endl;
            }
        }
    }

    return is;
}


