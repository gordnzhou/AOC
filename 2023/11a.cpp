#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll; 

vector<vector<char>> grid;
vector<vector<int>> gals;
vector<vector<ll>> empt;
int n, m;

ll GAP = 2;

vector<vector<int>> steps = {
    {0, 1},
    {-1, 0},
    {0, -1},
    {1, 0},
};

bool empty_col(int i) {
    bool ret = 1;
    for (int j = 0; j < m; ++j) {
        ret &= (grid[i][j] == '.');
    }
    return ret;
}

bool empty_row(int j) {
    bool ret = 1;
    for (int i = 0; i < n; ++i) {
        ret &= (grid[i][j] == '.');
    }
    return ret;
}

ll bfs(vector<int> start) {
    ll dist[n][m];
    memset(dist, 0, n * m * sizeof(ll));

    queue<vector<int>> q;
    dist[start[0]][start[1]] = 1LL;
    q.push(start);

    while (!q.empty()) {
        vector<int> f = q.front();
        int i = f[0], j = f[1];
        q.pop();

        for (auto s : steps) {
            int ni = i + s[0], nj = j + s[1];
            if (dist[ni][nj] > 0 || ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
            dist[ni][nj] = dist[i][j] + 1LL + (GAP - 1LL) * empt[ni][nj];
            q.push({ni, nj});
        }
    }

    ll ret = 0;
    for (auto g : gals) {
        if (g == start) continue;
        ret += dist[g[0]][g[1]] - 1LL;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream infile("input.txt");
    string line;
    string s;


    while (getline(cin, line)) {
        vector<char> row;
        for (auto c : line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }
    n = grid.size(), m = grid[0].size();

    for (int i = 0; i < n; ++i) {
        vector<ll> row;
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '#') {
                gals.push_back({i, j});
            }
            ll e = empty_row(j) + empty_col(i);
            row.push_back(e);
        }
        empt.push_back(row);
    }

    ll ans = 0;
    for (auto g : gals) {
        ans += bfs(g);
    }

    cout << ans / 2LL << "\n";
}