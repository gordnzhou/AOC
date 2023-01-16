#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

const int N = 1e3, ROUNDS = 10;

vector<pair<int, int>> D = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
set<pair<int, int>> elves;
map<pair<int, int>, vector<pair<int, int>>> cnts;

void draw() {
    int maxx = 0, maxy = 0, minx = 1e9, miny = 1e9;
    for (auto e : elves) {
        maxx = max(maxx, e.second);
        minx = min(minx, e.second);
        maxy = max(maxy, e.first);
        miny = min(miny, e.first);
    }

    for (int i = miny; i <= maxy; ++i) {
        for (int j = minx; j <= maxx; ++j) {
            if (elves.count({i, j})) cout << "#";
            else cout << ".";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);

    ifstream infile("input.txt");
    string line;

    vector<string> lines;
    while (getline(infile, line)) {
        istringstream iss(line);
        lines.push_back(line);
    }

    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[i].length(); ++j) {
            if (lines[i][j] == '#') {
                elves.insert({i, j});
            }
        }
    }

    int ans2 = 1, ans1;
    while (ans2++) {
        int stopped = 0;
        for (auto e : elves) {
            int i = e.first, j = e.second;
            bool good = false;
            for (int k = 0; k < 9; ++k) {
                int x = (k % 3 ? -1 : 0);
                if (k % 3 == 2) x = 1;
                int y = (k / 3 ? -1 : 0);
                if (k / 3 == 2) y = 1;
                if (!x && !y) continue;
                if (elves.count({i + y, j + x})) good = true;
            }
            if (!good) {
                stopped++;
                continue;
            }

            for (auto dir : D) {
                if (elves.count({i + dir.first, j + dir.second})) continue;
                if (dir.first == 0) {
                    if (elves.count({i + 1, j + dir.second}) || elves.count({i - 1, j + dir.second})) continue;
                }
                else {
                    if (elves.count({i + dir.first, j + 1}) || elves.count({i + dir.first, j - 1})) continue;
                }   
                cnts[{i + dir.first, j + dir.second}].push_back({i, j});
                break;
            }
        }
        if (stopped == elves.size()) break;

        for (auto c : cnts) {
            if (c.second.size() == 1) {
                elves.insert({c.first.first, c.first.second});
                elves.erase({c.second[0].first, c.second[0].second});
            }
        }
        cnts.clear();
        rotate(D.begin(), D.begin() + 1, D.end());

        if (ans2 == ROUNDS + 1) {
            int maxx = 0, maxy = 0, minx = 1e9, miny = 1e9;
            for (auto e : elves) {
                maxx = max(maxx, e.second);
                minx = min(minx, e.second);
                maxy = max(maxy, e.first);
                miny = min(miny, e.first);
            }
            ans1 = (maxx - minx + 1) * (maxy - miny + 1) - elves.size();
        }
    }
    ans2--;

    cout << ans1 << " " << ans2 << "\n";
}