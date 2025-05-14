/* -------------------------------------------------------------------------- */
/*  File:       logic.hpp                                                    */
/*  Purpose:    Header for Fillomino puzzle solver core logic.               */
/* -------------------------------------------------------------------------- */

#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "node.hpp"
#include <iostream>
#include <vector>

/* -------------------------------------------------------------------------- */
/*  Class:      Grid                                                          */
/*  Purpose:    Represents the Fillomino puzzle grid and solver methods.      */
/* -------------------------------------------------------------------------- */
class Grid {
public:
    Grid(int height, int width);   // Constructor
    ~Grid();                       // Destructor

    bool use_mrv = false;          // Use Minimum Remaining Values heuristic
    bool use_degree = false;       // Use Degree heuristic
    bool manual_input = false; 
    std::pair<int, int> select_next_cell(const std::vector<std::vector<bool>>& visited);
    bool solve_heuristic(int i, int j, std::vector<std::vector<bool>>& visited, int visited_count);

    void read(std::istream& in);   // Read grid input
    void print(std::ostream& out) const; // Print grid state

private:
    int height, width;
    Node** board;
    int node_counter = 0;

    const int dx[4] = { -1, 1, 0, 0 };  // Movement in x-direction
    const int dy[4] = { 0, 0, -1, 1 };  // Movement in y-direction

    bool check_indices(int x, int y) const; // Bounds check
    int get_size(int x, int y, int value, std::vector<std::vector<bool>>& visited, bool allow_zero) const;
    bool all_ok() const;            // Check if solution is complete
};

#endif 


