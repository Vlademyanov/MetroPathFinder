#ifndef METRO_FUNCTIONS_H
#define METRO_FUNCTIONS_H

#include <string>
#include "Graph.h"

// ������� ������������� �����
void initializeMetro(Graph& metro);

// ������� ����������� �������� ����
void showMainMenu(Graph& metro);

// ������� ��� ���������� ���� ���������� ����� �����
std::unordered_set<std::string> findMetroBranches(Graph& metro);

// ����� ������� �� �����
void printStationsByBranch(Graph& metro, const std::string& branch);

// ������� ��� ���������� ����������� ���� ����� ��������� � �������������� ��������� ��������
void shortestPath(Graph& metro, int startNode, int endNode);

// ������
int randomNumber(int min, int max);

#endif // METRO_FUNCTIONS_H
