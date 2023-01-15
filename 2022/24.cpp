#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

const int N = 1e5;

vector<pair<int, int>> D = {
    {0, -1},
    {0, 1},
    {1, 0},
    {-1, 0},
    {0, 0}
};
int n, m;

int negMod(int a, int b) {
    return (b + (a % b)) % b;
}

int toKey(int f, int s) {
    return f + n * s;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);

    string line;
    vector<string> lines;
    while (getline(cin, line)) {
       lines.push_back(line);
    }
    n = lines.size(), m = lines[0].size();

    int M = toKey(n, m);

    // repeats at time = lcm(# rows, # columns)
    int cycle = (n - 2) * (m - 2) / __gcd(n - 2, m - 2); 

    vector<vector<bool>> state(N, vector<bool>(M, 0));
    vector<vector<bool>> seen(M, vector<bool>(cycle, 1));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (lines[i][j] == '#' || lines[i][j] == '.') continue;
            int y = i, x = j;
            for (int k = 0; k < cycle; ++k) {
                seen[toKey(y, x)][k] = 0;
                if (lines[i][j] == '^') y--;
                else if (lines[i][j] == 'v') y++;
                else if (lines[i][j] == '<') x--;
                else x++;
                y = negMod(y - 1, n - 2) + 1;
                x = negMod(x - 1, m - 2) + 1;
            }
        }
    }

    vector<vector<pair<int, int>>> path = {
        {{0, 1}, {n - 1, m - 2}},
        {{n - 1, m - 2}, {0, 1}},
        {{0, 1}, {n - 1, m - 2}}
    };

    int ans1 = 0, ans2 = 0, prev = 0;
    for (int r = 0; r < 3; ++r) {
        pair<int, int> START = path[r][0], TAR = path[r][1];
        state[prev][START.first + n * START.second] = 1;

        for (int i = prev; i < N - 1; ++i) {
            if (state[i][TAR.first + n * TAR.second]) {
                prev = i;
                if (r == 0) ans1 = i - 1;
                ans2 = i - 1;
                fill(state[i].begin(), state[i].end(), 0);
                break;
            }

            for (int j = 0; j < M; ++j) {
                if (!state[i][j]) continue;
                pair<int, int> pos = {j % n, j / n};
                for (auto d : D) {
                    pair<int, int> newPos = {pos.first + d.first, pos.second + d.second};

                    if (newPos.first < 0 || newPos.first > n - 1 || newPos.second < 0 || newPos.second > m - 1) continue;
                    if (lines[newPos.first][newPos.second] == '#') continue;

                    int KEY = toKey(newPos.first, newPos.second);
                    if (seen[KEY][i % cycle]) state[i + 1][KEY] = true;
                }
            }
        }
    }

    cout << ans1 << " " << ans2 << "\n";
}