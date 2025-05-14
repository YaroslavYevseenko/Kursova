/* -------------------------------------------------------------------------- */
/*  File:       main.cpp                                                     */
/*  Purpose:    Entry point for the Fillomino puzzle solver                  */
/* -------------------------------------------------------------------------- */

#include <iostream>
#include <fstream>
#include <chrono>
#include "logic.hpp"

int main() {
    std::cout << "Choose input mode:\n";
    std::cout << "1 - Manual input\n";
    std::cout << "2 - Load from file (only 2, 3, 4, 13 allowed)\n";
    std::cout << "> ";

    int input_mode;
    std::cin >> input_mode;

    bool manual = (input_mode == 1);
    int n, m;

    std::istream* in_ptr = nullptr;
    std::ifstream file_input;

    if (manual) {
        std::cout << "Enter grid size (rows and columns): ";
        std::cin >> n >> m;
        in_ptr = &std::cin;
    } else {
        file_input.open("example.in");
        if (!file_input) {
            std::cerr << "File example.in not found!\n";
            return 1;
        }
        file_input >> n >> m;
        in_ptr = &file_input;
    }

    Grid game(n, m);
    game.use_mrv = true;
    game.use_degree = true;
    game.manual_input = manual;

    std::cout << "Enter the grid values row by row:\n";
    game.read(*in_ptr);

    std::cout << "Initial grid:\n";
    game.print(std::cout);

    std::cout << "Starting heuristic algorithm...\n";

    auto start = std::chrono::steady_clock::now();
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
    auto [x, y] = game.select_next_cell(visited);

    bool result = (x != -1) && game.solve_heuristic(x, y, visited, 0);

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Execution time: " << elapsed.count() << " seconds\n";

    if (result) {
        std::cout << "Solution found:\n";
        game.print(std::cout);
    } else {
        std::cout << "No solution exists.\n";
    }

    return 0;
}
