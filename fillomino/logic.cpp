/* -------------------------------------------------------------------------- */
/*  File:       logic.cpp                                                    */
/*  Purpose:    Core logic implementation for the Fillomino puzzle solver.   */
/* -------------------------------------------------------------------------- */

#include "logic.hpp"
#include <cstring>
#include <vector>

/* -------------------------------------------------------------------------- */
/*  Constructor: Grid                                                         */
/*  Purpose:     Initializes a grid with given height and width              */
/* -------------------------------------------------------------------------- */
Grid::Grid(int h, int w) : height(h), width(w) {
    board = new Node*[height];
    for (int i = 0; i < height; ++i) {
        board[i] = new Node[width];
    }
}

/* -------------------------------------------------------------------------- */
/*  Destructor: ~Grid                                                         */
/*  Purpose:     Cleans up dynamically allocated memory                       */
/* -------------------------------------------------------------------------- */
Grid::~Grid() {
    for (int i = 0; i < height; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

/* -------------------------------------------------------------------------- */
/*  Method:     read                                                          */
/*  Purpose:    Reads the grid from an input stream                          */
/* -------------------------------------------------------------------------- */
void Grid::read(std::istream& in) {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            int val;
            in >> val;
            board[i][j] = Node(i, j, val);
        }
}

/* -------------------------------------------------------------------------- */
/*  Method:     print                                                         */
/*  Purpose:    Prints the current grid to an output stream                  */
/* -------------------------------------------------------------------------- */
void Grid::print(std::ostream& out) const {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j)
            out << board[i][j].value << " ";
        out << "\n";
    }
}

/* -------------------------------------------------------------------------- */
/*  Method:     check_indices                                                 */
/*  Purpose:    Validates cell coordinates                                   */
/* -------------------------------------------------------------------------- */
bool Grid::check_indices(int x, int y) const {
    return x >= 0 && x < height && y >= 0 && y < width;
}

/* -------------------------------------------------------------------------- */
/*  Method:     get_size                                                      */
/*  Purpose:    Computes size of the connected region for a given value      */
/* -------------------------------------------------------------------------- */
int Grid::get_size(int x, int y, int value, std::vector<std::vector<bool>>& visited, bool allow_zero) const {
    visited[x][y] = true;
    int size = 1;

    for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (check_indices(nx, ny) && !visited[nx][ny] &&
            (board[nx][ny].value == value || (allow_zero && board[nx][ny].value == 0))) {
            size += get_size(nx, ny, value, visited, allow_zero);
        }
    }

    return size;
}

/* -------------------------------------------------------------------------- */
/*  Method:     all_ok                                                        */
/*  Purpose:    Checks if the entire grid is a valid Fillomino solution      */
/* -------------------------------------------------------------------------- */
bool Grid::all_ok() const {
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            if (!visited[i][j]) {
                int val = board[i][j].value;
                if (val == 0) return false;
                if (get_size(i, j, val, visited, false) != val)
                    return false;
            }
    return true;
}

/* -------------------------------------------------------------------------- */
/*  Method:     select_next_cell                                              */
/*  Purpose:    Selects the next most promising cell using MRV and Degree    */
/* -------------------------------------------------------------------------- */
std::pair<int, int> Grid::select_next_cell(const std::vector<std::vector<bool>>& visited) {
    int best_score = -1;
    std::pair<int, int> best_cell = {-1, -1};

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (visited[i][j]) continue;

            int mrv_score = 0, degree_score = 0;

            if (use_mrv && board[i][j].value == 0) {
                for (int v = 1; v <= 9; ++v) {
                    std::vector<std::vector<bool>> temp_visited(height, std::vector<bool>(width, false));
                    int comp_size = get_size(i, j, v, temp_visited, false);
                    if (comp_size <= v) {
                        mrv_score++;
                    }
                }
                mrv_score = 9 - mrv_score;
            }

            if (use_degree) {
                for (int d = 0; d < 4; ++d) {
                    int ni = i + dx[d], nj = j + dy[d];
                    if (check_indices(ni, nj) && board[ni][nj].value == 0)
                        degree_score++;
                }
            }

            int total_score = mrv_score + degree_score * 10;
            if (total_score > best_score) {
                best_score = total_score;
                best_cell = {i, j};
            }
        }
    }

    return best_cell;
}

/* -------------------------------------------------------------------------- */
/*  Method:     solve_heuristic                                               */
/*  Purpose:    Solves the puzzle using heuristic search      */
/* -------------------------------------------------------------------------- */
bool Grid::solve_heuristic(int i, int j, std::vector<std::vector<bool>>& visited, int visited_count) {
    if (node_counter++ > 500000) {
        std::cout << "Exceeded node limit\n";
        return false;
    }

    if (i == -1 || j == -1) return false;
    if (visited_count > height * width) return false;

    visited[i][j] = true;
    visited_count++;

    if (board[i][j].value != 0) {
        if (visited_count == height * width) {
            visited[i][j] = false;
            return all_ok();
        }

        auto [ni, nj] = select_next_cell(visited);
        bool res = solve_heuristic(ni, nj, visited, visited_count);
        visited[i][j] = false;
        return res;
    }

    for (int v : {2, 3, 4, 13}) { 
        board[i][j].value = v;
        std::cout << "Trying value " << v << " at (" << i << "," << j << ")\n";

        std::vector<std::vector<bool>> temp_visited(height, std::vector<bool>(width, false));
        int comp_size = get_size(i, j, v, temp_visited, false);
        if (comp_size > v) {
            board[i][j].value = board[i][j].init_value;
            continue;
        }

        temp_visited.assign(height, std::vector<bool>(width, false));
        if (comp_size != v && get_size(i, j, v, temp_visited, true) < v) {
            board[i][j].value = board[i][j].init_value;
            continue;
        }

        auto [ni, nj] = select_next_cell(visited);
        if (ni != -1 && solve_heuristic(ni, nj, visited, visited_count))
            return true;

        board[i][j].value = board[i][j].init_value;
    }

    visited[i][j] = false;
    std::cout << "Returning from (" << i << "," << j << ")\n";
    return false;
}









