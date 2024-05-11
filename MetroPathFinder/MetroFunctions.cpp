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
    // Станции
    metro.addNode(0, "Al-Sayeda Zeinab", "1 Первая", "Синий");
    metro.addNode(1, "Saad Zaghloul", "1 Первая", "Синий");
    metro.addNode(2, "Sadat-1", "1 Первая", "Синий");
    metro.addNode(3, "Nasser-1", "1 Первая", "Синий");
    metro.addNode(4, "Orabi", "1 Первая", "Синий");
    metro.addNode(5, "Al-Shohadaa", "1 Первая", "Синий");
    metro.addNode(6, "Ghamra", "1 Первая", "Синий");
    metro.addNode(7, "El-Demerdash", "1 Первая", "Синий");
    metro.addNode(8, "Dokki", "2 Вторая", "Красная");
    metro.addNode(9, "Opera", "2 Вторая", "Красная");
    metro.addNode(10, "Sadat-2", "2 Вторая", "Красная");
    metro.addNode(11, "Mohamed Naguib", "2 Вторая", "Красная");
    metro.addNode(12, "Attaba-1", "2 Вторая", "Красная");
    metro.addNode(13, "Al-Shohadaa-2", "2 Вторая", "Красная");
    metro.addNode(14, "Masarra", "2 Вторая", "Красная");
    metro.addNode(15, "Rod El-Farag", "2 Вторая", "Красная");
    metro.addNode(16, "Zamalek", "3 Третья", "Зелёная");
    metro.addNode(17, "Maspero", "3 Третья", "Зелёная");
    metro.addNode(18, "Nasser-2", "3 Третья", "Зелёная");
    metro.addNode(19, "Attaba-2", "3 Третья", "Зелёная");
    metro.addNode(20, "Bab El-Shaaria", "3 Третья", "Зелёная");
    metro.addNode(21, "El-Geish", "3 Третья", "Зелёная");

    // Тунели
    for (size_t i = 0; i < 7; i++) {                     // Синяя ветка
        metro.addEdge(i, i + 1, randomNumber(1, 7));
    }
    for (size_t i = 8; i < 15; i++) {                    // Красная ветка
        metro.addEdge(i, i + 1, randomNumber(1, 7));
    }
    for (size_t i = 16; i < 21; i++) {                   // Зелёная ветка
        metro.addEdge(i, i + 1, randomNumber(1, 7));
    }

    // Переходы
    metro.addEdge(2, 10, 2);
    metro.addEdge(5, 13, 2);
    metro.addEdge(3, 18, 2);
    metro.addEdge(12, 19, 2);
}

void showMainMenu(Graph& metro) {
    // Основное меню
    std::unordered_set<std::string> branches = findMetroBranches(metro);

    std::cout << "Добро пожаловать!\n";

    bool exitRequested = false;
    while (!exitRequested) {
        std::cout << "Выберите действие:\n";
        std::cout << "0 Выйти из программы.\n";
        std::cout << "1 Просмотреть информацию о ветке метро.\n";
        std::cout << "2 Найти кратчайший путь между станциями.\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "\nДоступные ветки метро:\n";
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
                    std::cout << "\nНеверный выбор.\n\n";
                }
            }
            break;
        }
        case 2: {
            std::cout << "\nВведите номер начальной станции: ";
            int startNode;
            std::cin >> startNode;
            std::cout << "Введите номер конечной станции: ";
            int endNode;
            std::cin >> endNode;
            shortestPath(metro, startNode, endNode);
            break;
        }
        case 0:
            exitRequested = true;
            break;
        default:
            std::cout << "\nНеверный выбор.\n\n";
        }
    }
}

std::unordered_set<std::string> findMetroBranches(Graph& metro) {
    // Код для поиска всех уникальных веток метро
    std::unordered_set<std::string> branches;
    int numberStations = metro.getSize();
    for (int i = 0; i < numberStations; ++i) {
        Station stationInfo = metro.getStationData(i);
        branches.insert(stationInfo.branch);
    }
    return branches;
}

void printStationsByBranch(Graph& metro, const std::string& branch) {
    // Код для вывода станций по ветке
    std::vector<int> stations = metro.getStationsByBranch(branch);
    if (stations.empty()) {
        std::cout << "\nНа этой ветке нет станций.\n";
    }
    else {
        std::cout << "\nСтанции на ветке \"" << branch << "\":\n\n";
        for (int station : stations) {
            Station stationInfo = metro.getStationData(station);
            std::cout << "Станция " << stationInfo.name << "\n";
        }
    }
    std::cout << "\n";
}

void shortestPath(Graph& metro, int startNode, int endNode) {
    int numNodes = metro.getSize();
    std::vector<int> distance(numNodes, std::numeric_limits<int>::max()); // Изначально расстояние до всех узлов бесконечность
    std::vector<bool> visited(numNodes, false); // Флаги посещения для узлов
    std::vector<PathInfo> pathInfo(numNodes);  // Информация о пути

    distance[startNode] = 0; // Расстояние до начального узла равно 0

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq; // Очередь с приоритетом для обработки узлов

    pq.push(std::make_pair(0, startNode)); // Добавляем начальный узел в очередь

    while (!pq.empty()) {
        int u = pq.top().second; // Извлекаем узел с наименьшим расстоянием
        pq.pop();

        if (u == endNode) // Если достигли конечного узла, выходим из цикла
            break;

        if (visited[u]) // Если узел уже посещён, пропускаем его
            continue;

        visited[u] = true; // Помечаем узел как посещённый

        // Обходим всех соседей текущего узла
        for (auto& neighbor : metro.getNeighbors(u)) {
            int v = neighbor.first;
            int weight = neighbor.second;

            // Если найденное расстояние до узла v короче, чем ранее известное, обновляем его
            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                pq.push(std::make_pair(distance[v], v));
                pathInfo[v].previousNode = u; // Сохраняем предыдущую станцию для восстановления пути
                pathInfo[v].totalTime = distance[v]; // Обновляем общее время до этой станции
            }
        }
    }

    // Выводим кратчайший путь до конечного узла
    std::cout << "\nКратчайший путь от станции " << metro.getStationData(startNode).name << " до станции "
        << metro.getStationData(endNode).name << " составляет " << pathInfo[endNode].totalTime << " минут.\n";

    // Восстанавливаем полный и упрощенный путь
    std::vector<int> shortestPath;
    std::vector<std::pair<int, int>> simplifiedPath; // Для хранения упрощенного пути

    int currentNode = endNode;
    while (currentNode != startNode) {
        shortestPath.push_back(currentNode);

        // Проверяем, является ли текущая станция "тройной"
        bool isTriple = metro.getNeighbors(currentNode).size() >= 3;

        if (isTriple) {
            // Ищем переход между "тройными" станциями
            int transitionNode = pathInfo[currentNode].previousNode;
            while (transitionNode != startNode && metro.getNeighbors(transitionNode).size() < 3) {
                transitionNode = pathInfo[transitionNode].previousNode;
            }

            // Если нашли переход, добавляем упрощенный маршрут
            if (transitionNode != startNode) {
                simplifiedPath.emplace_back(transitionNode, currentNode);
                currentNode = transitionNode;
                continue;
            }
        }

        // Если нет перехода между "тройными" станциями, продолжаем обычное восстановление пути
        currentNode = pathInfo[currentNode].previousNode;
    }
    shortestPath.push_back(startNode);
    std::reverse(shortestPath.begin(), shortestPath.end());
    std::reverse(simplifiedPath.begin(), simplifiedPath.end());

    // Вывод полного маршрута
    std::cout << "\nПолный маршрут:\n";
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
                std::cout << " - (" << timeBetweenStations << " минут) -> ";
            }
            else {
                std::cout << " -> ";
            }
        }
        std::cout << metro.getStationData(shortestPath[i]).name;
    }

    // Выводим упрощенный маршрут
    std::cout << "\n\nУпрощенный Маршрут:\n";
    std::cout << metro.getStationData(startNode).name << " -> ";
    for (size_t i = 1; i < shortestPath.size() - 1; ++i) {
        bool branchChanged = metro.getStationData(shortestPath[i - 1]).branch != metro.getStationData(shortestPath[i]).branch;
        if (branchChanged) {
            std::cout << "Переход с " << metro.getStationData(shortestPath[i - 1]).name << " на " << metro.getStationData(shortestPath[i]).name << " -> ";
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