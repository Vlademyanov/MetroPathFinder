#ifndef METRO_FUNCTIONS_H
#define METRO_FUNCTIONS_H

#include <string>
#include "Graph.h"

// Функция инициализации метро
void initializeMetro(Graph& metro);

// Функция отображения главного меню
void showMainMenu(Graph& metro);

// Функция для нахождения всех уникальных веток метро
std::unordered_set<std::string> findMetroBranches(Graph& metro);

// Вывод станций по ветке
void printStationsByBranch(Graph& metro, const std::string& branch);

// Функция для нахождения кратчайшего пути между станциями с использованием алгоритма Дейкстры
void shortestPath(Graph& metro, int startNode, int endNode);

// Рандом
int randomNumber(int min, int max);

#endif // METRO_FUNCTIONS_H
