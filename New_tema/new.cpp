#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

void printQueue(queue <int>q, const string& label) {
    cout << label << " [";
    bool first = true;
    while( !q.empty()){
        if(!first) { cout << " " ; }
        cout << q.front();
        q.pop();
        first =  false;
    }
    cout << "]" << endl;
}

class Graph
{
    int numVertices;
    vector < vector < int >> adj;
    vector < bool > visited;
    bool verbose;

    public:
    Graph(int V, bool verboseMode = false){
        numVertices = V;
        adj.resize(V);
        visited.resize (V, false);
        verbose = verboseMode;
    }
    
    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void BFS(int startVertex){
        fill (visited.begin(), visited.end(), false);

        queue <int> q;
        visited [startVertex] = true;
        q.push(startVertex);

        if(verbose){
            printQueue(q, "Очередь после добавления вершины");
            cout << "Посещаем вершину:" << startVertex << endl;
        }

        int step = 1;

        while(!q.empty()){
            int currentVertex = q.front();
            q.pop();

            if(verbose){  
                cout << "Шаг " << step << ": Посещаем вершину" << currentVertex << endl;
            }

            cout << currentVertex << " ";

            for(int neighbor : adj[currentVertex]){
                if(!visited[neighbor]){
                    visited[neighbor] = true;
                    q.push(neighbor);
                    if(verbose){
                        cout << "добавляем  " << neighbor << endl;
                    }
                }
            }
            step++;
        }
    }
};

int main(){
    Graph g1(5, true);
    g1.addEdge(0,1);
    g1.addEdge(1,2);
    g1.addEdge(1,3);
    g1.addEdge(0,4);
    g1.addEdge(4,5);

    g1.BFS(0);
    return 0;

}


