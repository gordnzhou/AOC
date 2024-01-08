#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll; 


int solve() {
    string line;
    int ans = 0, diff = 0;

    vector<ll> row, col;

    ll i = 0;
    while (getline(cin, line)) {
        if (line.empty()) {
            break;
        }

        ll j = 0;
        for (auto c : line) {
            if (i >= row.size()) {
                row.push_back((1LL << j) * (c == '#'));
            }
            else row[i] += (1LL << j) * (c == '#');
            if (j >= col.size()) {
                col.push_back((1LL << i) * (c == '#'));
            }
            else col[j] += (1LL << i) * (c == '#');
            j++;
        }
        i++;
    }
    if (row.empty()) return 0;

    for (int i = 0; i < row.size() - 1; ++i) {
        bool ok = true;
        for (int j = 0; j < row.size(); ++j) {
            if (i - j < 0 || i + j + 1 >= row.size()) continue;
            ok &= row[i - j] == row[i + j + 1];
        }
        if (ok) {
            diff = (i + 1) * 100;
        }
    }

    for (int i = 0; i < col.size() - 1; ++i) {
        bool ok = true;
        for (int j = 0; j < col.size(); ++j) {
            if (i - j < 0 || i + j + 1 >= col.size()) continue;
            ok &= col[i - j] == col[i + j + 1];
        }
        if (ok) {
            diff = i + 1;
        }
    }

    for (int i1 = 0; i1 < row.size(); ++i1) {
        for (int j1 = 0; j1 < col.size(); ++j1) {
            row[i1] ^= (1 << j1);
            col[j1] ^= (1 << i1);

            for (int i = 0; i < row.size() - 1; ++i) {
                bool ok = true;
                for (int j = 0; j < row.size(); ++j) {
                    if (i - j < 0 || i + j + 1 >= row.size()) continue;
                    ok &= row[i - j] == row[i + j + 1];
                }
                if (ok && (i + 1) * 100 != diff) {
                    return (i + 1) * 100 + solve();
                }
            }

            for (int i = 0; i < col.size() - 1; ++i) {
                bool ok = true;
                for (int j = 0; j < col.size(); ++j) {
                    if (i - j < 0 || i + j + 1 >= col.size()) continue;
                    ok &= col[i - j] == col[i + j + 1];
                }
                if (ok && i + 1 != diff) {
                    return i + 1 + solve();
                }
            }

            row[i1] ^= (1 << j1);
            col[j1] ^= (1 << i1);
        }
    }

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream infile("input.txt");

    cout << solve() << "\n";
}