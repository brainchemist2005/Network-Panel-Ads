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
    vector<int> parent, rank;
public:
    UnionFind(int size) : parent(size), rank(size, 0) {
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
            if(rank[rootX] > rank[rootY]) parent[rootY] = rootX;
            else if(rank[rootX] < rank[rootY]) parent[rootX] = rootY;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

void tp3(Carte& carte){
    vector<Edge>& edges = carte.getEdges();
    const vector<string>& nodes = carte.getNodes();
    int nodeCount = nodes.size();
    UnionFind uf(nodeCount);
    vector<Edge> mst;
    int totalCost = 0;
    std::sort(edges.begin(), edges.end());


    for(auto& edge : edges){
        int u = carte.getNodeIndex(edge.start);
        int v = carte.getNodeIndex(edge.end);
        if(uf.find(u) != uf.find(v)){
            uf.unionSets(u, v);
            mst.push_back(edge);
            totalCost += edge.cost;
            if (mst.size() == static_cast<size_t>(nodeCount - 1)) break;
        }
    }

    for(const Edge& edge : mst){
        cout << edge.name << "\t" << edge.start << "\t" << edge.end << "\t" << edge.cost << endl;
    }
    cout << "---" << endl;
    cout << totalCost << endl;
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

    for(const auto& node : carte.getNodes()) {
        cout << node << endl;
    }
    tp3(carte);
    return 0;
}
