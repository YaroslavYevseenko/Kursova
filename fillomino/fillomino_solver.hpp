#ifndef FILLOMINO_SOLVER_HPP
#define FILLOMINO_SOLVER_HPP

#include "node.hpp"
#include <iostream>
#include <vector>

class Grid {
public:
    Grid(int height, int width);
    ~Grid();

    bool use_mrv = false;
    bool use_degree = false;

    std::pair<int, int> select_next_cell(const std::vector<std::vector<bool>>& visited);
    bool solve_heuristic(int i, int j, std::vector<std::vector<bool>>& visited, int visited_count);

    void read(std::istream& in);
    void print(std::ostream& out) const;
    bool solve(int i, int j);

private:
    int height, width;
    Node** board;
    int node_counter = 0;
    const int dx[4] = { -1, 1, 0, 0 };
    const int dy[4] = { 0, 0, -1, 1 };

    bool check_indices(int x, int y) const;
    int get_size(int x, int y, int value, std::vector<std::vector<bool>>& visited, bool allow_zero) const;
    bool all_ok() const;
};

#endif
