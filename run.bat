@echo off
g++ -O2 -std=c++17 src/main.cpp src/Graph.cpp src/Dijkstra.cpp -o routefinder
if %errorlevel%==0 routefinder.exe
