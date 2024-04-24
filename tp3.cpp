/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique / TP3
 *
 *  Vos noms + codes permanents : BOUARGAN Zakariae BOUZ90340206
 *                                Bissonnette Vincent BISV28059906
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "carte.h"

using namespace std;

struct UnionFind {
    vector<int> parent, rang;
public:
    UnionFind(int size) : parent(size), rang(size, 0) {
        for(int i = 0; i < size; ++i) parent[i] = i;
    }

    int find(int x) {
        if(parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if(rootX != rootY) {
            if(rang[rootX] > rang[rootY]) parent[rootY] = rootX;
            else if(rang[rootX] < rang[rootY]) parent[rootX] = rootY;
            else {
                parent[rootY] = rootX;
                rang[rootX]++;
            }
        }
    }
};

void tp3(Carte& carte){
    vector<Arrete>& arretes = carte.getArretes();
    const vector<string>& sommets = carte.getSommets();
    int nbrSommet = sommets.size();
    UnionFind uf(nbrSommet);
    vector<Arrete> mst;
    int coutTotal = 0;
    std::sort(arretes.begin(), arretes.end());


    for(auto& arrete : arretes){
        int u = carte.getSommetIndex(arrete.debut);
        int v = carte.getSommetIndex(arrete.fin);
        if(uf.find(u) != uf.find(v)){
            uf.unionSets(u, v);
            mst.push_back(arrete);
            coutTotal += arrete.cout;
            if (mst.size() == static_cast<size_t>(nbrSommet - 1)) break;
        }
    }

    for(const Arrete& arrete : mst){
        cout << arrete.nom << " " << arrete.debut << " " << arrete.fin << " " << arrete.cout << endl;
    }
    cout << "---" << endl;
    cout << coutTotal << endl;
}


int main(int argc, const char** argv)
{
    if(argc != 2){
        cout << "Syntaxe: ./tp3 exemple.txt" << endl;
        return 1;
    }
    ifstream fichiercarte(argv[1]);
    if(!fichiercarte){
        cout << "Erreur ouverture du fichier : " << argv[1] << endl;
        return 1;
    }
    Carte carte;
    fichiercarte >> carte;
    fichiercarte.close();

    for(const auto& sommet : carte.getSommets()) {
        cout << sommet << endl;
    }
    tp3(carte);
    return 0;
}
