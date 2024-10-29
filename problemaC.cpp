#include <iostream>
#include <vector>
#include <deque>

using namespace std;
#define INF 1000000000

// Función para calcular la energía mínima usando BFS con lista de adyacencia
vector<int> calcularEnergiaMinima(int n, vector<vector<int>>& adj, vector<int>& energias) {


    // Cola para BFS
    deque<int> colaBFS;
    colaBFS.push_back(1);  // Empezamos en el aula 1

    while (!colaBFS.empty()) {
        int aula_actual = colaBFS.front();
        colaBFS.pop_front();

        // Verificamos todas las aulas adyacentes a la aula actual
        for (int aula_adyacente : adj[aula_actual]) {
            if (energias[aula_adyacente] > energias[aula_actual] + 1) {
                energias[aula_adyacente] = energias[aula_actual] + 1;
                colaBFS.push_back(aula_adyacente);  // Añadir a la cola para procesar
            }
        }
    }

    return energias;
}

int main() {

    int n;
    cout << ":";
    cin >> n;

    // Lista de adyacencia, donde adj[i] es un vector que contiene las aulas adyacentes a la aula i
    vector<vector<int>> lista_adyacencia(n + 1);

    // Leemos los atajos y llenamos la lista de adyacencia
    for (int i = 1; i <= n; ++i) {
        int atajo;
        cout << ":";
        cin >> atajo;
        if (i + 1 <= n) lista_adyacencia[i].push_back(i + 1);  // Conexión con la aula siguiente
        if (i - 1 >= 1) lista_adyacencia[i].push_back(i - 1);  // Conexión con la aula anterior
        lista_adyacencia[i].push_back(atajo);  // Añadir el atajo como adyacente
    }

    // Inicializamos un vector de energía con valores infinitos
    vector<int> energias(n + 1);

    energias[1] = 0;  // La energía para llegar a la primera aula (índice 1) es 0

    for (int i = 2; i <= n; ++i) {
        
        energias[i] = INF;
    }

    // Calcular la mínima energía para cada aula
    vector<int> res = calcularEnergiaMinima(n, lista_adyacencia, energias);

    // Imprimir el resultado desde el aula 1 hasta el aula n
    for (int i = 1; i <= n; ++i) {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}
