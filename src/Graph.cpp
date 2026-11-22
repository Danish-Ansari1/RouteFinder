#include "../include/Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>

Graph::Graph() : nodeCount(0) {}

int Graph::getOrCreateId(const string& name) {
    auto it = nameToId.find(name);
    if (it != nameToId.end()) return it->second;

    nameToId[name] = nodeCount;
    idToName.push_back(name);
    adj.push_back({});
    return nodeCount++;
}

void Graph::addEdge(const string& from, const string& to, int weight, bool directed) {
    int u = getOrCreateId(from);
    int v = getOrCreateId(to);
    adj[u].push_back({v, weight});
    if (!directed) adj[v].push_back({u, weight});
}

bool Graph::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "File open nahi hui: " << filename << endl;
        return false;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string from, to, w;
        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, w, ',');
        addEdge(from, to, stoi(w));
    }
    return true;
}

int Graph::getNodeCount() const { return nodeCount; }

int Graph::getId(const string& name) const {
    auto it = nameToId.find(name);
    return it == nameToId.end() ? -1 : it->second;
}

string Graph::getName(int id) const { return idToName[id]; }

const vector<pair<int,int>>& Graph::getNeighbors(int u) const { return adj[u]; }