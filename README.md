# Route Finder

A command-line shortest-route finder for a small road network around Patiala, Punjab, written in C++17. Enter two places and it finds the shortest route using **Dijkstra's algorithm**.

## Features

- Road network modelled as a weighted graph, loaded from a CSV file
- Shortest path with **Dijkstra** (min-heap priority queue)
- Reports route, total distance, nodes explored and time taken
- Case-insensitive input and multi-word names (e.g. "fatehgarh sahib")
- "Did you mean ...?" suggestions for misspelled places

## DSA Concepts Used

| Concept | Where it is used |
|---|---|
| Graph (adjacency list) | Road network in `Graph` class |
| Hash Map (`unordered_map`) | Place name to node ID lookup in O(1) average |
| Priority Queue (min-heap) | Dijkstra's algorithm |
| Dijkstra's algorithm | `Dijkstra.cpp` |
| Dynamic Programming | Edit distance for spelling suggestions |
| Path reconstruction | `parent[]` array, then reverse |

## Complexity

- Dijkstra: O((V + E) log V) time, O(V) space
- Edit distance: O(m * n) per comparison

## Project Structure

```
RouteFinder/
├── include/
│   ├── Graph.h
│   └── Dijkstra.h
├── src/
│   ├── Graph.cpp
│   ├── Dijkstra.cpp
│   └── main.cpp
├── data/
│   └── edges.csv      (from,to,weight in km)
├── tests/
│   └── generate.cpp   (generates a large random graph for benchmarking)
└── README.md
```

## Build and Run

Requires a C++17 compiler (g++).

```
g++ -O2 -std=c++17 src/main.cpp src/Graph.cpp src/Dijkstra.cpp -o routefinder
./routefinder          # Windows PowerShell: .\routefinder.exe
```

Run it from the project root so the `data/` paths resolve.

## Sample Run

```
From: Mohali
To: Ambala

Shortest route: Mohali -> Chandigarh -> Zirakpur -> Ambala
Total distance: 70 km
Nodes explored: 9
```

## Data Format

`data/edges.csv`
```
from,to,weight
Patiala,Rajpura,28
```

Roads are treated as undirected.

## Notes and Limitations

- Distances are **approximate sample data**, not exact road measurements.
- With only 15 nodes, timing is not meaningful. Benchmarks need a larger graph (planned).

## Future Work

- Benchmark on a 100,000-node graph
- Load real road data from OpenStreetMap
- Directed edges for one-way roads
- Unit tests and CMake build
- Command-line arguments for source and destination

