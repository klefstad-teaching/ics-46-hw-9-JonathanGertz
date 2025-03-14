#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    vector<int> distances(G.numVertices, INF);
    previous.assign(G.numVertices, -1);
    distances[source] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();
        
        if (currentDist > distances[currentNode]) continue;
        
        for (const Edge& edge : G[currentNode]) {
            int neighbor = edge.dst;
            int newDist = distances[currentNode] + edge.weight;
            
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                previous[neighbor] = currentNode;
                pq.push({newDist, neighbor});
            }
        }
    }
    
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    vector<int> path;
    if (distances[destination] == INF) {
        return path;
    }
    
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total)
{
    if (v.empty()) {
        cout << "No path found" << endl;
        return;
    }
    
    cout << "Shortest path: ";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i < v.size() - 1) cout << " -> ";
    }
    cout << "\nTotal distance: " << total << endl;
}