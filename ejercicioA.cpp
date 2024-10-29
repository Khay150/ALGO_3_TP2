#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class DisjointSet {

    vector<int> rank, parent;

    public:

        DisjointSet(int n) {
            rank.resize(n + 1, 0);
            parent.resize(n + 1);
            for(int i = 0; i < n + 1; i++){
                parent[i] = i;
            }
        }
    
        int findSet(int node){
    
            // En caso que nodo sea el representante
            if (node == parent[node]) {

                return node;

            }

            // Hago path compression
            return parent[node] = findSet(parent[node]);
        }
    
        void unionByRank(int u, int v) {
            int uRep = findSet(u);
            int vRep = findSet(v);
    
            // Si tienen el mismo representante, entonces pertenece al
            // mismo conjunto
            if (uRep == vRep) return;
    
            // Actualizamos el representante segun el caso del rank
            if (rank[uRep] < rank[vRep]) {

                parent[uRep] = vRep;

            } 
            
            else if(rank[uRep] > rank[vRep]) {

                parent[vRep] = uRep;
            
            } 
            
            else {
                
                parent[vRep] = uRep;
                rank[uRep]++;
            
            }
        }
};

const int NO_LO_VI = 0;
const int EMPECE_A_VER = 1;
const int TERMINE_DE_VER = 2;

vector<int> estado;
vector<vector<int>> ady;
vector<vector<int>> tree_edges;
vector<int> padre;
vector<int> back_edges_con_extremo_superior_en;
vector<int> back_edges_con_extremo_inferior_en;
vector<int> memo;

void dfs(int v, int p = -1) {
    estado[v] = EMPECE_A_VER;
    for (int u : ady[v]) {
        if (estado[u] == NO_LO_VI) {
            tree_edges[v].push_back(u);
            padre[u] = v;
            dfs(u, v);
        } else if (u != padre[v]) {
            if (estado[u] == EMPECE_A_VER) {
                back_edges_con_extremo_superior_en[v]++;
            } else {
                back_edges_con_extremo_inferior_en[v]++;
            }
        }
    }
    estado[v] = TERMINE_DE_VER;
}

int cubren(int v, int p) {
    if (memo[v] != -1) return memo[v];
    int res = 0;
    for (int hijo : tree_edges[v]) {
        if (hijo != p) {
            res += cubren(hijo, v);
        }
    }
    res += back_edges_con_extremo_superior_en[v];
    res -= back_edges_con_extremo_inferior_en[v];
    memo[v] = res;
    return res;
}