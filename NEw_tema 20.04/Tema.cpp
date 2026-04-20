#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void printStack(stack <int> s, const string& label) {
    cout << label << " [";
    vector <int> temp;
    while (!s.empty()) {
        temp.push_back(s.top());
        s.pop();
    }
    for (int i = temp.size() - 1; i >= 0; i--) {
        cout << temp[i];
        if (i > 0) {
            cout << " ";
        }
    }
    cout << "]" << endl;
}

class Graph {
    int numVertices;
    vector<vector<int>> adj;
    vector<bool> visited;
    bool verbose;
public:
    Graph(int v, bool verboseMode = false) {
        numVertices = v;
        adj.resize(v);
        visited.resize(v, false);
        verbose = verboseMode;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void DFS(int startVertex) {
        fill(visited.begin(), visited.end(), false);
        stack <int> s;
        visited[startVertex] = true;
        s.push(startVertex);

        if (verbose) {
            printStack(s, "Начало ");
        }
        
        while (!s.empty()) {
            int currentVertex = s.top();
            s.pop();

            cout << currentVertex << " ";

            if (verbose) {
                cout << "Ищем соседей currentVertex: " << currentVertex << " : ";
                for (int neighbor : adj[currentVertex]) {
                    cout << neighbor;
                    if (visited[neighbor]) {
                        cout << " посещён ";
                    } else {
                        cout << " Новая ";
                    }
                }
                cout << endl;
            }

            for (int i = adj[currentVertex].size() - 1; i >= 0; i--) {
                int neighbor = adj[currentVertex][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                    if (verbose) {:}
                }
            }
        }
    }
};
