#include <iostream>
#include <unordered_set>
#include "Graph.h"
#include "MetroFunctions.h"

int main() {
    // ������� ����
    setlocale(0, "");

    // ���� �����
    Graph metro;

    // ������������� �����
    initializeMetro(metro);

    // ������� ����
    showMainMenu(metro);

    return 0;
}
