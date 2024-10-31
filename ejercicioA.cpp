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

void dfs(int v, int p = -1, const vector<vector<int>>& ady_temporal) {
    estado[v] = EMPECE_A_VER;
    for (int u : ady[v]) {
        if (u == p) continue; 
        if (estado[u] == NO_LO_VI) {
            tree_edges[v].push_back(u);
            padre[u] = v;
            dfs(u, v, ady_temporal);
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
    // Contar la cantidad de hijos de v
    int hijos_count = 0;
    for (int hijo : tree_edges[v]) {
        if (hijo != p) {
            res += cubren(hijo, v);
            hijos_count++; // Contar los hijos
        }
    }
    res += back_edges_con_extremo_superior_en[v];
    res -= (back_edges_con_extremo_inferior_en[v] - hijos_count );
    memo[v] = res;
    return res;
}


void Kruskal_Mod( int n, int m, vector<tuple<int, int, int>>& aristas, vector<int>& indices, vector<string>& res, vector<vector<int>>& adj)  {

    DisjointSet dsu(n);

    //ordenar las aristas por peso
    sort(indices.begin(), indices.end(), [&](int index1, int index2) {

        return get<0>(aristas[index1]) < get<0>(aristas[index2]);

    });
     // Procesamos las aristas por grupos de peso
    for (int i = 0; i < m;) {

        int peso_actual = get<0>(aristas[indices[i]]);

        vector<int> grupo_actual;

        while (i < m && (get<0>(aristas[indices[i]]) == peso_actual))
        {
            grupo_actual.push_back(indices[i]);
            i++;
        }


        // Crear una copia del DSU
        DisjointSet dsu_temporal = dsu;

        if (grupo_actual.size() == 1) {

            int index = grupo_actual[0];

            int u = get<1>(aristas[index]);
            int v = get<2>(aristas[index]);

            if (dsu_temporal.findSet(u) != dsu_temporal.findSet(v)) {

                res[index] = "any";

                dsu.unionByRank(u, v);

            } else {

                res[index] = "none";

            }
        }
        else { //Tengo problemas de memoria en esta parte de Kruskal

            vector<vector<int>> ady_temporal(n + 1);

            for (int index : grupo_actual) {

                int u = get<1>(aristas[index]);
                int v = get<2>(aristas[index]);

                if (dsu_temporal.findSet(u) != dsu_temporal.findSet(v)) {

                    ady_temporal[u].push_back(v);
                    ady_temporal[v].push_back(u);

                }

            }
            // Actualizamos el DSU principal con las aristas que no generaron ciclos
            for (int index : grupo_actual) {

                int u = get<1>(aristas[index]);
                int v = get<2>(aristas[index]);

                if (dsu_temporal.findSet(u) != dsu_temporal.findSet(v)) {
                    dsu_temporal.unionByRank(u, v);

                    estado.assign(n + 1, NO_LO_VI);
                    back_edges_con_extremo_superior_en.assign(n + 1, 0);
                    back_edges_con_extremo_inferior_en.assign(n + 1, 0);
                    memo.assign(n + 1, -1);
                    tree_edges.assign(n + 1, vector<int>());
                    padre.assign(n + 1, -1);

                    dfs(u, -1, ady_temporal);

                    if (cubren(u, -1) == 0) {
                        res[index] = "any";
                    } else {
                        res[index] = "at least one";
                    }
                } else {
                    res[index] = "none";
                }
            }

            for (int index : grupo_actual) {
                int u = get<1>(aristas[index]);
                int v = get<2>(aristas[index]);

                if (dsu_temporal.findSet(u) != dsu_temporal.findSet(v)) {
                    dsu.unionByRank(u, v);
                }
            }
        }
    }
}

int main() {

    int n, m;
    cout << ":";
    cin >> n >> m;

    vector<tuple<int, int, int>> aristas(m);
    vector<int> indices(m);
    vector<string> res(m);
    vector<vector<int>> ady(n+1);

    estado.assign(n + 1, NO_LO_VI); 
    back_edges_con_extremo_superior_en.assign(n + 1, 0); 
    back_edges_con_extremo_inferior_en.assign(n + 1, 0); 
    memo.assign(n + 1, -1); 
    tree_edges.assign(n + 1, vector<int>()); 
    padre.assign(n + 1, -1);

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cout << ":";
        cin >> a >> b >> w;
        aristas[i] = make_tuple(w, a, b);
        indices[i] = i;
        ady[a].push_back(b);
        ady[b].push_back(a);
    }

    Kruskal_Mod(n, m, aristas, indices, res, ady);

    for(int i = 0; i < m; i++) {
         cout << res[i] << endl;
    }
    
    return 0;
}
