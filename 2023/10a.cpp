#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream infile("input.txt");
    string line;
    string s;


    vector<vector<char>> grid;
    while (getline(cin, line)) {
        vector<char> row;
        for (auto c : line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }

    pair<int, int> start;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 'S') {
                start = {i, j};
            }
        }
    }

    pair<int, int> pos = {start.first + 1, start.second}, prev = start;
    int ans = 0;
    while (pos != start) {
        int i = pos.first, j = pos.second;
        int pi = prev.first, pj = prev.second;
        prev = pos;
        if (grid[i][j] == '|') {
            if (pi != i - 1) {
                pos = {i - 1, j};
            }
            else {
                pos = {i + 1, j};
            }
        }
        else if (grid[i][j] == '-') {
            if (pj != j - 1) {
                pos = {i, j - 1};
            }
            else {
                pos = {i, j + 1};
            }
        }
        else if (grid[i][j] == 'L') {
            if (pi != i - 1) {
                pos = {i - 1, j};
            }
            else {
                pos = {i, j + 1};
            }
        }
        else if (grid[i][j] == 'J') {
            if (pi != i - 1) {
                pos = {i - 1, j};
            }
            else {
                pos = {i, j - 1};
            }
        }
        else if (grid[i][j] == '7') {
            if (pi != i + 1) {
                pos = {i + 1, j};
            }
            else {
                pos = {i, j - 1};
            }
        }
        else if (grid[i][j] == 'F') {
            if (pi != i + 1) {
                pos = {i + 1, j};
            }
            else {
                pos = {i, j + 1};
            }
        }
        ans++;
    }

    cout << (ans + 1) / 2 << "\n";
}