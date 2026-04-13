#include <iostream>
#include <vector>
#include <queue>

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
    // тут начало для меня
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

            //тут две перемнные для меня
        int step = 1;
        int level = 0;
        //тут остановился

        while(!q.empty()){
            int currentVertex = q.front();
            q.pop();

            if(verbose){  
                cout << "Шаг " << step << ": Посещаем вершину" << currentVertex << endl;
               }

               cout << currentVertex << "";


            for(int neighbor : adj[currentVertex]){
                if(!visited[neighbor]){
                    visited[neighbor] = true;
                    q.push(neighbor);
                    if(verbose){
                        cout << "жобавляем  " << neighbor << endl;
                    }
                }
            }
            
    }
    };
    
   

int main(){
    std::queue<int> q;

    q.push(10); // Queue: [10]
    q.push(20); // Queue: [10, 20]
    q.push(30); // Queue: [10, 20, 30]
    string label = "ssdfs";
    printQueue (q, label);
    
    return 0;

}

