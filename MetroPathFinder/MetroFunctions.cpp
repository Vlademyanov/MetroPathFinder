#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <unordered_set>
#include <queue>
#include <limits>
#include "Graph.h"
#include "PathInfo.h"
#include "MetroFunctions.h"


void initializeMetro(Graph& metro) {
    // �������
    metro.addNode(0, "Al-Sayeda Zeinab", "1 ������", "�����");
    metro.addNode(1, "Saad Zaghloul", "1 ������", "�����");
    metro.addNode(2, "Sadat-1", "1 ������", "�����");
    metro.addNode(3, "Nasser-1", "1 ������", "�����");
    metro.addNode(4, "Orabi", "1 ������", "�����");
    metro.addNode(5, "Al-Shohadaa", "1 ������", "�����");
    metro.addNode(6, "Ghamra", "1 ������", "�����");
    metro.addNode(7, "El-Demerdash", "1 ������", "�����");
    metro.addNode(8, "Dokki", "2 ������", "�������");
    metro.addNode(9, "Opera", "2 ������", "�������");
    metro.addNode(10, "Sadat-2", "2 ������", "�������");
    metro.addNode(11, "Mohamed Naguib", "2 ������", "�������");
    metro.addNode(12, "Attaba-1", "2 ������", "�������");
    metro.addNode(13, "Al-Shohadaa-2", "2 ������", "�������");
    metro.addNode(14, "Masarra", "2 ������", "�������");
    metro.addNode(15, "Rod El-Farag", "2 ������", "�������");
    metro.addNode(16, "Zamalek", "3 ������", "������");
    metro.addNode(17, "Maspero", "3 ������", "������");
    metro.addNode(18, "Nasser-2", "3 ������", "������");
    metro.addNode(19, "Attaba-2", "3 ������", "������");
    metro.addNode(20, "Bab El-Shaaria", "3 ������", "������");
    metro.addNode(21, "El-Geish", "3 ������", "������");

    // ������
    for (size_t i = 0; i < 7; i++) {                     // ����� �����
        metro.addEdge(i, i + 1, randomNumber(1, 7));
    }
    for (size_t i = 8; i < 15; i++) {                    // ������� �����
        metro.addEdge(i, i + 1, randomNumber(1, 7));
    }
    for (size_t i = 16; i < 21; i++) {                   // ������ �����
        metro.addEdge(i, i + 1, randomNumber(1, 7));
    }

    // ��������
    metro.addEdge(2, 10, 2);
    metro.addEdge(5, 13, 2);
    metro.addEdge(3, 18, 2);
    metro.addEdge(12, 19, 2);
}

void showMainMenu(Graph& metro) {
    // �������� ����
    std::unordered_set<std::string> branches = findMetroBranches(metro);

    std::cout << "����� ����������!\n";

    bool exitRequested = false;
    while (!exitRequested) {
        std::cout << "�������� ��������:\n";
        std::cout << "0 ����� �� ���������.\n";
        std::cout << "1 ����������� ���������� � ����� �����.\n";
        std::cout << "2 ����� ���������� ���� ����� ���������.\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "\n��������� ����� �����:\n";
            for (const std::string& branch : branches) {
                std::cout << branch << "\n";
            }
            int branchChoice;
            std::cin >> branchChoice;

            switch (branchChoice) {
            case 0:
                exitRequested = true;
                break;
            default:
                if (branchChoice > 0 && branchChoice <= branches.size()) {
                    auto it = branches.begin();
                    std::advance(it, branchChoice - 1);
                    printStationsByBranch(metro, *it);
                }
                else {
                    std::cout << "\n�������� �����.\n\n";
                }
            }
            break;
        }
        case 2: {
            std::cout << "\n������� ����� ��������� �������: ";
            int startNode;
            std::cin >> startNode;
            std::cout << "������� ����� �������� �������: ";
            int endNode;
            std::cin >> endNode;
            shortestPath(metro, startNode, endNode);
            break;
        }
        case 0:
            exitRequested = true;
            break;
        default:
            std::cout << "\n�������� �����.\n\n";
        }
    }
}

std::unordered_set<std::string> findMetroBranches(Graph& metro) {
    // ��� ��� ������ ���� ���������� ����� �����
    std::unordered_set<std::string> branches;
    int numberStations = metro.getSize();
    for (int i = 0; i < numberStations; ++i) {
        Station stationInfo = metro.getStationData(i);
        branches.insert(stationInfo.branch);
    }
    return branches;
}

void printStationsByBranch(Graph& metro, const std::string& branch) {
    // ��� ��� ������ ������� �� �����
    std::vector<int> stations = metro.getStationsByBranch(branch);
    if (stations.empty()) {
        std::cout << "\n�� ���� ����� ��� �������.\n";
    }
    else {
        std::cout << "\n������� �� ����� \"" << branch << "\":\n\n";
        for (int station : stations) {
            Station stationInfo = metro.getStationData(station);
            std::cout << "������� " << stationInfo.name << "\n";
        }
    }
    std::cout << "\n";
}

void shortestPath(Graph& metro, int startNode, int endNode) {
    int numNodes = metro.getSize();
    std::vector<int> distance(numNodes, std::numeric_limits<int>::max()); // ���������� ���������� �� ���� ����� �������������
    std::vector<bool> visited(numNodes, false); // ����� ��������� ��� �����
    std::vector<PathInfo> pathInfo(numNodes);  // ���������� � ����

    distance[startNode] = 0; // ���������� �� ���������� ���� ����� 0

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq; // ������� � ����������� ��� ��������� �����

    pq.push(std::make_pair(0, startNode)); // ��������� ��������� ���� � �������

    while (!pq.empty()) {
        int u = pq.top().second; // ��������� ���� � ���������� �����������
        pq.pop();

        if (u == endNode) // ���� �������� ��������� ����, ������� �� �����
            break;

        if (visited[u]) // ���� ���� ��� �������, ���������� ���
            continue;

        visited[u] = true; // �������� ���� ��� ����������

        // ������� ���� ������� �������� ����
        for (auto& neighbor : metro.getNeighbors(u)) {
            int v = neighbor.first;
            int weight = neighbor.second;

            // ���� ��������� ���������� �� ���� v ������, ��� ����� ���������, ��������� ���
            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                pq.push(std::make_pair(distance[v], v));
                pathInfo[v].previousNode = u; // ��������� ���������� ������� ��� �������������� ����
                pathInfo[v].totalTime = distance[v]; // ��������� ����� ����� �� ���� �������
            }
        }
    }

    // ������� ���������� ���� �� ��������� ����
    std::cout << "\n���������� ���� �� ������� " << metro.getStationData(startNode).name << " �� ������� "
        << metro.getStationData(endNode).name << " ���������� " << pathInfo[endNode].totalTime << " �����.\n";

    // ��������������� ������ � ���������� ����
    std::vector<int> shortestPath;
    std::vector<std::pair<int, int>> simplifiedPath; // ��� �������� ����������� ����

    int currentNode = endNode;
    while (currentNode != startNode) {
        shortestPath.push_back(currentNode);

        // ���������, �������� �� ������� ������� "�������"
        bool isTriple = metro.getNeighbors(currentNode).size() >= 3;

        if (isTriple) {
            // ���� ������� ����� "��������" ���������
            int transitionNode = pathInfo[currentNode].previousNode;
            while (transitionNode != startNode && metro.getNeighbors(transitionNode).size() < 3) {
                transitionNode = pathInfo[transitionNode].previousNode;
            }

            // ���� ����� �������, ��������� ���������� �������
            if (transitionNode != startNode) {
                simplifiedPath.emplace_back(transitionNode, currentNode);
                currentNode = transitionNode;
                continue;
            }
        }

        // ���� ��� �������� ����� "��������" ���������, ���������� ������� �������������� ����
        currentNode = pathInfo[currentNode].previousNode;
    }
    shortestPath.push_back(startNode);
    std::reverse(shortestPath.begin(), shortestPath.end());
    std::reverse(simplifiedPath.begin(), simplifiedPath.end());

    // ����� ������� ��������
    std::cout << "\n������ �������:\n";
    for (size_t i = 0; i < shortestPath.size(); ++i) {
        if (i != 0) {
            int timeBetweenStations = -1;
            for (auto& neighbor : metro.getNeighbors(shortestPath[i - 1])) {
                if (neighbor.first == shortestPath[i]) {
                    timeBetweenStations = neighbor.second;
                    break;
                }
            }
            if (timeBetweenStations != -1) {
                std::cout << " - (" << timeBetweenStations << " �����) -> ";
            }
            else {
                std::cout << " -> ";
            }
        }
        std::cout << metro.getStationData(shortestPath[i]).name;
    }

    // ������� ���������� �������
    std::cout << "\n\n���������� �������:\n";
    std::cout << metro.getStationData(startNode).name << " -> ";
    for (size_t i = 1; i < shortestPath.size() - 1; ++i) {
        bool branchChanged = metro.getStationData(shortestPath[i - 1]).branch != metro.getStationData(shortestPath[i]).branch;
        if (branchChanged) {
            std::cout << "������� � " << metro.getStationData(shortestPath[i - 1]).name << " �� " << metro.getStationData(shortestPath[i]).name << " -> ";
        }
    }
    std::cout << metro.getStationData(endNode).name << "\n\n";
}

int randomNumber(int min, int max) {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}