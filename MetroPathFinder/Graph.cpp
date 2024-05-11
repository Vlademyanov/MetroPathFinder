#include "Graph.h"

void Graph::addNode(int number, const std::string& name, const std::string& branch, const std::string& color) {
    if (nodes.find(number) == nodes.end()) {
        nodes[number] = std::unordered_map<int, int>();
        stationData[number] = { name, number, branch, color };
    }
}

void Graph::addEdge(int node1, int node2, int weight) {
    addNode(node1, "", "", "");
    addNode(node2, "", "", "");
    nodes[node1][node2] = weight;
    nodes[node2][node1] = weight;
}

std::unordered_map<int, int> Graph::getNeighbors(int node) {
    if (nodes.find(node) != nodes.end()) {
        return nodes[node];
    }
    else {
        return std::unordered_map<int, int>();
    }
}

int Graph::getSize() const {
    return nodes.size();
}

Station Graph::getStationData(int number) {
    return stationData[number];
}

std::vector<int> Graph::getStationsByBranch(const std::string& branch) {
    std::vector<int> stations;
    for (const auto& station : stationData) {
        if (station.second.branch == branch) {
            stations.push_back(station.first);
        }
    }
    return stations;
}
