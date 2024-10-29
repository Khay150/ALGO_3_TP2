#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAXN 100000 // Cantidad maxima de Nodos

vector<int> aristas[MAXN+1]; // Lista de adyacencias para las aristas del árbol

int distancia[MAXN+1];         // Para mantener la distancia desde el nodo inicial

// Función que chequea si una componente es bipartita, usando BFS

bool esComponenteBipartita(int n, int inicio) {
    queue<int> q;
    distancia[inicio] = 0;  // Distancia inicial
    q.push(inicio);

    while (!q.empty()) {
        int vertice = q.front();
        q.pop();
        for(int vecino : aristas[vertice]) {

            // Si no hemos visitado el nodo, lo visitamos y asignamos su distancia
            if (distancia[vecino] == -1) {
                distancia[vecino] = distancia[vertice] +1;
                q.push(vecino);
            }

            // No es bipartito si los vecinos tienen la misma paridad en sus distancia
            else if ((distancia[vecino] - distancia[vertice]) % 2 == 0)
            {
                return false;
            }
            

        }
    }
    
    return true;
}

// Función que chequea si todo el grafo es bipartito

bool esBipartitio(int n) {

    // Inicializo todas las distancias como no visitadas (-1)
    for ( int i = 1; i <= n; i ++) {
        distancia[i] = -1;
    }

    // Verificar cada componente conexa
    for (int i = 1; i <= n; i++) {
        if (distancia[i] == -1) { // Si no ha sido visitado
            if (!esComponenteBipartita(n, i)) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    int n;
    cin >> n;

    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }


    // Leer las aristas del árbol
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        aristas[u].push_back(v);
        aristas[v].push_back(u);
    }
    
     // Verificar si el árbol es bipartito
    if (!esBipartitio(n)) {
        cout << 0 << endl;  // Si no es bipartito, no se puede agregar ninguna arista
        return 0;
    }

    // Contar los nodos en cada conjunto
    int cantNodosA = 0;
    int cantNodosB = 0;

    for (int i = 1; i <= n; i++) {
        if (distancia[i] % 2 == 0) {
            cantNodosA++;   // Los nodos con distancia par pertenecen al conjunto A
        }   
        else {
             cantNodosB++;  // Los nodos con distancia impar pertenecen al otro conjunto
        }
    }

    // Calcular el número máximo de aristas adicionales que se pueden agregar
    long long maxAristas = (long long) cantNodosA * cantNodosB - (n - 1);  //La cantidad máxima de aristas posibles en un grafo bipartito completo es |A|*|B| 
                                                                           //entonces la cantidad que podemos agregar es |A|*|B| - (n-1) 
                                                                           //ya que la cantidad de aristas que ya estaban de antes es n - 1

    cout << maxAristas << endl;

    return 0;
}
