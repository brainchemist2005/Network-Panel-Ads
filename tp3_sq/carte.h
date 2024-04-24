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
#include <algorithm>

struct Arrete {
    std::string nom, debut, fin;
    int cout;
    bool operator<(const Arrete& other) const {
        if(cout != other.cout) return cout < other.cout;
        if(debut != other.debut) return debut < other.debut;
        return fin < other.fin;
    }
};

class Carte {
private:
    std::vector<std::string> sommets;
    std::vector<Arrete> arretes;
    std::map<std::string, int> sommetIndexMap;

public:
    Carte();
    void addSommet(const std::string& sommet);
    void addArrete(const std::string& nom, const std::string& debut, const std::string& fin, int cout);
    const std::vector<std::string>& getSommets() const;
    std::vector<Arrete>& getArretes() ;
    int getSommetIndex(const std::string& sommet) const;
    friend std::istream& operator>>(std::istream& is, Carte& carte);
};

#endif
