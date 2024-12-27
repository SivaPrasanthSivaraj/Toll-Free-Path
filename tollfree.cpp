#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Graph {
public:
    vector<vector<int>> dist;   
    vector<vector<int>> next;   
    vector<vector<bool>> isToll;  

    Graph(int nodes) {
        dist.resize(nodes, vector<int>(nodes, INT_MAX));
        next.resize(nodes, vector<int>(nodes, -1));
        isToll.resize(nodes, vector<bool>(nodes, false));

    
        for (int i = 0; i < nodes; ++i) {
            dist[i][i] = 0;
            next[i][i] = i;
        }
    }

    void addEdge(int u, int v, int weight, bool toll = false) {
        dist[u][v] = weight;
        dist[v][u] = weight;
        isToll[u][v] = toll;
        isToll[v][u] = toll;
        next[u][v] = v;
        next[v][u] = u;
    }

 
    void floydWarshall() {
        int n = dist.size();
        
   
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (isToll[i][j]) {
                    dist[i][j] = INT_MAX; 
                    next[i][j] = -1;       
                }
            }
        }


        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                        if (dist[i][j] > dist[i][k] + dist[k][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            next[i][j] = next[i][k];
                        }
                    }
                }
            }
        }
    }

    int getShortestDistance(int u, int v) {
        return dist[u][v];
    }

    void printPath(int u, int v) {
        if (next[u][v] == -1) {
            cout << "No path available between node " << u << " and node " << v << ".\n";
            return;
        }

        cout << "Shortest path from node " << u << " to node " << v << ": ";
        int current = u;
        while (current != v) {
            cout << current << " -> ";
            current = next[current][v];
        }
        cout << v << endl;
    }

    /*void printShortestPaths() {
        int n = dist.size();
        cout << "Shortest Path Distances (Excluding Toll Roads):\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] == INT_MAX) {
                    cout << "INF ";
                } else {
                    cout << dist[i][j] << " ";
                }
            }
            cout << endl;
        }
    }*/
};

int main() {
    Graph g(15); 
    
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 20, true);
    g.addEdge(0, 2, 30);
    g.addEdge(2, 3, 40);
    g.addEdge(3, 4, 50, true); 
    g.addEdge(0, 4, 60);
    g.addEdge(4, 5, 70);
    g.addEdge(5, 6, 80);
    g.addEdge(6, 7, 90);
    g.addEdge(7, 8, 100);
    g.addEdge(8, 9, 110);
    g.addEdge(9, 10, 120, true);
    g.addEdge(10, 11, 130);
    g.addEdge(11, 12, 140);
    g.addEdge(12, 13, 150);
    g.addEdge(13, 14, 160);

    g.floydWarshall();

    int source, destination;
    char choice;

    cout << "==========Find You Shortest Path In Your Journey!!==========" << endl;
    cout<< endl;

do {
    cout << "Enter source node: ";
    cin >> source;
    cout << "Enter destination node: ";
    cin >> destination;


    if (source >= 15 || destination >= 15) {
        cout << "Invalid input! Source and destination nodes must be less than 15.\n";
        continue; 
    }

    int shortestDist = g.getShortestDistance(source, destination);
    if (shortestDist == INT_MAX) {
        cout << "No path available between node " << source << " and node " << destination << ".\n";
    } else {
        cout << "The shortest distance from node " << source << " to node " << destination << " (excluding toll roads) is: " << shortestDist << endl;
        g.printPath(source, destination);
    }

    cout << "\nDo you want to find another path? (y/n): ";
    cin >> choice;

} while (choice == 'y' || choice == 'Y');

cout << "Exiting the program. Thank you!\n";
return 0;

}

