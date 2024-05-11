#include <iostream>
#include <unordered_set>
#include "Graph.h"
#include "MetroFunctions.h"

int main() {
    // Русский язык
    setlocale(0, "");

    // Сеть метро
    Graph metro;

    // Инициализация метро
    initializeMetro(metro);

    // Главное меню
    showMainMenu(metro);

    return 0;
}
