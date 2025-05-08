#include "fillomino_solver.hpp"
#include <iostream>
#include <fstream>
#include <chrono>


int main() {
    std::ifstream input("C:/cygwin64/home/Repositorii/fillomino/fillomino.in");
    std::cout << "Відкриваю файл fillomino.in..." << std::endl;
    if (!input) {
        std::cerr << "Помилка: не вдалося відкрити файл fillomino.in" << std::endl;
        return 1;
    }

    int n, m, test = 1;
    while (input >> n >> m) {
        Grid game(n, m);
        game.read(input);

        auto start = std::chrono::steady_clock::now();

        std::cout << "Тест " << test++ << ": " << std::endl;

        if (game.solve(0, 0)) {
            std::cout << "Розв'язок знайдено:\n";
            game.print(std::cout);
        } else {
            std::cout << "Розв'язку не існує." << std::endl;
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Час виконання: " << elapsed.count() << " сек\n";        

        std::cout << "-----------------------------\n";
    }

    return 0;
}
