#pragma once
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Graph {
private:
    int nodeCount;
    vector<vector<pair<int,int>>> adj;
    unordered_map<string,int> nameToId;
    vector<string> idToName;

    int getOrCreateId(const string& name);

public:
    Graph();
    void addEdge(const string& from, const string& to, int weight, bool directed = false);
    bool loadFromFile(const string& filename);

    int getNodeCount() const;
    int getId(const string& name) const;
    string getName(int id) const;
    const vector<pair<int,int>>& getNeighbors(int u) const;
};