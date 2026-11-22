#include "../include/Dijkstra.h"
#include <queue>
#include <climits>
#include <algorithm>

PathResult Dijkstra::shortestPath(const Graph& g, const string& source, const string& destination) {
    PathResult result;
    result.found = false;
    result.distance = -1;
    result.nodesExplored = 0;

    int src = g.getId(source);
    int dest = g.getId(destination);
    if (src == -1 || dest == -1) return result;

    int n = g.getNodeCount();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);

    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq;

    dist[src] = 0;
    pq.push(make_pair(0, src));

    while (!pq.empty()) {
        pair<int,int> top = pq.top();
        pq.pop();
        int d = top.first;
        int u = top.second;

        if (d > dist[u]) continue;
        result.nodesExplored++;
        if (u == dest) break;

        const vector<pair<int,int> >& neighbors = g.getNeighbors(u);
        for (size_t i = 0; i < neighbors.size(); i++) {
            int v = neighbors[i].first;
            int w = neighbors[i].second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    if (dist[dest] == INT_MAX) return result;

    result.found = true;
    result.distance = dist[dest];

    for (int at = dest; at != -1; at = parent[at])
        result.path.push_back(g.getName(at));
    reverse(result.path.begin(), result.path.end());

    return result;
}
