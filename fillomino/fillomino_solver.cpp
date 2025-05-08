#include "fillomino_solver.hpp"
#include <cstring>

Grid::Grid(int h, int w) : height(h), width(w) {
    board = new Node*[height];
    for (int i = 0; i < height; ++i) {
        board[i] = new Node[width];
    }
}

Grid::~Grid() {
    for (int i = 0; i < height; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

void Grid::read(std::istream& in) {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            int val;
            in >> val;
            board[i][j] = Node(i, j, val);
        }
}

void Grid::print(std::ostream& out) const {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j)
            out << board[i][j].value << " ";
        out << "\n";
    }
}

bool Grid::check_indices(int x, int y) const {
    return x >= 0 && x < height && y >= 0 && y < width;
}

int Grid::get_size(int x, int y, int value, bool visited[10][10], bool allow_zero) const {
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

bool Grid::all_ok() const {
    bool visited[10][10];
    std::memset(visited, 0, sizeof(visited));
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

bool Grid::solve(int i, int j) {
    if (node_counter++ > 1000000) return false;
    if (i == height) return all_ok();
    if (j == width) return solve(i + 1, 0);
    if (board[i][j].value != 0)
        return solve(i, j + 1);

    for (int v = 1; v <= 9; ++v) {
        board[i][j].value = v;
        bool visited[10][10] = {};
        int comp_size = get_size(i, j, v, visited, false);
        if (comp_size > v) {
            board[i][j].value = 0;
            continue;
        }
        if (comp_size != v) {
            std::memset(visited, 0, sizeof(visited));
            if (get_size(i, j, v, visited, true) < v) {
                board[i][j].value = 0;
                continue;
            }
        }
        if (solve(i, j + 1)) return true;
        board[i][j].value = 0;
    }
    return false;
}