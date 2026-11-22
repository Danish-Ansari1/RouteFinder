#include <chrono>
#include "../include/Graph.h"
#include "../include/Dijkstra.h"
#include <iostream>
#include <algorithm>
#include <cctype>

string normalize(string s) {
    bool newWord = true;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == ' ') { newWord = true; continue; }
        s[i] = newWord ? toupper(s[i]) : tolower(s[i]);
        newWord = false;
    }
    return s;
}

int editDistance(const string& a, const string& b) {
    vector<vector<int> > dp(a.size() + 1, vector<int>(b.size() + 1));
    for (size_t i = 0; i <= a.size(); i++) dp[i][0] = i;
    for (size_t j = 0; j <= b.size(); j++) dp[0][j] = j;
    for (size_t i = 1; i <= a.size(); i++)
        for (size_t j = 1; j <= b.size(); j++) {
            int cost = (a[i-1] == b[j-1]) ? 0 : 1;
            dp[i][j] = min(min(dp[i-1][j] + 1, dp[i][j-1] + 1), dp[i-1][j-1] + cost);
        }
    return dp[a.size()][b.size()];
}

string closestPlace(const Graph& g, const string& input) {
    string best = "";
    int bestDist = 1000;
    for (int i = 0; i < g.getNodeCount(); i++) {
        int d = editDistance(input, g.getName(i));
        if (d < bestDist) { bestDist = d; best = g.getName(i); }
    }
    return bestDist <= 3 ? best : "";
}

bool resolvePlace(const Graph& g, string& name) {
    name = normalize(name);
    if (g.getId(name) != -1) return true;
    string s = closestPlace(g, name);
    if (s.empty()) {
        cout << "Place \"" << name << "\" not found. Please choose from the list above." << endl;
        return false;
    }
    cout << "Place \"" << name << "\" not found. Did you mean \"" << s << "\"? (y/n): ";
    string ans;
    getline(cin, ans);
    if (!ans.empty() && (ans[0] == 'y' || ans[0] == 'Y')) { name = s; return true; }
    return false;
}

int main() {
    Graph g;
    if (!g.loadFromFile("data/edges.csv")) return 1;

    cout << "=== Route Finder ===" << endl;
    cout << "Available places: ";
    for (int i = 0; i < g.getNodeCount(); i++) {
        cout << g.getName(i);
        if (i + 1 < g.getNodeCount()) cout << ", ";
    }
    cout << endl << endl;

    string source, destination;
    cout << "From: ";
    getline(cin, source);
    if (!resolvePlace(g, source)) return 0;

    cout << "To: ";
    getline(cin, destination);
    if (!resolvePlace(g, destination)) return 0;

    auto start = chrono::high_resolution_clock::now();
    PathResult res = Dijkstra::shortestPath(g, source, destination);
    auto end = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(end - start).count();

    if (!res.found) {
        cout << "No route found between these places." << endl;
        return 0;
    }

    cout << endl << "Shortest route: ";
    for (size_t i = 0; i < res.path.size(); i++) {
        cout << res.path[i];
        if (i + 1 < res.path.size()) cout << " -> ";
    }
    cout << endl << "Total distance: " << res.distance << " km" << endl;
    cout << "Nodes explored: " << res.nodesExplored << endl;
    cout << "Time taken: " << ms << " ms" << endl;
    return 0;
}