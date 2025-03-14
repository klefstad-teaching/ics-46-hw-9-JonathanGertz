#include "dijkstras.h"
#include <iostream>
#include <vector>

using namespace std;

void test_dijkstras() {
    Graph G;
    G.numVertices = 5;
    G.resize(5);
    
    G[0].push_back({0, 1, 10});
    G[0].push_back({0, 3, 30});
    G[0].push_back({0, 4, 100});
    G[1].push_back({1, 2, 50});
    G[2].push_back({2, 4, 10});
    G[3].push_back({3, 2, 20});
    G[3].push_back({3, 4, 60});

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
    cout << "Shortest distances from node 0:" << endl;
    for (int i = 0; i < distances.size(); i++) {
        cout << "Node " << i << ": " << distances[i] << endl;
    }
    
    int destination = 4;
    vector<int> path = extract_shortest_path(distances, previous, destination);
    
    cout << "\nPath from 0 to " << destination << ":" << endl;
    print_path(path, distances[destination]);
}

int main() {
    test_dijkstras();
    return 0;
}
