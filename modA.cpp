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


void Kruskal_Mod( long long n, long long m, vector<tuple<long long, long long, long long>>& aristas, vector<long long>& indices, vector<string>& res) {


    DisjointSet dsu(n);

    //ordenar las aristas por peso
    sort(indices.begin(), indices.end(), [&](long long index1, long long index2) {

        return get<0>(aristas[index1]) < get<0>(aristas[index2]);

    });

 
    // Procesamos las aristas por grupos de peso

    for (long long i = 0; i < m;) {

        long long peso_actual = get<0>(aristas[indices[i]]);

        vector<long long> grupo_actual;

        while (i < m && (get<0>(aristas[indices[i]]) == peso_actual))
        {
            grupo_actual.push_back(indices[i]);
            i++;
        }

        // Crear una copia del DSU
        DisjointSet dsu_temporal = dsu;



        for (long long index : grupo_actual) {

            long long u = get<1>(aristas[index]);
            long long v = get<2>(aristas[index]);

            if (dsu_temporal.findSet(u) != dsu_temporal.findSet(v)) {

                res[index] = "at least one";

            } else {

                res[index] = "none";

            }
        }

        map<long long, long long> componentSize;
        for (long long j : grupo_actual) {
            long long u = get<1>(aristas[j]);
            long long v = get<2>(aristas[j]);
            componentSize[dsu.findSet(u)]++;
            componentSize[dsu.findSet(v)]++;
        }

        for (long long j : grupo_actual) {
            long long u = get<1>(aristas[j]);
            long long v = get<2>(aristas[j]);
            if (componentSize[dsu.findSet(u)] == 1 || componentSize[dsu.findSet(v)] == 1) {
                res[j] = "any";
            }
            dsu.unionByRank(u, v);
        }
    }

}


int main() {

    long long n, m;
    cout << ":";
    cin >> n >> m;

    vector<tuple<long long, long long, long long>> aristas(m);

    vector<long long> indices(m);

    for (long long i = 0; i < m; i++) {
        long long a, b, w;
        cout << ":";
        cin >> a >> b >> w;
        aristas[i] = make_tuple(w, a, b);
        indices[i] = i;
    }

    vector<string> res(m);
    
    Kruskal_Mod(n, m, aristas, indices, res);

    for (long long i = 0; i < m; i++) {

        cout << res[i] << endl;
    
    }

    return 0;
}
