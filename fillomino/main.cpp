#include <iostream>
#include <fstream>
#include <chrono>
#include "fillomino_solver.hpp"

int main() {
    std::ifstream input("C:/cygwin64/home/Repositorii/fillomino/fillomino.in");
    if (!input) {
        std::cerr << "Файл fillomino.in не знайдено!" << std::endl;
        return 1;
    }

    int n, m, test = 1;
    while (input >> n >> m) {
        Grid game(n, m);
        game.read(input);

        std::cout << "Тест " << test++ << ":\n";
        game.print(std::cout);

        std::cout << "Оберіть алгоритм:\n";
        std::cout << "1 - Простий backtracking\n";
        std::cout << "6 - Евристичний (MRV + Degree)\n";
        std::cout << "> ";

        int choice;
        std::cin >> choice;

        bool result = false;
        auto start = std::chrono::steady_clock::now();

        if (choice == 1) {
            result = game.solve(0, 0);
        } else if (choice == 6) {
            game.use_mrv = true;
            game.use_degree = true;

            std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
            auto [x, y] = game.select_next_cell(visited);

            if (x == -1 || y == -1) {
                std::cout << "Немає доступної клітинки для старту!\n";
                result = false;
            } else {
                result = game.solve_heuristic(x, y, visited, 0);
            }
        } else {
            std::cout << "Невідома опція!" << std::endl;
            return 1;
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Час виконання: " << elapsed.count() << " сек\n";

        if (result) {
            std::cout << "Розв'язок знайдено:\n";
            game.print(std::cout);
        } else {
            std::cout << "Розв'язку не існує.\n";
        }

        std::cout << "-----------------------------\n";
    }

    return 0;
}
