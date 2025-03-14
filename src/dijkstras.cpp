#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);
    priority_queue<pair<int,int>> minHeap;
    minHeap.push({0, source});
    distances[source] = 0;
    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (Edge edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    stack<int> temp_path;

    if(distances[destination] == INF) return path;

    for (int v = destination; v != -1; v = previous[v]) {
        temp_path.push(v);
    }
    while (!temp_path.empty()) {
        path.push_back(temp_path.top());
        temp_path.pop();
    }
    return path;
}

void print_path(const vector<int>& path, int total) {
    if(path.empty()) {
        cout << "No path found" << endl;
        return;
    }
    cout << "shorted path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << "\n Total cost is: " << total << endl;
}