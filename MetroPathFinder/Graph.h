#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <string>

#include "Station.h"

class Graph {
private:
    std::unordered_map<int, std::unordered_map<int, int>> nodes;
    std::unordered_map<int, Station> stationData;

public:
    void addNode(int number, const std::string& name, const std::string& branch, const std::string& color);

    void addEdge(int node1, int node2, int weight);

    std::unordered_map<int, int> getNeighbors(int node);

    int getSize() const;

    Station  getStationData(int number);

    std::vector<int> getStationsByBranch(const std::string& branch);
};
#endif // GRAPH_H
