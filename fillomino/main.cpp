/* -------------------------------------------------------------------------- */
/*  File:       main.cpp                                                     */
/*  Purpose:    Entry point for the Fillomino puzzle solver                  */
/* -------------------------------------------------------------------------- */

#include <iostream>
#include <fstream>
#include <chrono>
#include "logic.hpp"

int main() {
    std::ifstream input("C:/cygwin64/home/Repositorii/fillomino/fillomino.in");
    if (!input) {
        std::cerr << "File fillomino.in not found!" << std::endl;
        return 1;
    }

    int n, m, test = 1;
    while (input >> n >> m) {
        Grid game(n, m);
        game.read(input);

        std::cout << "Test " << test++ << ":\n";
        game.print(std::cout);

        std::cout << "Starting heuristic algorithm...\n";

        bool result = false;
        auto start = std::chrono::steady_clock::now();

        game.use_mrv = true;
        game.use_degree = true;

        std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
        auto [x, y] = game.select_next_cell(visited);

        if (x == -1 || y == -1) {
            std::cout << "No available starting cell!\n";
            result = false;
        } else {
            result = game.solve_heuristic(x, y, visited, 0);
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Execution time: " << elapsed.count() << " seconds\n";

        if (result) {
            std::cout << "Solution found:\n";
            game.print(std::cout);
        } else {
            std::cout << "No solution exists.\n";
        }
    }

    return 0;
}
