#include <iostream>
using namespace std;

const int N = 10;

int grid[N][N] = {
    {2, 0, 2, 0, 4, 0, 2, 0, 4, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {3, 0, 2, 0, 2, 0, 2, 3, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 3, 0, 2},
    {3, 0, 3, 0, 0, 3, 0, 0, 0, 0},
    {0, 0, 0, 0, 4, 0, 0, 4, 0, 4},
    {2, 0, 4, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 4, 2, 0, 2, 0, 2, 0, 4},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 3, 0, 2, 0, 3, 0, 2, 0, 2}
};

bool visited[N][N];

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool isInside(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

bool isConnected(const std::vector<std::pair<int, int>>& cells) {
    std::set<std::pair<int, int>> visited;
    std::queue<std::pair<int, int>> q;
    q.push(cells[0]);
    visited.insert(cells[0]);

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (isInside(nx, ny) && std::find(cells.begin(), cells.end(), std::make_pair(nx, ny)) != cells.end()) {
                if (!visited.count({nx, ny})) {
                    visited.insert({nx, ny});
                    q.push({nx, ny});
                }
            }
        }
    }

    return visited.size() == cells.size();
}