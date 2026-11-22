#pragma once
#include "Graph.h"
#include <vector>
#include <string>
using namespace std;

struct PathResult {
    bool found;
    int distance;
    int nodesExplored;
    vector<string> path;
};

class Dijkstra {
public:
    static PathResult shortestPath(const Graph& g, const string& source, const string& destination);
};
