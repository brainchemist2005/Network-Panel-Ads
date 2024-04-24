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

void Carte::addSommet(const std::string& sommet) {
    if(sommetIndexMap.find(sommet) == sommetIndexMap.end()) {
        sommetIndexMap[sommet] = sommets.size();
        sommets.push_back(sommet);
    }
}

void Carte::addArrete(const std::string& nom, const std::string& debut, const std::string& fin, int cout) {
    arretes.push_back({nom, debut, fin, cout});
}

const std::vector<std::string>& Carte::getSommets() const {
    return sommets;
}

std::vector<Arrete>& Carte::getArretes()  {
    return arretes;
}

int Carte::getSommetIndex(const std::string& sommet) const {
    auto it = sommetIndexMap.find(sommet);
    if(it != sommetIndexMap.end()) {
        return it->second;
    }
    return -1;
}

std::istream& operator>>(std::istream& is, Carte& carte) {
    std::string ligne;
    bool lireSommets = true;
    int compteur = 0;

    while (std::getline(is, ligne)) {
        ligne.erase(ligne.begin(), std::find_if(ligne.begin(), ligne.end(), [](unsigned char c) { return !std::isspace(c); }));
        ligne.erase(std::find_if(ligne.rbegin(), ligne.rend(), [](unsigned char c) { return !std::isspace(c); }).base(), ligne.end());

        if (ligne.empty()) {
        }

        if (ligne == "---") {
            lireSommets = false;
            compteur++;
            continue;
        }

        if (lireSommets) {
            carte.addSommet(ligne);
        } else {
            std::istringstream iss(ligne);
            std::string nom, debut, fin;
            char deuxPoints;
            int cout;
            char pointVirgule;

            if (iss >> nom >> deuxPoints >> debut >> fin >> cout >> pointVirgule) {
                carte.addArrete(nom, debut, fin, cout);
            } else {
                std::cerr << "Erreur de lecture de l'arête: " << ligne << std::endl;
            }
        }
    }
    return is;
}


