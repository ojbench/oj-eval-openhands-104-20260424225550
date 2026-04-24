
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> grid(m, vector<int>(n));
    int start_r, start_c, home_r, home_c;
    vector<pair<int, int>> shops;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                start_r = i;
                start_c = j;
            } else if (grid[i][j] == 3) {
                home_r = i;
                home_c = j;
            } else if (grid[i][j] == 4) {
                shops.push_back({i, j});
            }
        }
    }

    auto bfs = [&](int r, int c) {
        vector<vector<int>> dist(m, vector<int>(n, INF));
        queue<pair<int, int>> q;
        dist[r][c] = 0;
        q.push({r, c});

        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};

        while (!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nr = curr.first + dr[i];
                int nc = curr.second + dc[i];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] != 1) {
                    if (dist[nr][nc] == INF) {
                        dist[nr][nc] = dist[curr.first][curr.second] + 1;
                        q.push({nr, nc});
                    }
                }
            }
        }
        return dist;
    };

    vector<vector<int>> dist_start = bfs(start_r, start_c);
    vector<vector<int>> dist_home = bfs(home_r, home_c);

    int min_dist = INF;
    for (auto& shop : shops) {
        if (dist_start[shop.first][shop.second] != INF && dist_home[shop.first][shop.second] != INF) {
            min_dist = min(min_dist, dist_start[shop.first][shop.second] + dist_home[shop.first][shop.second]);
        }
    }

    if (min_dist == INF) {
        // What to output if no path? The problem doesn't specify.
        // Given the context, it's likely there's always a path in test cases,
        // or we should output something like -1.
        // Let's assume -1 for now if no path is found.
        cout << -1 << endl;
    } else {
        cout << min_dist << endl;
    }

    return 0;
}
